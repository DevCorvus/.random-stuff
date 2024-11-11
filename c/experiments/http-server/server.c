#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT "8080" // Pass as arg (?)
#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 1024 // 1 KB

// TODO: Multithreading

const char *get_file_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');

    if (!dot || dot == filename) {
        return "";
    }

    return dot + 1;
}

const char *get_mime_type(const char *file_ext) {
    if (strcasecmp(file_ext, "html") == 0 || strcasecmp(file_ext, "htm") == 0) {
        return "text/html";
    } else if (strcasecmp(file_ext, "txt") == 0) {
        return "text/plain";
    } else if (strcasecmp(file_ext, "jpg") == 0 ||
               strcasecmp(file_ext, "jpeg") == 0) {
        return "image/jpeg";
    } else if (strcasecmp(file_ext, "png") == 0) {
        return "image/png";
    } else {
        return "application/octet-stream";
    }
}

void send_file_response(int fd, char *filename) {
    int file_fd;
    char res[BUFFER_SIZE];

    // Try to open file
    // TODO: Handle security (allow only safe dir/subdirs and files with
    // permissions)
    if ((file_fd = open(filename, O_RDONLY)) < 0) {
        snprintf(res, BUFFER_SIZE,
                 "HTTP/1.1 404 Not Found\r\n"
                 "Content-Type: text/plain\r\n"
                 "\r\n");

        printf("RESPONSE PAYLOAD\n\n"
               "%s\n",
               res);

        perror("open error");

        send(fd, res, strlen(res), 0);
        return;
    }

    // Get file stat (file size)
    struct stat file_stat;
    fstat(file_fd, &file_stat);
    off_t file_size = file_stat.st_size;

    // Get file extension
    char file_ext[32];
    strcpy(file_ext, get_file_extension(filename));

    // Basic headers
    char header[BUFFER_SIZE];
    snprintf(header, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %ld\r\n"
             "\r\n",
             get_mime_type(file_ext), file_size);

    size_t res_len = strlen(header);
    memcpy(res, header, res_len);

    // Read file bytes
    size_t bytes_read;
    while ((bytes_read = read(file_fd, res + res_len, BUFFER_SIZE - res_len)) >
           0) {
        res_len += bytes_read;
    }

    printf("RESPONSE PAYLOAD\n\n"
           "%s\n",
           res);

    // Send response (remaining bytes are not handled)
    send(fd, res, res_len, 0);
    close(file_fd);
}

void send_file_from_url_param(int fd, char *buffer) {
    char *filename = buffer + 5;
    char *first_space = strchr(filename, ' ');

    if (first_space != NULL) {
        *first_space = 0;
    }

    send_file_response(fd, filename);
}

void old_way() {
    int server_fd;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Use my IPv4 address
    server_addr.sin_port = htons(8080);       // Port byte ordered

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    // Then listen and bla bla bla
}

int main() {
    int status;
    struct addrinfo hints;     // Config
    struct addrinfo *servinfo; // Result

    memset(&hints, 0, sizeof hints); // Ensure hints is clear
    hints.ai_family = AF_INET;       // Force IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // Set localhost (127.0.0.1)

    // First parameter is NULL because of ai_flags
    if ((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) < 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    int server_fd;
    struct addrinfo *p;

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) <
            0) {
            perror("socket error");
            continue;
        }

        // Reuse socket address
        int yes = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) <
            0) {
            perror("setsockopt error");
            exit(EXIT_FAILURE);
        }

        // Bind port
        if (bind(server_fd, p->ai_addr, p->ai_addrlen) < 0) {
            close(server_fd);
            perror("bind error");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);

    // Wait for incoming connections
    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %s\n", PORT);

    while (true) {
        int client_fd;
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                                &client_addr_len)) < 0) {
            perror("accept error");
            continue;
        }

        // Get client IPv4 address
        char ip4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, ip4, INET_ADDRSTRLEN);

        // Get request buffer
        // TODO: Compliant parsing and validation
        char buffer[BUFFER_SIZE];
        recv(client_fd, buffer, BUFFER_SIZE, 0);

        printf("FROM %s\n\n"
               "REQUEST PAYLOAD\n\n"
               "%s\n",
               ip4, buffer);

        send_file_from_url_param(client_fd, buffer);
        close(client_fd);
    }

    close(server_fd);
}
