
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



//Check Directory
boolean check_directory(char command[])
{

	int file;
	
	char filename[MAX_LENGTH];
	
	boolean has_access = TRUE;

	GET_File(command, filename);

	//read the file
	file = open(filename, O_RDONLY);
	
	if (file == -1) //Error Condition
	{
		perror("ERROR> Requested action not taken ");
		
		close(file);
		
		has_access = FALSE;

	}

	return has_access;
}
