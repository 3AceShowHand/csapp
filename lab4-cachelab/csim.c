/* A cache simulator, which takes a valgrind memory trace as input,
simulates the hit/miss behavior of a cache memory on this trace, and outputs
the total number of hits, misses and evictions.
*/

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cachelab.h"

typedef struct _cacheLine {
    int valid;
    long tag;
    int time;
} cacheLine;

typedef struct _traceLine {
    long addr;
    int size;
    char op;
} traceLine;

traceLine* createTrace() {
    traceLine* ret = (traceLine*)malloc(sizeof(traceLine));
    return ret;
}

void destroyTrace(traceLine* tl) {
    free(tl);
}

// build a cache, as an array of cacheline, lc = setCount * linePerSet
// return cache is success, else null
cacheLine*
buildCache(int lc) {
    cacheLine* cache = (cacheLine*)malloc(sizeof(cacheLine) * lc);
    if (cache == NULL) {
        return NULL;
    }
    for (int i = 0; i < lc; i++) {
        cache[i].valid = 0;
        cache[i].tag = 0;
        cache[i].time = 0;
    }
    return cache;
}

void destroyCache(cacheLine* cache) {
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

void parseLine(char* line, traceLine* tl) {
    char delim = ' ';
    char* token = strtok(line, &delim);
    tl->op = *token;
    delim = ',';
    token = strtok(NULL, &delim);
    tl->addr = atol(token);
    token = strtok(NULL, &delim);
    tl->size = atoi(token);
}

void getResult(const char* filename, cacheLine* cache, int* result, int rl) {
    if (cache == NULL) {
        return;
    } else if (filename == NULL) {
        return;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }
    char* line = NULL;
    size_t len = 0;

    traceLine* record = createTrace();
    if (record == NULL) {
        printf("cannot create trace line.");
        return;
    }
    while (getline(&line, &len, file) != -1) {
        if (line[0] == ' ') {
            parseLine(line, record);
        }
    }
    free(line);
    destroyTrace(record);
    fclose(file);
}

int main(int args, char* argv[]) {
    int addrSize = 64;
    int tagBits = 0;
    int setBits = 0;
    int blockBits = 0;

    int linePerSet = 0;
    int result[3] = {0, 0, 0};  // hit, miss, eviction

    int ch;
    const char* optstring = "hv::s:E:b:t:";
    char* filename = NULL;
    while ((ch = getopt(args, argv, optstring)) != -1) {
        switch (ch) {
            case 'h':
                helpInfo();
                break;
            case 'v':
                // print verbose information
                break;
            case 's':
                // fetch number of set index bits
                setBits = atoi(optarg);
                break;
            case 'E':
                // fetch number of lines per set (Associativity)
                linePerSet = atoi(optarg);
                break;
            case 'b':
                blockBits = atoi(optarg);
                // fetch number of block bits
                break;
            case 't':
                // fetch name of the valgrind trace to replay
                filename = strdup(optarg);
                break;
            default:
                break;
        }
    }

    int setCount = (int)pow(2, setBits);
    int lineCount = setCount * linePerSet;
    tagBits = addrSize - blockBits - setBits;
    cacheLine* cache = buildCache(lineCount);

    getResult(filename, cache, result, 3);
    printSummary(result[0], result[1], result[2]);
    free(filename);
    destroyCache(cache);
    return 0;
}