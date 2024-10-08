#include "TCPListener.h"

int TCPListener::init() {
    // Create socket
    m_socket = socket(AF_INET, SOCK_STREAM,0);
    if (m_socket == -1) {
        perror("Failed to create socket");
        return -1;
    }

    // Bind ip address and port to socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ipAddress, &hint.sin_addr);

    if (bind(m_socket, (sockaddr*) &hint, sizeof(hint)) == -1) {
        perror("Failed to bind socket to port");
        return -2;
    }
}

int TCPListener::run() {}