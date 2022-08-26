

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



int main(int argc, char *argv[])
{

	int controlSocket;
	char *ip = argv[1];
	
	boolean has_quit = 0;


	clientparamerterChecker(argc);

	controlSocket = CreateSocketClient(PORT, ip);

	//Untile QUIT command Clint will send command as a request to server and server response it as reply
	
	
	while (has_quit == FALSE) 
	{

		char command[MAX_LENGTH];
		char command_temp[MAX_LENGTH];
		
		printf("\nFTP Client-> ");
		
		fgets(command, MAX_LENGTH, stdin);	//Taking input from user
		
		strcat(command, "\r\n");
		strcpy(command_temp, command);
		
		boolean has_access = TRUE;

		
		//STOR Command
		if (strncmp("STOR", command, 4) == 0) 
		{
			has_access = check_directory(command_temp);
		}


		if (has_access == TRUE) 
		{

			//Send command to server
			if (write(controlSocket, command, strlen(command)) < 0) 
			{
				perror("\n[Error]: write()");
				exit(1);
			}

			char response[MAX_LENGTH];
			
			//Read response from server
			Read_Res(controlSocket, response);

			
			//PASV Mode (passive mode)
			if (strncmp("227", response, 3) == 0) 
			{
				PASV_Process(response);
			}
			
			//If user enters RETR, LIST or STOR
			if (!strncmp("150", response, 3) && (!strncasecmp("LIST", command, 4)) )
			{

				CREATE_ConncetData(command, ip);
				Read_Res(controlSocket, response);

			}
			
			if (!strncmp("150", response, 3) && (!strncasecmp("STOR", command, 4) )) 
			{

				CREATE_ConncetData(command, ip);
				Read_Res(controlSocket, response);

			}
			if (!strncmp("150", response, 3) && (!strncasecmp("RETR", command, 4) )) 
			{

				CREATE_ConncetData(command, ip);
				Read_Res(controlSocket, response);

			}
			
			//Quit Command
			if (strncasecmp("QUIT", command, 4) == 0) 
			{
				has_quit = TRUE;
			}


		}
	}


	//After client Send QUIT Command
	printf("\n\nProcessing complete\n\n");
	exit(0);
}

/*
void LIST_Process(int sock_data)
{

	//read the data from the server
	char list[MAX_LENGTH];
	int n;
	
	while ((n = read(sock_data, list, MAX_LENGTH - 1))) 
	{

		list[n] = '\0';
		fprintf(stderr, "%s", list);
	}
}

*/
