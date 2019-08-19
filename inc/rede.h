#ifndef REDE_H
    #define REDE_H
        #include "tabuleiro.h"

        #ifdef _WIN32
            #include <winsock2.h>
            #include <ws2tcpip.h>

            SOCKET socket_host_game(const char *address);
            SOCKET socket_connect_game(const char *address);
            int socket_send(SOCKET *socket_fd, const char *to_address, unsigned short x, unsigned short y);
            int socket_receive(SOCKET *socket_fd, const char *from_address, char *recv_buffer);
            void socket_destroy(SOCKET *socket_fd);
        #else
            int socket_host_game(const char *address);
            int socket_connect_game(const char *address);
            int socket_send(int *socket_fd, const char *to_address, unsigned short x, unsigned short y);
            int socket_receive(int *socket_fd, const char *from_address, char *recv_buffer);
            void socket_destroy(int *socket_fd);
        #endif
#endif
