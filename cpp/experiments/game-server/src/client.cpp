#include "udp.hpp"
#include <ctime>
#include <thread>

int main(int argc, char **argv) {
    auto *serverIp = "127.0.0.1";
    auto *serverPort = "8080";

    auto udpServer = UDPServer();

    Message msg;
    msg.type = MessageType::CONNECT;
    msg.timestamp = std::time(NULL);

    std::vector<Message *> messages;

    udpServer.listen(serverIp, serverPort,
                     [&messages](const char *buffer, int numbytes,
                                 const struct sockaddr_storage &client_addr) {
                         messages.push_back((Message *)buffer);
                     });

    // Connect
    udpServer.send(serverIp, serverPort, msg);

    bool gameRunning = true;

    while (gameRunning) {
        auto msg = messages.front();

        if (msg != nullptr) {
            // Process message
            messages.erase(messages.begin());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
}
