

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




//Process of Stor Command
void STOR_Process(char command[], int sock_data)
{

	int file;
	char filename[MAX_LENGTH];
	char temp[MAX_LENGTH];

	GET_File(command, filename);

	//read the file
	file = open(filename, O_RDONLY);
	if (file == -1) 
	{
		perror("[ERROR]: Unable to foolow Requested action ");
		exit(1);
	}


	//read the file line by line 
	
	//send each line to the server
	int byte = read(file, temp, MAX_LENGTH);
	
	while (byte > 0) 
	{

		
		write(sock_data, temp, byte);
		
		byte = read(file, temp, MAX_LENGTH);
	}

	//Close Connection from client
	if (byte == 0) 
	{
		close(file);
		
		close(sock_data);
	}
	
	else if (byte < 0) //Error Condition
	{
		perror("\n[Error]: Unable to read file");
		exit(1);
	}
}
