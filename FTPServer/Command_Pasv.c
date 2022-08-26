


// ASP PROJECT: SIMULATION OF FTP PROTOCOL

// SECTION-2

// JAY PARESHKUMAR SHAH (110072802)
// MANSI MITESHKUMAR SHAH (110073005)



#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>
#include <netinet/in.h>

#include "FTPServerFunctions.h"


#define SERV_BACKLOG 5
#define PORT "21"
#define MAX_SIZE 1024
#define SEPCHARS " \t\r\n"



enum states //Diffrent User States
{
	Connected, 
	NotConnected, 
	Login, 
	Password_Check
}; 





void PASV_Command(int controlSocket) 
{
    
    struct sockaddr_in servaddr;
    char tempStr[MAX_SIZE];
    unsigned int ip;
    unsigned short port;
    uint16_t PredefinedPortNumber;
    int len;

    // Data Socket
    dataSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (dataSocket == 1)
    {
        perror("[Error]:  calling socket().");
        exit(8);
    }


    srand(time(NULL));
    PredefinedPortNumber = (uint16_t)(rand() % (65530 - 1024) + 1024);

    memset(&servaddr, 0, sizeof(servaddr));
    len = sizeof(servaddr);

    getsockname(controlSocket, (struct sockaddr*)&servaddr, &len);
    servaddr.sin_port = htons(PredefinedPortNumber);;

    if (bind(dataSocket, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) 
	{
        printf("bind() for passive socket FAILED: %s\n", strerror(errno));
        exit(8);
    }
    getsockname(dataSocket, (struct sockaddr*)&servaddr, &len);

    if (listen(dataSocket, SERV_BACKLOG) < 0)
    {
        perror("[Error]:  calling listen().");
        exit(8);
    }
    ip = ntohl(servaddr.sin_addr.s_addr);
    port = ntohs(servaddr.sin_port);

    snprintf(tempStr, MAX_SIZE - 1, "Reply [227]: Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", (unsigned int)((ip >> 24) & 0xff), (unsigned int)((ip >> 16) & 0xff), (unsigned int)((ip >> 8) & 0xff), (unsigned int)(ip & 0xff), (unsigned int)(port >> 8), (unsigned int)(port & 0xff));

    printf("Opened passive connection : Ip_address->%s : Port->%d\n", inet_ntoa(servaddr.sin_addr), port);

    write_message(controlSocket, tempStr);
}