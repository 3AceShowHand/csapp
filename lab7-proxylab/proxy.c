#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "csapp.h"
#include "proxy.h"
#include "cache.h"

static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

typedef struct {
	char* method;
	char* url;
	char* version;
} request_line;

typedef struct {
	int connection;
	char* host;
	char* user_agent;
	char* accept_language;
} request_header_line;

typedef struct {
	request_line title;
	request_header_line content;
} request;

typedef struct {
	char* version;
	char* status;
	char* status_info;
} response_line;

typedef struct {
	char* connection;
	char* server;
	char* last_modified;
	char* content_length;
	char* content_type;
} response_header_line;

typedef struct {
	response_line title;
	response_header_line content;
} response;

void get_request(int fd, char* buf, int buflen) {
	rio_t rio;
	Rio_readinitb(&rio, fd);

	char line[MAXLINE];
	Rio_readlineb(&rio, line, MAXLINE);
	while (strcmp(line, "\r\n")) {
		strcat(buf, line);
		Rio_readlineb(&rio, line, MAXLINE);
	}
	strcat(buf, "\r\n");
	printf("%s\n", buf);
}

void parse_title(request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = " ";
	char* token = strtok_r(rest, delim, &rest);
	req->title.method = strdup(token);
	token = strtok_r(rest, delim, &rest);
	req->title.url = strdup(token);
	token = strtok_r(rest, delim, &rest);
	req->title.version = strdup(token);
}

void parse_host(request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = ": ";
	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	req->content.host = strdup(token);
}

void parse_useragent(request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = ": ";
	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	req->content.user_agent = strdup(token);
}

void parse_language(request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = ": ";
	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	req->content.accept_language = strdup(token);
}

/*
 * parse a http request line by line
 * only store title, host, user-agent, language information
*/
request* build_request(char* buf, int buflen) {
	request* ret = (request*)Malloc(sizeof(request));
	char* rest = buf;
	const char* delim = "\r\n";

	char* line = strtok_r(rest, delim, &rest);
	parse_title(ret, line, MAXLINE);

	line = strtok_r(rest, delim, &rest);
	parse_host(ret, line, MAXLINE);

	line = strtok_r(rest, delim, &rest);
	parse_useragent(ret, line, MAXLINE);

	line = strtok_r(rest, delim, &rest);
	line = strtok_r(rest, delim, &rest);
	parse_language(ret, line, MAXLINE);

	ret->content.connection = 0;

	return ret;
}

void destroy_request(request* n) {
	Free(n->title.method);
	Free(n->title.url);
	Free(n->title.version);
	Free(n->content.host);
	Free(n->content.user_agent);
	Free(n->content.accept_language);
	Free(n);
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	char hostname[MAXLINE], port[MAXLINE];
	struct sockaddr_storage clientaddr;
	socklen_t clientlen;
	int listenfd, connfd;
	listenfd = Open_listenfd(argv[1]);

	char buf[MAXLINE];
	while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE,
		            port, MAXLINE, 0);
		printf("Accepted connection from (%s, %s)\n", hostname, port);
		memset(buf, 0, MAXLINE);
		get_request(connfd, buf, MAXLINE);
		request* req =  build_request(buf, MAXLINE);

		printf("method is: %s\n", req->title.method);
		printf("length of method is: %d\n", strlen(req->title.method));
		printf("url is: %s\n", req->title.url);
		printf("version is: %s\n", req->title.version);
		printf("host is: %s\n", req->content.host);
		printf("language is: %s\n", req->content.accept_language);
		printf("user-agent is: %s\n", req->content.user_agent);
		printf("connection is: %d\n", req->content.connection);
		destroy_request(req);
		Close(connfd);
	}
}
