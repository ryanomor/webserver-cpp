#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
// #include <WS2tcpip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <sstream>
/**
 * Virtual class actual TCPListener
 * will use definitions from
 * */ 
class TCPListener {
    public:
        // Constructor
        TCPListener(const char* ipAddress, int port):
            m_ipAddress(ipAddress), m_port(port) {}

        // Initiliaze listener
        int init();

        // Run listener
        int run();

    protected:

    private:
        int m_port;               // Port # for web service
        int m_socket;             // Listening socket's internal file descriptor
        const char* m_ipAddress;  // IP Address server will run on
};