#ifdef _WIN32
    #define _WIN32_WINNT 0x0501
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "inc/rede.h"

const char *port = "8888";
char buffer[256];

#ifdef _WIN32
    WSADATA wsaData;
    int result = -1;
#endif

#ifdef __linux__
    #include <sys/socket.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>

    #define INVALID_SOCKET -1
#endif

#ifdef _WIN32
    SOCKET socket_host_game(const char *host_address)
#else
    int socket_host_game(const char *host_address)
#endif
{
    #ifdef _WIN32
        SOCKET sock = INVALID_SOCKET;
        if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        {
            printf("FAILED TO INITIATE WSADATA\n");
            WSACleanup();
            return -1;
        }
    #else
        int sock = -1;
    #endif
    struct addrinfo hints, *s_address = NULL;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    if(getaddrinfo(host_address, port, &hints, &s_address) == 0)
    {
        sock = socket(s_address->ai_family, s_address->ai_socktype, s_address->ai_protocol);
        if(sock != INVALID_SOCKET)
        {
            if(bind(sock, s_address->ai_addr, s_address->ai_addrlen) == -1)
            {
                perror("BIND ERROR: ");
            }
        }
        else
        {
            perror("THE SOCKET COULDN'T BE CREATED: ");
        }
    }
    else
    {
        printf("ERROR ON RETRIEVE INFORMATION FROM ADDRESS\n");
    }

    freeaddrinfo(s_address);
    return sock;
}

#ifdef _WIN32
    SOCKET socket_connect_game(const char *host_address)
#else
    int socket_connect_game(const char *host_address)
#endif
{
    #ifdef _WIN32
        SOCKET sock = INVALID_SOCKET;
        if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        {
            printf("FAILED TO INITIATE WSADATA\n");
            WSACleanup();
            return -1;
        }
    #else
        int sock = -1;
    #endif
    struct addrinfo hints, *c_address = NULL;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    if(getaddrinfo(host_address, port, &hints, &c_address) == 0)
    {
        sock = socket(c_address->ai_family, c_address->ai_socktype, c_address->ai_protocol);
        if(sock == INVALID_SOCKET)
        {
            perror("ERROR ON CLIENT DESCRIPTOR: ");
        }
    }

    freeaddrinfo(c_address);
    return sock;
}

#ifdef _WIN32
    int socket_send(SOCKET *socket_fd, const char *to_address, unsigned short x, unsigned short y)
#else
    int socket_send(int *socket_fd, const char *to_address, unsigned short x, unsigned short y)
#endif
{
    struct addrinfo hint, *socketinfo = NULL;
    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_family = AF_INET;
    if(getaddrinfo(to_address, port, &hint, &socketinfo) != -1)
    {
        sprintf(buffer, "FRANCIELLE\n /PUT:%dx%d", x, y);
        if(sendto((*socket_fd), buffer, sizeof buffer, 0, socketinfo->ai_addr, socketinfo->ai_addrlen) > -1)
        {
            return 0;
        }
        else
        {
            perror("ERROR ON SEND: ");
            return -1;
        }
    }
    else
    {
        perror("ERROR ON ASSINGN FROM SEND: ");
        return -1;
    }
    freeaddrinfo(socketinfo);
}

#ifdef _WIN32
    int socket_receive(SOCKET *socket_fd, const char *from_address, char *recv_buffer)
#else
    int socket_receive(int *socket_fd, const char *from_address, char *recv_buffer)
#endif
{
    struct addrinfo hints, *remote_addr = NULL;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    if(getaddrinfo(from_address, port, &hints, &remote_addr) == 0)
    {
        if(recvfrom((*socket_fd), buffer, sizeof(buffer), 0, remote_addr->ai_addr, &(remote_addr->ai_addrlen)) > -1)
        {
            if(strcpy(recv_buffer, buffer) != NULL)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            perror("COULDN'T RECEIVE: ");
            return -1;
        }
    }
    else
    {
        printf("ERROR ON ASSINGN FROM RECEIVE\n");
    }
    freeaddrinfo(remote_addr);
}

#ifdef _WIN32
    void socket_destroy(SOCKET *socket_fd)
#else
    void socket_destroy(int *socket_fd)
#endif
{
    if(socket_fd != NULL)
    {
        #ifdef _WIN32
            WSACleanup();
            closesocket(*socket_fd);
        #else
            close((*socket_fd));
        #endif
    }
}
