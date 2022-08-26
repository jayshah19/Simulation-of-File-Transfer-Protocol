


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



//  CREATE_ConncetData used when user enter , RETR or STOR commands. It will Creates a data connection 

void CREATE_ConncetData(char command[], char ip[])
{

	int sock_data, rv;
	struct addrinfo hints, *servinfo, *p;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if ((rv = getaddrinfo(ip, dataPort, &hints, &servinfo)) != 0) 
	{
		printf("[Error]: Unable to getaddrinfo\n");
		exit(0);
	}


	for (p = servinfo; p != NULL; p = p->ai_next) 
	{
		if ((sock_data = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
		{
			printf("socket\n");
			continue;
		}

		if (connect(sock_data, p->ai_addr, p->ai_addrlen) <0) 
		{
			close(sock_data);
			perror("[Error]: Unable to Connect");
			continue;
		}
		break;
	}
	if (p == NULL) 
	{
		fprintf(stderr, "[Error]: failed to create socket\n");
		exit(0);
	}

	//STOR command
	if (strncasecmp("STOR", command, 4) == 0) 
	{
		STOR_Process(command, sock_data);

	}

	else if ((strncasecmp("RETR", command, 4) == 0))
	{
		RETR_Process(command, sock_data);
	}

	//LIST command
	else if (strncasecmp("LIST", command, 4) == 0) 
	{
		LIST_Process(sock_data);
	}

	else
	{
		fprintf(stderr, "\n[Error]: Not a valid command.\n\n");
	}
}

