/* A cache simulator, which takes a valgrind memory trace as input,
simulates the hit/miss behavior of a cache memory on this trace, and outputs
the total number of hits, misses and evictions.
*/
#define _GNU_SOURCE

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cachelab.h"

typedef struct _args {
    int help;
    int verbose;
    int sbits;       // number of set index bits
    int lps;         // Associativity (number of lines per set)
    int bbits;       // number of block bits
    char* filename;  // Name of the valgrind trace to replay
} Args;

typedef struct _CacheLine {
    int valid;
    long tag;
    int time;
} CacheLine;

typedef struct _traceLine {
    long tag;
    long setIndex;
    char op;
} TraceLine;

Args* buildArgs() {
    Args* ret = (Args*)malloc(sizeof(Args));
    if (ret == NULL) {
        return NULL;
    }
    ret->help = 0;
    ret->verbose = 0;
    ret->sbits = 0;
    ret->lps = 0;
    ret->bbits = 0;
    ret->filename = NULL;

    return ret;
}

void destroyArgs(Args* x) {
    if (x->filename != NULL) {
        free(x->filename);
    }
    free(x);
}

TraceLine* createTrace() {
    TraceLine* ret = (TraceLine*)malloc(sizeof(TraceLine));
    return ret;
}

void destroyTrace(TraceLine* tl) {
    free(tl);
}

// build a cache, as an array of cacheline, lc = setCount * linePerSet
// return cache is success, else null
CacheLine* buildCache(int lc) {
    CacheLine* cache = (CacheLine*)malloc(sizeof(CacheLine) * lc);
    if (cache == NULL) {
        return NULL;
    }
    for (int i = 0; i < lc; i++) {
        cache[i].valid = 0;
        cache[i].tag = -1;
        cache[i].time = 0;
    }
    return cache;
}

void destroyCache(CacheLine* cache) {
    free(cache);
}

// return a copy of s, should be freed by caller.
char* strdup(const char* s) {
    int len = strlen(s) + 1;
    char* ret = (char*)malloc(sizeof(char) * len);
    if (ret == NULL) {
        return NULL;
    }
    strcpy(ret, s);
    return ret;
}

void helpInfo() {
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\n");
    printf("Example:\n");
    printf("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace");
    printf("  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

int hexToDecimal(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return c - 'a' + 10;
}

long convertAddr(char* addr) {
    long ret = 0;
    for (int i = 0; addr[i] != '\0'; i++) {
        ret = ret * 16 + hexToDecimal(addr[i]);
    }
    return ret;
}

void parseAddr(char* addr, Args* arg, TraceLine* record) {
    long mask = 0;
    long x = convertAddr(addr);
    x = x >> arg->bbits;
    mask = (0x1L << arg->sbits) - 1;
    record->setIndex = x & mask;
    x = x >> arg->sbits;
    mask = (0x1L << (64 - arg->bbits - arg->sbits)) - 1;
    record->tag = x & mask;
}

void parseLine(char* line, TraceLine* tl, Args* arg) {
    if (line == NULL) {
        return;
    }
    if (tl == NULL) {
        return;
    }
    char delim = ' ';
    char* token = strtok(line, &delim);
    tl->op = *token;
    delim = ',';
    token = strtok(NULL, &delim);
    parseAddr(token, arg, tl);
}

// given setIdx and line per set, return idx = setIdx * linePerSet
int getStart(int setIdx, int lc) {
    return setIdx * lc;
}

// this function will be called, if all cache lines are valid, then find the one with largest time
int getLRUIndex(CacheLine* cache, int start, int lc) {
    int end = start + lc;
    int ret = start;
    for (int i = start + 1; i < end; i++) {
        if (cache[ret].time > cache[i].time) {
            ret = i;
        }
    }
    return ret;
}

// reset ith cache line, set valid, tag, and time to original status.
void replace(CacheLine* cache, int i, long t, int time) {
    cache[i].time = time;
    cache[i].tag = t;
    cache[i].valid = 1;
}

// hit, if a line in the given cache set have the same tag as argument t, return 1
// in miss, if all lines are valid, then eviction should be perform, return 0

void update(CacheLine* cache, TraceLine* record, Args* arg, int* result, int rl, int time) {
    int length = arg->lps;
    int start = getStart(record->setIndex, length);
    int end = start + length;
    CacheLine* cursor = NULL;
    int hit = -1;
    int empty = -1;
    for (int i = start; i < end; i++) {
        cursor = &(cache[i]);
        if (cursor->valid == 0) {  // find empty cache line, does not eviction.
            empty = i;
        } else if ((cursor->valid == 1) && (cursor->tag == record->tag)) {  // hit
            hit = i;
            replace(cache, hit, record->tag, time);
            result[0] += 1;
            if (arg->verbose) {
                printf(" hit");
            }
            return;
        }
    }
    // must miss.
    if (hit == -1) {
        result[1] += 1;
        if (empty != -1) {  // empty != -1, then just replace that cacheline
            replace(cache, empty, record->tag, time);
            if (arg->verbose) {
                printf(" miss");
            }
        } else {  // should eviction, which means all cacheLine is valid.
            int idx = getLRUIndex(cache, start, length);
            replace(cache, idx, record->tag, time);
            result[2] += 1;
            if (arg->verbose) {
                printf(" miss eviction");
            }
        }
    }
}

void getResult(Args* arg, int* result, int rl) {
    if (arg->filename == NULL) {
        return;
    }
    FILE* file = fopen(arg->filename, "r");
    if (file == NULL) {
        return;
    }
    int setSize = 1 << arg->sbits;
    CacheLine* cache = buildCache(arg->lps * setSize);
    if (cache == NULL) {
        return;
    }
    TraceLine* record = createTrace();
    if (record == NULL) {
        return;
    }
    char* line = NULL;
    size_t len = 0;
    int time = 1;
    while (getline(&line, &len, file) != -1) {
        if (line[0] == ' ') {
            strtok(line, "\n");
            if (arg->verbose) {
                printf("%s", line);
            }
            parseLine(line, record, arg);
            switch (record->op) {
                case 'L':
                    update(cache, record, arg, result, 3, time);
                    break;
                case 'S':
                    update(cache, record, arg, result, 3, time);
                    break;
                case 'M':
                    update(cache, record, arg, result, 3, time);
                    update(cache, record, arg, result, 3, time);
                    break;
                default:
                    break;
            }
            printf("\n");
        }
        time += 1;
    }
    free(line);
    destroyTrace(record);
    destroyCache(cache);
    fclose(file);
}

int main(int args, char* argv[]) {
    Args* arg = buildArgs();

    int ch;
    const char* optstring = "hv::s:E:b:t:";
    while ((ch = getopt(args, argv, optstring)) != -1) {
        switch (ch) {
            case 'h':
                arg->help = 1;
                break;
            case 'v':
                // print verbose information
                arg->verbose = 1;
                break;
            case 's':
                // fetch number of set index bits
                arg->sbits = atoi(optarg);
                break;
            case 'E':
                // fetch number of lines per set (Associativity)
                arg->lps = atoi(optarg);
                break;
            case 'b':
                arg->bbits = atoi(optarg);
                // fetch number of block bits
                break;
            case 't':
                // fetch name of the valgrind trace to replay
                arg->filename = strdup(optarg);
                break;
            default:
                break;
        }
    }
    if (arg->filename == NULL) {
        destroyArgs(arg);
        helpInfo();
        return 0;
    }
    int result[] = {0, 0, 0};
    getResult(arg, result, 3);
    printSummary(result[0], result[1], result[2]);
    destroyArgs(arg);
    return 0;
}