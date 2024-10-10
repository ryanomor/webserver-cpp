#include "MultiClient.h"
// #include <iostream>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <netdb.h>
// #include <string.h>
// #include <string>

// .h are from C lib

// using namespace std;

void main() {
    MultiClient mc("0.0.0.0", 54000);

    if (mc.init() != 0) {
        return;
    }

    mc.run();
    system("pause");
}

// int main(int argc, char const *argv[])
// {
//     // create a socket
//     int listening = socket(AF_INET, SOCK_STREAM, 0);
//     if (!listening) {
//         cerr << "Failed to create socket" << endl;
//         return -1;
//     }

//     // biind socket to an IP / port
//     // set up server address struct
//     // AF_INET - IPv4
//     // 54000 - port
//     // 0.0.0.0 - listen on any available network interface
//     sockaddr_in hint;
//     socklen_t hintSize = sizeof(hint);
//     hint.sin_family = AF_INET;
//     hint.sin_port = htons(54000);
//     inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

//     if (bind(listening, (sockaddr *)&hint, hintSize) == -1) {
//         cerr << "Failed to bind to IP/port" << endl;
//         return -2;
//     }

//     // mark socket for listening for connections
//     if (listen(listening, SOMAXCONN) == -1) {
//         cerr << "Failed to listen" << endl;
//         return -3;
//     }

//     // accept connections
//     sockaddr_in client;
//     socklen_t clientSize = sizeof(client);
//     char host[NI_MAXHOST];
//     char svc[NI_MAXSERV];

//     int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
//     if (clientSocket == -1) {
//         cerr << "Failed to connect client to socket" << endl;
//         return -4;
//     }

//     // close socket
//     close(listening);

//     memset(host, 0, NI_MAXHOST);
//     memset(svc, 0, NI_MAXSERV);

//     int result = getnameinfo((sockaddr *)&client, clientSize, host, NI_MAXHOST, svc, NI_MAXSERV, 0);

//     if (result) {
//         cout << host << " connected on port " << svc << endl;
//     } else {
//         // address to string. In  this case, 
//         // client.sin_addr to string
//         // this will go to the host
//         // max buffer in socket is NI_MAXHOST
//         inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
//         cout << host << " connected on " << ntohs(client.sin_port) << endl;
//     }
//     // when receiving,  display msg, echo msg
//     char buf[4096];
//     while (true) {
//         // clear buffer of anything in it before we read
//         memset(buf, 0, 4096);
//         // receive message
//         int bytesRecv = recv(clientSocket, buf, 4096, 0);
//         if (bytesRecv == -1) {
//             cerr << "Error in recv()" << endl;
//             break;
//         }
//         if (bytesRecv == 0) {
//             cout << "Connection closed" << endl;
//             break;
//         }

//         cout << "Received " << string(buf, 0, bytesRecv) << endl;
//         // echo message back to client
//         send(clientSocket, buf, bytesRecv + 1, 0);
//     }

//     // close socket
//     close(clientSocket);

//     return 0;
// }
