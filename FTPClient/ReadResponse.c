

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


void Read_Res(int controlSocket, char response[MAX_LENGTH])
{
	
	int n;
	
	//read response from server
	if ((n = read(controlSocket, response, MAX_LENGTH - 1))) 
	{
		response[n] = '\0';
		fprintf(stderr, "%s", response);
	}
	
	if (n < 0) 
	{
		printf("READ ERROR !!%s.\n", strerror(errno));
		exit(8);
	}
	
	if (n == 0) 
	{
		printf("READ ERROR !!%s.\n", strerror(errno));
		exit(0);
	}
	
}