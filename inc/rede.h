#ifndef REDE_H
    #define REDE_H
        #include "tabuleiro.h"

        int socket_host_game(const char *host_address);
        int socket_connect(const char *host_address);
        int socket_send(int *socket_fd, const char *to_address, unsigned short x, unsigned short y);
        int socket_receive(int *socket_fd, const char *from_address);
        void socket_destroy(int *socket_fd);
#endif
