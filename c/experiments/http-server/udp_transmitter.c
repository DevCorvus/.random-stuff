#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT "8080"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "missing message\n");
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;    // use IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; // UDP
    hints.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) < 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) <
            0) {
            perror("socket error");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);

    int numbytes;
    if ((numbytes = sendto(sockfd, argv[1], strlen(argv[1]), 0, p->ai_addr,
                           p->ai_addrlen)) < 0) {
        perror("sendto error");
        exit(EXIT_FAILURE);
    }

    close(sockfd);
}
