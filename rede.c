#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "inc/rede.h"

const unsigned short port = 8888;
char buffer[256];

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib,"ws2_32.lib")

#endif

#ifdef __linux__
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <arpa/inet.h>

#endif

int socket_host_game(const char *host_address)
{
    int sock = -1;
    struct sockaddr_in server_addr;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1)
    {
        perror("THE SOCKET COULDN'T BE CREATED: ");
    }
    else
    {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, host_address, &(server_addr.sin_addr));
        if(bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
        {
            perror("BIND ERROR: ");
        }
    }

    return sock;
}

int socket_connect(const char *host_address)
{
    ssize_t bytes_sended = 0;
    int sock = -1;
    struct sockaddr_in client_addr;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock != -1)
    {
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(port);
        if(inet_pton(AF_INET, host_address, &(client_addr.sin_addr)) == -1)
        {
            perror("ERROR ON ASSIGN STRUCT: ");
        }
    }
    else
    {
        perror("SOCKET COULDN'T CONNECTO TO HOST: ");
    }

    return sock;
}

int socket_send(int *socket_fd, const char *to_address, unsigned short x, unsigned short y)
{
    ssize_t bytes_sended = 0;
    int rv = 0;
    struct addrinfo hint, *socketinfo;
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_protocol = IPPROTO_UDP;
    rv = getaddrinfo(to_address, "8888", &hint, &socketinfo);
    if(rv != -1)
    {
        sprintf(buffer, "%dx%d", x, y);
        bytes_sended = sendto((*socket_fd), buffer, sizeof buffer, 0, socketinfo->ai_addr, socketinfo->ai_addrlen);
        if(bytes_sended != -1)
        {
            printf("SENDED!\n");
        }
        else
        {
            perror("ERROR ON SEND: ");
        }
    }
    else
    {
        perror("ERROR ON ASSINGN FROM SEND: ");
    }
}

int socket_receive(int *socket_fd, const char *from_address)
{
    socklen_t fromlen;
    ssize_t bytes_received = 0;
    struct sockaddr_in remote_addr;
    printf("RECEIVING DATA...\n");
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, from_address, &(remote_addr.sin_addr)) != -1)
    {
        bytes_received = recvfrom((*socket_fd), buffer, sizeof buffer, 0, (struct sockaddr *) &remote_addr, &fromlen);
        if(bytes_received > 0)
        {
            printf("BUFFER RECEIVED: %s\n", buffer);
        }
        else
        {
            perror("COULDN'T RECEIVE: ");
        }
    }
    else
    {
        perror("ERROR ON ASSINGN FROM RECEIVE: ");
    }
}

void socket_destroy(int *socket_fd)
{
    if(socket_fd != NULL)
    {
        close((*socket_fd));
    }
}
