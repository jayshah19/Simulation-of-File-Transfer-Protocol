


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


void SYST_Command(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [215]: Linux system.\r\n");
    write_message(controlSocket, tempStr);
}
