


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



void CDUP_Command(int controlSocket) 
{
    // The Parent Directory
    char cwd[1024];
    
	if (chdir("..") == 0) 
	{
        ReplyForCmdSuccessful(controlSocket, "CDUP");
    }
    
	else 
	{
        ReplyForFileNotFound(controlSocket);
    }
}
