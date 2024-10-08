#include "TCPListener.h"

int TCPListener::init() {
    // Create socket
    l_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (l_socket == -1) {
        perror("Failed to create socket");
        return -1;
    }

    // Bind ip address and port to socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(l_port);
    inet_pton(AF_INET, l_ipAddress, &hint.sin_addr);

    if (bind(l_socket, (sockaddr*) &hint, sizeof(hint)) == -1) {
        perror("Failed to bind socket to port");
        return -2;
    }

    // Mark socket for listening in
    if (listen(l_socket, SOMAXCONN) == -1) {
        perror("Failed to listen on socket");
        return -3;
    };
}

int TCPListener::run() {}