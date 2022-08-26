


// ASP PROJECT: SIMULATION OF FTP PROTOCOL

// SECTION-2

// JAY PARESHKUMAR SHAH (110072802)
// MANSI MITESHKUMAR SHAH (110073005)

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <netdb.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>


#include "FTPClientFunctions.h"

#define MAX_LENGTH 1024
#define SEPCHARS " \t\r\n"
#define PORT "21"



enum BOOLEAN 
{
	FALSE = 0,
	TRUE = 1
};

typedef enum BOOLEAN boolean;

char *dataPort;
char *bytesRead;


void clientparamerterChecker(int argc)
{
	
	if (argc != 2)
	{
		fprintf(stderr, "[ERROR]: Please check ./client <ip_address> and Try Again\n");
		exit(1);
	}
	
}


//Creating The Socket for  Client.
int CreateSocketClient(char *port, char *ipAdd)
{
	int controlSocket;
	struct sockaddr_in address;
	
	
	//create a tcp socket
	if ((controlSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  //Error Condition
	{

		perror("\nError in socket()");
		exit(1);
	}

	//Construct the struct
	memset(&address, 0, sizeof(address));       	
	
	address.sin_family = AF_INET;                  	
	address.sin_addr.s_addr = inet_addr(ipAdd);  	//IP Address
	address.sin_port = htons(atoi(port));       	//Server Port..By default Here i am taking port Number as 21

	char *ip = inet_ntoa(address.sin_addr);

	printf("\nTrying %s ...\n", ip);
	
	
	//Connect to the server
	if (connect(controlSocket, (struct sockaddr *) &address, sizeof(address)) < 0) 
	{
		perror("\nError in connect()");
		exit(1);
	}
	
	char response[MAX_LENGTH];
	
	//Read response from server
	Read_Res(controlSocket, response);
	
	return controlSocket;
}
