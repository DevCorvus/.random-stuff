#ifndef UDP_HPP
#define UDP_HPP

#include "game.hpp"
#include <ctime>
#include <functional>

#define BUFFER_SIZE 1024

void *getInAddr(struct sockaddr *sa);

enum MessageType { CONNECT, DISCONNECT, ACTION };

struct Message {
    MessageType type;
    PlayerAction *action;
    std::time_t timestamp;
};

class UDPServer {
    using Callback =
        std::function<void(const char *, int, const struct sockaddr_storage &)>;

  public:
    ~UDPServer();
    void listen(const char *addr, const char *port, Callback cb);
    void send(const char *addr, const char *port, const Message data);

  private:
    int sockfd;
};

#endif
