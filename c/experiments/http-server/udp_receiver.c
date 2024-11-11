
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT "8080"
#define BUFFER_SIZE 256

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void) {
    int sockfd;
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;     // IPv6
    hints.ai_socktype = SOCK_DGRAM; // UDP
    hints.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
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

    while (true) {
        printf("waiting to recvfrom...\n");

        char buffer[BUFFER_SIZE];
        struct sockaddr_storage their_addr;
        socklen_t addr_len = sizeof their_addr;

        int numbytes;
        if ((numbytes = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                                 (struct sockaddr *)&their_addr, &addr_len)) <
            0) {
            perror("recvfrom error");
            exit(EXIT_FAILURE);
        }

        char s[INET6_ADDRSTRLEN];
        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);

        printf("got packet from %s\n", s);
        printf("packet is %d bytes long\n", numbytes);

        buffer[numbytes] = '\0';
        printf("packet contains \"%s\"\n\n", buffer);
    }

    close(sockfd);
}
