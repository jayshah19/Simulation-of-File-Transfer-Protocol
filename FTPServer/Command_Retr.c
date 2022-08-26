


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



void RETR_Command(int controlSocket, char *filename, intmax_t position) {
    int fd;
    char tempStr[MAX_SIZE];
    int n;
    FILE *filefd;
    struct stat sb;

    if (dataSocket == 0 )
    {
        ReplyForPASVSwitch(controlSocket);
        return;
    }
    if (stat(filename, &sb) == -1)
    {
        ReplyForFileNotFound(controlSocket);
        return;
    }
    
    filefd = fopen(filename, "r");
    if (filefd == 0)
    {
        ReplyForFailToOpen(controlSocket);
        return;
    }
    else
    {
        ReplyForASCII(controlSocket, filename);

    }

    fd = open_data_connection();
    if (!fd) {
        ReplyForUnableToOpenData(controlSocket);
        return;
    }
    fseek(filefd, position, SEEK_SET);
    while ((n = fread(tempStr, 1, MAX_SIZE, filefd)) > 0)
    {
        write(fd, tempStr, n);
    }

    if (n == 0)
    {
        close(fd);
        fclose(filefd);
        if (!position )ReplyForTransfer(controlSocket, sb.st_size);
        else ReplyForTransfer(controlSocket, sb.st_size - position - 1);
    }
    else if (n < 0)
    {
        fprintf(stderr, "[Error]:  reading file.\n");
        exit(8);
    }
}
