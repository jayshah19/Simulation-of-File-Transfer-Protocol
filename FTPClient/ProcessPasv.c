

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





//PASV command Process
void PASV_Process(char *response)
{

	int port;
	char *temp;
	temp = strrchr(response, ',');      // temp = the last occurrence of ',' in reply
	port = atoi(temp + 1);              // port number receive the last number (p2) sent
	*temp = '\0';
	temp = strrchr(response, ',');      // temp will now point to (p1)
	port += atoi(temp + 1) * 256;       // port_num will now be equal to the sent port number from the server
	dataPort = (char *)malloc(sizeof(char) * MAX_LENGTH);
	sprintf(dataPort, "%d", port);
	size_t len = strlen(dataPort);
}
