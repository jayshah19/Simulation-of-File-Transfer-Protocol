
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




void GET_File(char command[], char filename[])
{

	char *word;

	
	word = strtok(command, SEPCHARS);
	
	if (word == NULL) //Error Condition
	{
		perror("\nError in STOR command");
		exit(1);
	}
	
	//Get Filename
	word = strtok(NULL, SEPCHARS);
	
	if (word == NULL) 
	{
		strncpy(filename, "", MAX_LENGTH);
	}
	
	else 
	{
		strncpy(filename, word, MAX_LENGTH);
	}
}
