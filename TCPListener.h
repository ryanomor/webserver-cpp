#pragma once
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