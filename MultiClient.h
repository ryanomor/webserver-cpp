#pragma once
#include "TCPListener.h"

class MultiClient: public TCPListener {
    public:
        MultiClient(const char* ipAddress, int port):
            TCPListener(ipAddress, port) {}
    
    protected:
        // handler for client connections
        virtual void clientConnect(int clientSock);

        // handler for client disconnections
        virtual void clientDisconnect(int clientSock);

        // Handler for receiving a message from the client
        virtual void onMessageReceived(int clientSock, const char* msg, int msgLen);

    private:
};