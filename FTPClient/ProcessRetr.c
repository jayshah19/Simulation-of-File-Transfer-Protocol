

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




//RETR Command
void RETR_Process(char command[], int sock_data)
{

	int file;
	int bytes_received = 0;
	char temp[MAX_LENGTH];
	char filename[MAX_LENGTH];
	int n;

	GET_File(command, filename);
	
	//Creating a new file
	if (strncasecmp(command, "RESM", 4)) 
	{
		file = open(filename, O_WRONLY | O_CREAT, S_IRWXU);
	}
	
	else 
	{
		setenv("SOMEVAR", filename, 1); // Creating a  environment variable
		
		system("perl -pi -e 'chomp if eof' $SOMEVAR"); // Pass this variable in this command
		
		file = open(filename, O_APPEND | O_RDWR);
		
		//unsetenv("SOMEVAR"); // Clear that variable (optional)
	}

	if (file == -1) 
	{
		perror("[Error]:  Unable to open file");
	}

	//read data in from server and write these into new file
	n = read(sock_data, temp, MAX_LENGTH);
	
	while (n > 0) 
	{
		bytes_received += n;
		write(file, temp, n);
		n = read(sock_data, temp, MAX_LENGTH);
	}
	
	if (n == 0) 
	{
		close(file);
		close(sock_data);
	}
	
	else if (n < 0) 
	{
		fprintf(stderr, "[Error]:  Unable to read()");
	}
}
