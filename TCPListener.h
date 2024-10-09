#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
// #include <WS2tcpip.h>
#include <sys/socket.h>
#include <sys/_select.h>
#include <arpa/inet.h>
#include <unistd.h>
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
            l_ipAddress(ipAddress), l_port(port) {}

        // Initiliaze listener
        int init();

        // Run listener
        int run();

    protected:

    private:
        int l_port;               // Port # for web service
        int l_socket;             // Listening socket's internal file descriptor
        const char* l_ipAddress;  // IP Address server will run on
        fd_set l_master;          // Master file descriptor list
};