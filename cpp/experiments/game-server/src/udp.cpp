#include "udp.hpp"
#include <cstdio>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

void *getInAddr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void UDPServer::listen(const char *addr, const char *port, Callback cb) {
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    int status;
    if ((status = getaddrinfo(addr, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) <
            0) {
            perror("socket error");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) < 0) {
            close(sockfd);
            perror("bind error");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "failed to bind socket\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);

    std::thread([this, cb]() {
        while (true) {
            printf("waiting to recvfrom...\n");

            char buffer[BUFFER_SIZE];
            struct sockaddr_storage client_addr;
            socklen_t addr_len = sizeof client_addr;

            int numbytes;
            if ((numbytes = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                                     (struct sockaddr *)&client_addr,
                                     &addr_len)) < 0) {
                perror("recvfrom error");
                exit(EXIT_FAILURE);
            }

            buffer[numbytes] = '\0';

            cb(buffer, numbytes, client_addr);
        }
    }).detach();
}

void UDPServer::send(const char *addr, const char *port, const Message data) {
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int status;
    if ((status = getaddrinfo(addr, port, &hints, &servinfo)) < 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) <
            0) {
            perror("socket error");
            continue;
        }

        // TODO: Bind socket

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);

    int numbytes;
    if ((numbytes = sendto(sockfd, &data, sizeof(data), 0, p->ai_addr,
                           p->ai_addrlen)) < 0) {
        perror("sendto error");
        exit(EXIT_FAILURE);
    }
}

UDPServer::~UDPServer() { close(sockfd); }
