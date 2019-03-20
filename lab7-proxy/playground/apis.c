#include <arpa/inet.h>

struct in_addr {
    uint32_t s_addr;
};

struct sockaddr {
    uint16_t sa_family;
    char sa_data[14];
};

struct sockaddr_in {
    uint16_t sin_family;
    uint16_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
};

struct addrinfo {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    char* ai_canonname;
    size_t ai_addrlen;
    struct sockaddr* ai_addr;
    struct addrinfo* ai_next;
};

uint32_t htonl(uint32_t hostlong);   // convert 32bit host endian to network endian (big-endian)
uint16_t htons(uint16_t hostshort);  // convert 16bit host endian to network endian

uint32_t ntohl(uint32_t netlong);    // convert 32bit network endian (big-endian) to host endian
uint16_t ntohs(uint16_t hostshort);  // convert 16bit network endian to host endian

/* 
 * af must be AF_INET or AF_INET6
 * src point to a string containing an ip address of the form "ddd.ddd.ddd.ddd"
 * src is converted to a struct in_addr and copied to dst
 * the size of dst pointed to must be sizeof(struct in_addr)
 * return 1 on success,
 * return 0 if src does not contain a character string representation
 * return -1 if af does not contain a valid address family, errno set to EAFNOSUPPORT
*/
int inet_pton(int af, const char* src, void* dst);
struct sockaddr_in sa;
char str[INET_ADDRSTRLEN];

inet_pton(AF_INET, "192.0.2.33", &(sa.sin_addr));

/*
* convert the network address structure src in the af address family into
* a character string. The resulting string is copied to the buffer pointed
* to by dst, which must be a non-null pointer. The caller specifies the number
* of bytes available in this buffer in argument size.
* return a non-null pointer to dst, on success.
* return NULL if there was an erro , errno set to indicate the error.
*/
const char* inet_ntop(int af, const void* src, char* dst, socklen_t size);

#include <sys/socket.h>
#include <sys/types.h>

/* 
 * create an endpoint for communication and return s descriptor.
 * domain: specifies communication domain, select the protocol family which will be
 * used for communication.
 * type: specifies the communication semantics.
 * SOCK_STREAM: tcp, provides sequenced, reliable, two-way, connection-based byte stream.
 * SOCK_DGRAM: udp, connectionless, unreliable message of a fixed maximum length.
 * protocol: specifies a particular protocol to be used with the socket. Normally only a 
 * single protocol exists to support a particular socket type within a given protocol family,
 * can be set to 0. if many protocols exists, must be specified.
 * on success, return a file descriptor.
 * on error, return -1 and errno is set appropriately.
*/
int socket(int domain, int type, int protocol);
int clientfd = socket(AF_INET, SOCK_STREAM, 0);

/*
 * connect the socket clientfd to the address specified by addr, addrlen specifies
 * the size of addr.
 * if clientfd is of type SOCK_DGRAM, addr is the address to which datagrams are sent by default
 * else of type SOCK_STREAM, this call attemps to make a connection to the socket that is bound to the address specified by addr.
 * return 0, if the connection or binding succeed.
 * else reutrn -1 on error, and errno is set appropriately.
*/
int connect(int clientfd, const struct sockaddr* addr, socklen_t addrlen);

/*
 * assigns the address specified by addr to the socket referred to by the sockfd.
 * The actual structure passed for the addr argument will depend on the address family.
 * on success, reurn 0
 * on error, return -1, errno is set.
*/
int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);

/*
 * mark the socket referred to by sockfd as a passive socket,
 * be used to accept incoming connection requests.
 * backlog defines the maximum length of the queue of pending connections
 * return 0 on success, return -1 on error, errno is set.
*/
int listen(int sockfd, int backlog);

/*
 * used with connection-based socket types.
 * listenfd is a socket, bound to a local address, and is listening for connections.
 * on success, return a non-nagative integer.
 * on error, return -1, errno is set.
*/
int accept(int listenfd, struct sockaddr* addr, int* addrlen);

/*
 * Given host and service, returns one or more addrin structures.
 * hints point to an addrinfo, specifies criteria for selecting the socket address
 * structures returned in the list pointed to by results.
 * return 0 on succeed, else return a non-zero error code.
*/
int getaddrinfo(const char* host, const char* service,
                const struct addrinfo* hints, struct addrinfo** results);

void freeaddrinfo(struct addrinfo* result);

const char* gai_strerror(int errcode);

/*
 * convert a socket address to a corresponding host and service, in a protocol-independent
 * manner.
 * sa is a pointer to a generic socket address structure of size salen.
 * host and service pointed to caller-allocated buffers, and put null-terminated strings containing
 * the host and service names respectively.
 * return 0 on success, and host and service name.
 * on error, one of the nonzero error codes is returned. 
*/
int getnameinfo(const struct sockaddr* sa, socklen_t salen,
                char* host, size_t hostlen, char* service, size_t servlen, int flags);
