#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "csapp.h"
#include "proxy.h"
#include "cache.h"

typedef struct {
	char* method;
	char* host;
	char* query;
	char* version;
	char* user_agent;
	char* accept_language;
	char connection[6];
	char proxy_connection[6];

} request;

char* build_query(char* str, int len) {
	char* ret = (char*)Malloc(len + 2);
	*ret = '/';
	strcpy(ret+1, str);
	return ret;
}

/*
 * get host and query for request
*/
void parse_host_query(request* req, char* line, int len) {
	char* rest = line;
	const char* delim = "/";

	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	req->host = strdup(token);
	req->query = build_query(rest, strlen(rest));
}

/*
 * get http method, version by call this function.
 * host and query also obtained by call parse_host_query.
*/
void parse_title(request* req, char* line, int len) {
	char* rest = line;
	const char* delim = " ";
	char* token = strtok_r(rest, delim, &rest);
	req->method = strdup(token);

	token = strtok_r(rest, delim, &rest);
	parse_host_query(req, token, strlen(token));

	// token = strtok_r(rest, delim, &rest);
	req->version = strdup("HTTP/1.0");
}

/*
 * get user_agent for request
*/
void parse_useragent(request* req, char* line, int len) {
	char* rest = line;
	const char* delim = ": ";
	strtok_r(rest, delim, &rest);
	req->user_agent = strdup(rest+1);
}

/*
 * get accept_language for request
*/
void parse_language(request* req, char* line, int len) {
	char* rest = line;
	const char* delim = ": ";
	char* token = strtok_r(rest, delim, &rest);
	token = strtok_r(rest, delim, &rest);
	req->accept_language = strdup(token);
}

/*
 * parse incoming client http request into a struct
 * each field obtained by parse functions above.
 * each function parse lines by call strtok_r function to separte each words in the line.
*/
request* build_request(char* buf, int len) {
	request* req = (request*)Malloc(sizeof(request));

	char* rest = buf;
	const char* delim = "\r\n";
	char* line = NULL;

	while ((line = strtok_r(rest, delim, &rest))) {
		if (strstr(line, "HTTP") != NULL) {
			parse_title(req, line, strlen(line));
		} else if (strstr(line, "User-Agent") != NULL) {
			parse_useragent(req, line, strlen(line));
		} else if (strstr(line, "Accept-Language") != NULL) {
			parse_language(req, line, strlen(line));
		}
	}
	strncpy(req->connection, "close", 6);
	strncpy(req->proxy_connection, "close", 6);
	return req;
}

void destroy_request(request* n) {
	Free(n->method);
	Free(n->host);
	Free(n->query);
	Free(n->version);
	Free(n->user_agent);
	Free(n->accept_language);
	Free(n);
}

void get_request(int fd, char* buf, int len) {
	rio_t rio;
	Rio_readinitb(&rio, fd);

	char line[MAXBUF];
	Rio_readlineb(&rio, line, MAXBUF);
	while (strcmp(line, "\r\n")) {
		strcat(buf, line);
		Rio_readlineb(&rio, line, MAXBUF);
	}
	strcat(buf, "\r\n");
	printf("%s\n", buf);
}

void send_proxy_request(request* req) {
	char buf[MAXBUF];

	sprintf(buf, "%s %s %s\r\n", req->method, req->query, req->version);
	sprintf(buf, "%sHost: %s\r\n", buf, req->host);
	sprintf(buf, "%sConnection: %s\r\n", buf, req->connection);
	sprintf(buf, "%sProxy Connetion: %s\r\n", buf, req->proxy_connection);
	printf("response header is\n");
	printf("%s", buf);
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	char hostname[MAXBUF], port[MAXBUF];
	struct sockaddr_storage clientaddr;
	socklen_t clientlen;
	int listenfd, connfd;
	listenfd = Open_listenfd(argv[1]);

	char buf[MAXBUF];
	while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXBUF,
		            port, MAXBUF, 0);
		printf("Accepted connection from (%s, %s)\n", hostname, port);

		memset(buf, 0, MAXBUF);
		get_request(connfd, buf, MAXBUF);
		request* req = build_request(buf, strlen(buf));

		printf("method is: %s\n", req->method);
		printf("host is: %s\n", req->host);
		printf("query is: %s\n", req->query);
		printf("version is: %s\n", req->version);
		printf("user-agent is: %s\n", req->user_agent);
		printf("language is: %s\n", req->accept_language);
		printf("connection is: %s\n", req->connection);
		printf("proxy connection is: %s\n", req->proxy_connection);
		send_proxy_request(req);
		destroy_request(req);
		Close(connfd);
	}
}

