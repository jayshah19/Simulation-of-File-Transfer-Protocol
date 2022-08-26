


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



void STOR_Command(int controlSocket, char *filename) 
{
    int filefd, fd;
    int bytesReceived = 0;
    char tempStr[MAX_SIZE];
    int n;

    if (dataSocket == 0 )
    {
        ReplyForPASVSwitch(controlSocket);
        return;

    }
    
	
	filefd = open(filename, O_WRONLY | O_CREAT, S_IRWXU);
    
	if (filefd < 0)
    {
        ReplyForNoCommandPermission(controlSocket);
        return;
    }
    else
    {

        ReplyForASCII(controlSocket, filename);

    }


    fd = open_data_connection();

    if (!fd) 
	{
        ReplyForUnableToOpenData(controlSocket);
        return;
    }

    n = read(fd, tempStr, MAX_SIZE);

    while (n > 0)
    {
        bytesReceived += n;

        write(filefd, tempStr, n);
        n = read(fd, tempStr, MAX_SIZE);
    }

    if (n == 0)
    {
        close(fd);
        close(filefd);
        ReplyForTransfer(controlSocket, bytesReceived);

    }
    else if (n < 0)
    {
        fprintf(stderr, "[Error]:  reading from socket.\n");
        exit(8);
    }
	
}