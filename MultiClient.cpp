#include "MultiClient.h"
#include <string>

void MultiClient::clientConnect(int clientSock) {
    // send msg to connected client
    std::string msg = "Welcome to the Server!";
    sendToClient(clientSock, msg.c_str(), msg.size() + 1);
}

void MultiClient::clientDisconnect(int clientSock) {}

void MultiClient::onMessageReceived(int clientSock, const char* msg, int msgLen) {
    broadcastToClients(clientSock, msg, msgLen);
}