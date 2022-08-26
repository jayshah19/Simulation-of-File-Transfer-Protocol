

// ASP PROJECT: SIMULATION OF FTP PROTOCOL

// SECTION-2

// JAY PARESHKUMAR SHAH (110072802)
// MANSI MITESHKUMAR SHAH (110073005)



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>

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



int main(int argc, char **argv) 
{
    int listenfd, controlSocket;    //Used For Sockets
    uint16_t PredefinedPortNumber = atoi(PORT);
    enum states state;
	
    paramerterChecker(argc);
	
	listenfd = createServer(PredefinedPortNumber);
    
	
	if (!listenfd) 
	{
        printf("\n Unable to Create Server\n\n");
		printf("\nPlease Try Again\n\n");
		exit(1);
    }
	
	printf("\nServer Created\n");
	printf("\nServer Port Number: %d\n",PredefinedPortNumber);
    printf("\nServer is Waiting For Clients\n");


    for ( ; ; )
    {

        int pid;
		state = NotConnected;

        if ((controlSocket = accept(listenfd, (struct sockaddr*) NULL, NULL)) < 0)
        {
            perror("[Error]:  Unable to call accept().");
            exit(8);
        }
        
		ReplyForConEstablished(controlSocket);
        state = Connected;

        pid = fork();
	
	
		
		if (pid == 0)  // This is the client process
		{
            close(listenfd);
            doProcessing(controlSocket, &state);
            exit(0);
        }
		
		else if (pid < 0) //Error Condition
		{
            perror("[Error]: on fork");
            exit(1);
        }
		
		else 
		{
			close(controlSocket);
		}
		

    }

    close(dataSocket);
    close(listenfd);
    return 0;
}


