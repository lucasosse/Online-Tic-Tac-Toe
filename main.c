#include <stdio.h>
#include <stdlib.h>
#include "inc/rede.h"

int main(int argc, char *argv[])
{
    int sock = -1;
    if(argv[1][0] == '1')
    {
        sock = socket_host_game("127.0.0.1");
        socket_receive(&sock, "127.0.0.1");
    }
    else
    {
        sock = socket_connect("127.0.0.1");
        socket_send(&sock, "127.0.0.1", 0, 0);
    }
    if(sock != -1) printf("SUCCESS!\n");
    else printf("ERROR!\n");

    socket_destroy(&sock);
    return 0;
}
