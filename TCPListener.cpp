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
    }

    // Zero master fd
    FD_ZERO(&l_master);

    // Add listening socket to master fd list
    // so we can 'hear' incoming connections to it
    FD_SET(l_socket, &l_master);

    return 0;
}

int TCPListener::run() {
    bool running = true;


    while (running) {
        // Make copy to master fd set
        // bc call to select() is _DESTRUCTIVE_
        // There can be many sockets accepting inbound conn reqs/msgs
        // when passed into select() it returns ONLY the client sending a msg at that time
        // all other sockets would have been lost if we passed the original master fd set
        // and not the copy
        fd_set read_fds = l_master;

        // see who's talking to us
        int socketCount = select(0, &read_fds, nullptr, nullptr, nullptr);

        int sock;
        for (int i = 0; i < socketCount; i++) {
            sock = read_fds.fd_array[i];

            // is conn inbound?
            if (sock == l_socket) {
                int client = accept(l_socket, nullptr, nullptr);

                // add conn to set of connected clients
                FD_SET(client, &l_master);

                clientConnect(client);

                // send msg to client
                sendToClient(client, "Hello", 5);
            } else {
                // inbound msg
                char buf[4096]; // hardcode max bytes buffer caan hold
                memset(buf, 0, 4096);

                // Receive msg into buffer
                int bytesRecv = recv(sock, buf, 4096, 0);
                if (bytesRecv <= 0) {
                    // Client has dropped conn
                    clientDisconnect(sock);
                    close(sock);
                    // remove from set
                    FD_CLR(sock, &l_master);
                } else {
                    onMessageReceived(sock, buf, bytesRecv);
                    // Check if msg is aa command
                    // if (buf[0] == '\\') {
                    //     // Is cmd quit?
                    //     string cmd = string(buf, bytesRecv);
                    //     if (cmd == "\\quit") {
                    //         running = false;
                    //         break;
                    //     }

                    // }

                    // // Send msg to all other clients excluding sender (listening sock)
                    // int outSock;
                    // for (int i = 0; i < l_master.fd_count; i++) {
                    //     outSock = l_master.fd_array[i];

                    //     if (outSock != l_socket && outSock != sock) {}
                    // }
                }
            }
        }
    }

    // Remove listening socket from maaster fd set
    // close it so no one else can connect
    FD_CLR(l_socket, &l_master);
    close(l_socket);

    int sock;
    while (l_master.fd_count > 0) {
        sock = l_master.fd_array[0];

        FD_CLR(sock, &l_master);
        close(sock);
    }
}

// handler for client connections
void TCPListener::sendToClient(int clientSock, const char* msg, int msgLen) {
    send(clientSock, msg, msgLen, 0);
}

// handler for client disconnections
void TCPListener::broadcastToClients(int sendingClient, const char* msg, int msgLen) {
    int outSock;
    for (int i = 0; i < l_master.fd_count; i++) {
        outSock = l_master.fd_array[i];

        if (outSock != l_socket && outSock != sendingClient) {
            sendToClient(outSock, msg, msgLen);
        }
    }
}

void TCPListener::clientConnect(int clientSock) {}

void TCPListener::clientDisconnect(int clientSock) {}

void TCPListener::onMessageReceived(int clientSock, const char* msg, int msgLen) {}