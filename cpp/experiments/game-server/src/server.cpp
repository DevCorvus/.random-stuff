#include "udp.hpp"
#include <arpa/inet.h>
#include <chrono>
#include <cstdio>
#include <netinet/in.h>
#include <thread>

int main() {
    auto udpServer = UDPServer();
    std::vector<Message *> messages;

    udpServer.listen("0.0.0.0", "8080",
                     [&messages](const char *buffer, int numbytes,
                                 const struct sockaddr_storage &client_addr) {
                         char s[INET6_ADDRSTRLEN];
                         inet_ntop(client_addr.ss_family,
                                   getInAddr((struct sockaddr *)&client_addr),
                                   s, sizeof s);

                         printf("got packet from %s\n", s);
                         printf("packet is %d bytes long\n", numbytes);

                         messages.push_back((Message *)buffer);
                     });

    while (messages.size() < 4) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };

    for (auto msg : messages) {
        printf("Timestamp %lu\n", msg->timestamp);
    }
}
