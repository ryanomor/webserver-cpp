#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <string>

// .h are from C lib

using namespace std;

int main(int argc, char const *argv[])
{
    // create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (!listening) {
        cerr << "Failed to create socket" << endl;
        return -1;
    }
    // biind socket to an IP / port
    // mark socket for listening for connections
    // accept connections
    // close socket
    // when receiving,  displaay msg, echo msg
    // close socket
    return 0;
}
