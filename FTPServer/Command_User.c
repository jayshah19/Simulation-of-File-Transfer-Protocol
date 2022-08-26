


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




void USER_Command(char *UsrName, enum states *ptrState, int controlSocket) {
    char tempStr[MAX_SIZE];

    if (UserNameChecker(UsrName, &CurrentUser))
    {
        strcpy(tempStr, "Reply [331]: User name is Valid, Now Please Enter Password below.\r\n");
        write_message(controlSocket, tempStr);
        *ptrState = Password_Check;
    }
    else
    {
        if (!strcmp(UsrName, "Professor")) 
		{
            strcpy(tempStr, "Reply [230]: No need a Pass..Welcome Professor..\r\n");
            write_message(controlSocket, tempStr);
            *ptrState = Login;
			
        }
		else if ((!strcmp(UsrName, "AZNAM")))
		{
			strcpy(tempStr, "Reply [230]: WELCOME Professor AZNAM TO OUR SERVER\r\n");
            write_message(controlSocket, tempStr);
            *ptrState = Login;
		}
        else 
		{
            ReplyForNoCommandPermission(controlSocket);
        }
    }
}