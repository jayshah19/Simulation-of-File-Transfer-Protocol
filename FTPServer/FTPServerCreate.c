

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

int dataSocket = 0; //For Data Connection
int count = 0;
char *CurrentUser = NULL; //Current Logged Username


void paramerterChecker(int argc) 
{
    //if user enter any parameters(like; port numberr) with server it will print error here
	//For example ./server 21
	int i = argc;	
	
	if (i > 1 || i < 1)
    {
        fprintf(stderr, "[Error]: Please Use Server Without any Parameters\n");
        exit(8);
    }
	
	
}

int createServer(int PredefinedPortNumber) 
{
    int listenfd;
    
	struct sockaddr_in servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
	if (listenfd == 1)
    {
        perror("[Error]: calling socket().");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PredefinedPortNumber);

    //ERROR CONDITIONS
	
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) 
	{
        perror("[Error]:  calling bind() ");
        return 0;
    }

    if (listen(listenfd, SERV_BACKLOG) < 0)
    {
        perror("[Error]:  calling listen().");
        return 0;
    }

    return listenfd;
}


int open_data_connection() 
{
    int  datafd;
    if ((datafd = accept(dataSocket, (struct sockaddr*) NULL, NULL)) < 0)
    {
        //fprintf("ERROR While Open Data connection.\n\n");
        exit(8);
    }

    fprintf(stderr, "Data connection established.\n\n");
   
    return datafd;
}



void write_message(int controlSocket, char *strMsg) 
{
    //ERROR CONDITIONS
	if ( write(controlSocket, strMsg, strlen(strMsg)) != strlen(strMsg))
    {
		fprintf(stderr, "[Error]:  Unable to write to client..Please Try Again\n");
		
		exit(8);
    }
}



