/*
 * Thread100.cpp
 *
 *  Created on: Aug 2, 2018
 *      Author: nadong
 */

#include "Thread100.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>


#define MAXLEN 4096

Thread100::Thread100() {
	// TODO Auto-generated constructor stub

}

Thread100::~Thread100() {
	// TODO Auto-generated destructor stub
}




void Thread100::testBlock() {
	// TODO Auto-generated constructor stub

    int    listenfd, sock_fd;
    struct sockaddr_in     servaddr;
    char    buff[MAXLEN];
    int     n;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)/n",strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8001);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    printf("waiting for client to connect\n");

    while(1){
        if( (sock_fd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }
        n = recv(sock_fd, buff, MAXLEN, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
        close(sock_fd);
        break;
    }
    close(listenfd);

}

void Thread100::testNonBlock() {
	// TODO Auto-generated constructor stub

    int    listenfd, sock_fd;
    struct sockaddr_in     servaddr;
    char    buff[MAXLEN];
    int     n;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)/n",strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8001);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    printf("waiting for client to connect\n");

    while(1){
        if( (sock_fd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }
        int flags = fcntl(sock_fd, F_GETFL, 0);
		fcntl(sock_fd, F_SETFL,flags | O_NONBLOCK);

	    n = recv(sock_fd, buff, MAXLEN, 0);
		printf("test block \n");
		while(n >= 0){
		     //buff[n] = '\0';
			  printf("recv msg from client: %s\n", buff);
			  break;
		}
    }
//    close(listenfd);

}

