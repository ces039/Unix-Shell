/* Corrine Smith
 * CSCI 315
 * Lab 4
 * 9/19/17
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

pid_t Fork(void);

int Pipe(int pipefd[2]);

int Read(int fd, void *buf, size_t count);

int Write(int fd, const void *buf, size_t count);

pid_t Wait(int *status);

pid_t Waitpid(pid_t pid, int *status, int options);

int Open(const char *pathname, int flags);

int Close(int fd);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int Getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
