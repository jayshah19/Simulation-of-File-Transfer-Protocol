

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




void ReplyForNotLogged(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [530]: User not logged in.\r\n");
    write_message(controlSocket, tempStr);
}

void ReplyForCloseDataConection(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [226]: Close Data Connection.\r\n");
    write_message(controlSocket, tempStr);
}

void ReplyForFailToOpen(controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [550]: Failed to open file.\r\n");
    write_message(controlSocket, tempStr);
}


void ReplyForNoFile(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [550]: No files found.\r\n");
    write_message(controlSocket, tempStr);
}


void ReplyForUnableToOpenData(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [425]: Cannot open data connection.\r\n");
    write_message(controlSocket, tempStr);
}


void ReplyForNoCommandPermission(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [550]: Permission Denied \r\n");
    write_message(controlSocket, tempStr);
}


void ReplyForNoCommand(controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [502]: No command given.\r\n");
    write_message(controlSocket, tempStr);
}


void ReplyForNoImplementationOfSuperflous(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [202]: Command not implemented, superfluous at this site.\r\n");
    write_message(controlSocket, tempStr);
}


void ReplyForFileNotFound(controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [550]: File / Dir unavailable, not found, not accessible.\r\n");
    write_message(controlSocket, tempStr);
}


void ReplyForUnknownCmd(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [502]: Command not implemented.\r\n");
    write_message(controlSocket, tempStr);
}


