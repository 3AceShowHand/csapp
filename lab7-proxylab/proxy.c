#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "csapp.h"
#include "proxy.h"
#include "cache.h"

typedef struct {
	char* method;
	char* url;
	char* version;
	char* host;
	char* user_agent;
	char* accept_language;
	char connection[6];
} client_request;

typedef struct {
	char* query;
	char* host;
	char* version;
} proxy_request;

//typedef struct {
//	char* version;
//	char* status;
//	char* status_info;
//} response_line;
//
//typedef struct {
//	char connection[6];
//	char* server;
//	char* last_modified;
//	char* content_length;
//	char* content_type;
//} response_header_line;

//typedef struct {
//	response_line title;
//	response_header_line content;
//} response;

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

char* build_query(char* str, int len) {
	char* ret = (char*)Malloc(len + 2);
	*ret = '/';
	strcpy(ret+1, str);
	return ret;
}

void parse_proxy(proxy_request* proxyRequest, char* line, int buflen) {
	char* rest = line;
	const char* delim = "/";

	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	proxyRequest->host = strdup(token);
	proxyRequest->query = build_query(rest, strlen(rest));
	proxyRequest->version = strdup("HTTP/1.0");
}

void parse_title(client_request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = " ";
	char* token = strtok_r(rest, delim, &rest);

	req->method = strdup(token);
	token = strtok_r(rest, delim, &rest);
	req->url = strdup(token);
	token = strtok_r(rest, delim, &rest);
	req->version = strdup(token);
}

void parse_host(client_request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = ": ";
	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	req->host = strdup(token);
}

void parse_useragent(client_request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = ": ";
	strtok_r(rest, delim, &rest);
	req->user_agent = strdup(rest+1);
}

void parse_language(client_request* req, char* line, int buflen) {
	char* rest = line;
	const char* delim = ": ";
	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	req->accept_language = strdup(token);
}

/*
 * parse a http request line by line
 * only store title, host, user-agent, language information
*/
client_request* build_client_request(char* buf, int buflen) {
	client_request* ret = (client_request*)Malloc(sizeof(client_request));
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

	strncpy(ret->connection, "close", 6);

	return ret;
}

void destroy_client_request(client_request* n) {
	Free(n->method);
	Free(n->url);
	Free(n->version);
	Free(n->host);
	Free(n->user_agent);
	Free(n->accept_language);
	Free(n);
}

proxy_request* build_proxy_request(client_request* req) {
	proxy_request* ret = (proxy_request*)Malloc(sizeof(proxy_request));
	parse_proxy(ret, req->url, strlen(req->host));
	return ret;
}

void destroy_proxy_request(proxy_request* x) {
	Free(x->host);
	Free(x->query);
	Free(x->version);
	Free(x);
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
		client_request* req = build_client_request(buf, MAXLINE);

		printf("method is: %s\n", req->method);
		printf("url is: %s\n", req->url);
		printf("version is: %s\n", req->version);
		printf("host is: %s\n", req->host);
		printf("language is: %s\n", req->accept_language);
		printf("user-agent is: %s\n", req->user_agent);
		printf("connection is: %s\n", req->connection);

		proxy_request* proxyRequest = build_proxy_request(req);
		printf("request host for proxy is: %s\n", proxyRequest->host);
		printf("request query for proxy is: %s\n", proxyRequest->query);
		printf("request version for proxy is: %s\n", proxyRequest->version);
		destroy_client_request(req);
		destroy_proxy_request(proxyRequest);
		Close(connfd);
	}
}
