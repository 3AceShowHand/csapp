#include "csapp.h"

#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

typedef struct {
    char method[10];
    char host[50];
    char port[10];
    char query[50];
    char version[10];
    char user_agent[100];
    char accept_language[50];
    char connection[6];
    char proxy_connection[6];
} request;

void build_query(request* req, const char* str) {
    memset(req->query, 0, strlen(req->query));
    req->query[0] = '/';
    strcat(req->query, str);
}

void parse_useragent(request* req, char* line) {
    char* rest = line;
    const char* delim = ": ";
    strtok_r(rest, delim, &rest);
    strcpy(req->user_agent, rest + 1);
}

void parse_language(request* req, char* line) {
    char* rest = line;
    const char* delim = ": ";
    char* token = strtok_r(rest, delim, &rest);
    token = strtok_r(rest, delim, &rest);
    strcpy(req->accept_language, token);
}

void parse_host_query(request* req, char* line) {
    char* rest = line;
    const char* delim = "/";

    char* token = strtok_r(rest, delim, &rest);
    token = strtok_r(rest, delim, &rest);
    build_query(req, rest);
    if (strstr(token, ":")) {
        token = strtok_r(token, ":", &rest);
        strcpy(req->port, rest);
    } else {
        strcpy(req->port, "80");
    }
    strcpy(req->host, token);
}

void parse_title(request* req, char* line) {
    char* rest = line;
    const char* delim = " ";
    char* token = strtok_r(rest, delim, &rest);
    strcpy(req->method, token);

    token = strtok_r(rest, delim, &rest);
    parse_host_query(req, token);
    strcpy(req->version, "HTTP/1.0");
}

request* build_request(char* buf, int len) {
    request* req = (request*)Malloc(sizeof(request));

    char* rest = buf;
    const char* delim = "\r\n";
    char* line = NULL;

    while ((line = strtok_r(rest, delim, &rest))) {
        if (strstr(line, "HTTP") != NULL) {
            parse_title(req, line);
        } else if (strstr(line, "User-Agent") != NULL) {
            parse_useragent(req, line);
        } else if (strstr(line, "Accept-Language") != NULL) {
            parse_language(req, line);
        }
    }
    strncpy(req->connection, "close", 6);
    strncpy(req->proxy_connection, "close", 6);
    return req;
}

void destroy_request(request* req) {
    Free(req);
}

/*
 * parse incoming client http request into a struct
 * each field obtained by parse functions above.
 * each function parse lines by call strtok_r function to separte each words in the line.
*/

void send_request(int fd, request* req) {
    char buf[MAXBUF];
    sprintf(buf, "%s %s %s\r\n", req->method, req->query, req->version);
    sprintf(buf, "%sHost: %s\r\n", buf, req->host);
    sprintf(buf, "%sConnection: %s\r\n", buf, req->connection);
    sprintf(buf, "%sProxy Connetion: %s\r\n\r\n", buf, req->proxy_connection);

    int proxyfd = Open_clientfd(req->host, req->port);
    rio_t rio;
    Rio_readinitb(&rio, proxyfd);
    Rio_writen(proxyfd, buf, strlen(buf));
    int n;
    memset(buf, 0, MAXBUF);
    while ((n = rio_readlineb(&rio, buf, MAXBUF)) != 0) {
        Rio_writen(fd, buf, n);
    }
    Close(proxyfd);
    Close(fd);
}

void doit(int fd) {
    rio_t rio;
    Rio_readinitb(&rio, fd);
    char buf[MAXBUF];
    char line[MAXBUF];
    memset(buf, 0, MAXBUF);
    memset(line, 0, MAXBUF);
    Rio_readlineb(&rio, line, MAXBUF);
    while (strcmp(line, "\r\n")) {
        strcat(buf, line);
        Rio_readlineb(&rio, line, MAXBUF);
    }
    strcat(buf, "\r\n");
    request* req = build_request(buf, strlen(buf));

    send_request(fd, req);
    destroy_request(req);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    char hostname[MAXBUF], port[MAXBUF];
    struct sockaddr_storage clientaddr;
    socklen_t clientlen;
    int listenfd, connfd;
    listenfd = Open_listenfd(argv[1]);

    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
        Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXBUF,
                    port, MAXBUF, 0);
        fprintf(stdout, "Accepted connection from (%s, %s)\n", hostname, port);
        doit(connfd);
    }
}