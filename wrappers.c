/* Corrine Smith
 * CSCI 315
 * Lab 4
 * 9/19/17
 */

#include "wrappers.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

int
Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	if(accept(sockfd, addr, addrlen) == -1){
		perror("Accept failed");
		exit(-1);
	}
}

pid_t
Fork(void){
	pid_t pid = fork();
	if(pid == -1){
		perror("Fork failed");
		exit(-1);
	}
}

int
Pipe(int pipefd[2]){
	if(pipe(pipefd) == -1){
		perror("Pipe failed");
		exit(-1);
	}
}

int
Read(int fd, void *buf, size_t count){
	if(read(fd, buf, count) == -1){
		perror("Read failed");
		exit(-1);
	}
}

int
Write(int fd, const void *buf, size_t count){
	if(write(fd, buf, count) == -1){
		perror("Write failed");
		exit(-1);
	}
}

pid_t
Wait(int *status){
	if(wait(status) == -1){
		perror("Wait failed");
		exit(-1);
	}
}

pid_t
Waitpid(pid_t pid, int *status, int options){
	if(waitpid(pid, status, options) == -1){
		perror("Waitpid failed");
		exit(-1);
	}
}

int
Open(const char *pathname, int flags){
	if(open(pathname, flags) == -1){
		perror("Open failed");
		exit(-1);
	}
}

int
Close(int fd){
	if(close(fd) == -1){
		perror("Close failed");
		exit(-1);
	}
}

int
Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	if(connect(sockfd, addr, addrlen) == -1){
		perror("Connect failed");
		exit(-1);
	}
}

int
Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	if(bind(sockfd, addr, addrlen) == -1){
		perror("Bind failed");
		exit(-1);
	}
}

int
Listen(int sockfd, int backlog){
	if(listen(sockfd, backlog) == -1){
		perror("Listen failed");
		exit(-1);
	}
}

int
Getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res){
	if(getaddrinfo(node, service, hints, res) == -1){
		perror("Getaddrinfo failed");
		exit(-1);
	}
}
