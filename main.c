#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <iphlpapi.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "inc/rede.h"

int main(int argc, char *argv[])
{
    #ifdef _WIN32
        SOCKET sock = INVALID_SOCKET;
    #else
        int sock = -1;
    #endif
    if(argv[1][0] == '1')
    {
        sock = socket_host_game("127.0.0.1");
        printf("WAITING FOR DATA...\n");
        socket_receive(&sock, "127.0.0.1");
    }
    else
    {
        sock = socket_connect_game("127.0.0.1");
        socket_send(&sock, "127.0.0.1", 0, 0);
    }
    if(sock != -1) printf("SUCCESS!\n");
    else printf("ERROR!\n");

    socket_destroy(&sock);
    return 0;
}
