#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/menu.h"

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls");
    SOCKET sock = INVALID_SOCKET;
#endif

#ifdef __linux__
    #define CLEAR_SCREEN() system("clear");
    int sock = -1;
#endif

void menu_init()
{
    char opt = 0x00;
    CLEAR_SCREEN();
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\t\tOnline Tic Tac Toe \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");

    printf("\n\t\t[1] Host a game");
    printf("\n\t\t[2] Connect to a game");
    printf("\n\t\t[3] Quit");
    printf("\n\t\t-> ");

    scanf("%c", &opt);

    switch (opt)
    {
        case 0x31:
            menu_host_game();
            break;

        case 0x32:
            menu_connect_game();
            break;

        case 0x33:
            exit(0);
            break;

        default:
            printf("Choose a valid option!\n");
            break;
    }
}

void menu_host_game()
{
    char conf_ip = 0x32, in_game = 0x00;
    char host_addr[16], recv_buffer[256];
    memset(host_addr, 0, sizeof(host_addr));
    memset(recv_buffer, 0, sizeof(recv_buffer));

    while(conf_ip == 0x32) // While is not confirm the ip address (conf_ip == 2)
    {
        CLEAR_SCREEN();
        printf("####################################################\n");
        printf("####################################################\n");
        printf("# \t\t\t\t\t\t   #");
        printf("\n#\t\tHost a game \t\t\t   #\n# \t\t\t\t\t\t   #\n");
        printf("####################################################\n");
        printf("####################################################\n");

        printf("\n\tType the IP Address of the host");
        printf("\n\t-> ");

        scanf("%s", host_addr);

        CLEAR_SCREEN();
        printf("####################################################\n");
        printf("####################################################\n");
        printf("# \t\t\t\t\t\t   #");
        printf("\n#\t\tHost a game \t\t\t   #\n# \t\t\t\t\t\t   #\n");
        printf("####################################################\n");
        printf("####################################################\n");

        printf("\n\tIs the %s the correct IP Address?", host_addr);
        printf("\n\t[1] Yes");
        printf("\n\t[2] No");
        printf("\n\t-> ");

        scanf(" %c", &conf_ip);
    }

    sock = socket_host_game(host_addr);
    in_game = 0x01;
    printf("Waiting for a player...\n");
    while(in_game)
    {
        socket_receive(&sock, NULL, recv_buffer);
    }
    socket_destroy(&sock);
}

void menu_connect_game()
{

}
