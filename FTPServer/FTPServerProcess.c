


// ASP PROJECT: SIMULATION OF FTP PROTOCOL

// SECTION-2

// JAY PARESHKUMAR SHAH (110072802)
// MANSI MITESHKUMAR SHAH (110073005)



#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>
#include <netinet/in.h>

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


int doProcessing(int controlSocket, enum states *ptrState) 
{
    int datafd;
    char cmdstring[MAX_SIZE];
    char *word, *filenm;
    char command[MAX_SIZE];
    char arg[MAX_SIZE];
    int n;

    for ( ; ; )
    {
        //Command Read
        n = read(controlSocket, cmdstring, MAX_SIZE - 1); 

        if (n == 0)
        {
            fprintf(stderr, "Client disconnected.\n");
            close(controlSocket);
            return 0;

        }
        cmdstring[n] = '\0';
        
        word = strtok(cmdstring, SEPCHARS);
        
		if (word == NULL) //Error condition
        {
            fprintf(stderr, "[Error]: , no command given\n");
            ReplyForNoCommand(controlSocket);
            continue;
        }

        strncpy(command, word, MAX_SIZE);

        int Cdata = 0;
		
        if (!strncasecmp(command, "RESM", 4)) 
		{
			Cdata = 1;
		}
        
		word = strtok(NULL, SEPCHARS);
        
		if (word == NULL)
        {
            strncpy(arg, "", MAX_SIZE);
        }
        
		else
        {
            strncpy(arg, word, MAX_SIZE);
        }
        
		if (Cdata) 
		{
            filenm = (char *)malloc(sizeof(char) * MAX_SIZE);
            word = strtok(NULL, SEPCHARS);
            strncpy(filenm , word, MAX_SIZE);
        }
       
		
		fprintf(stderr, "\nClient:");
		
		fprintf(stderr, "Typed Command: %s\t", command);
        
		fprintf(stderr, "\tTyped Arg: %s", arg);
        
		
		if (Cdata) 
		{
            fprintf(stderr, "filename:%s,length:%d\n\n", filenm, strlen(filenm));
            char *arg2 = (char *)malloc(sizeof(char) * MAX_SIZE);
            snprintf(arg2, MAX_SIZE, "%s %s", arg, filenm);
            strcpy(arg, arg2);
        }
        else 
		{
			printf("\n");
		}


        if (strncasecmp("QUIT", command, 4) == 0)
        {
            QUIT_Command(controlSocket, ptrState);
            
			close(controlSocket);
            return 0;
        }
		
		if (strncasecmp("REIN", command, 4) == 0)
        {
                REIN_Command(controlSocket, ptrState);
				
				close(controlSocket);
				return 0;
        }

        switch (*ptrState)
        {
        
		
		case Connected :
		//For Connection Establish between Client and server
            
			if ((strlen(command) == 4) && (strncasecmp("USER", command, 4) == 0)) //COMMAND USER
            {
                USER_Command(arg, ptrState, controlSocket);
            }
            
			else if ((strlen(command) == 4) && (strncasecmp("PASS", command, 4) == 0)) //COMMAND PASS
            {
                PASS_Command(arg, ptrState, controlSocket);
            }
            
			else 
            {
                ReplyForNotLogged(controlSocket);

            }

            break;

        
		
		
		case Password_Check:
		//Password Check
            
			if ((strlen(command) == 4) && (strncasecmp("PASS", command, 4) == 0)) 
            {
                PASS_Command(arg, ptrState, controlSocket);
            }
            
			else if ((strlen(command) == 4) && (strncasecmp("USER", command, 4) == 0)) 
            {
                USER_Command(arg, ptrState, controlSocket);
            }
            
			else
            {
                ReplyForNotLogged(controlSocket);
            }

            break;

        
		
		case Login:
		//After Login User Can Perform Diffrent Type Of Commands			
		
            if ((strlen(command) == 4) && (strncasecmp("LIST", command, 4) == 0) )
            {
                LIST_Command(controlSocket);

            }
            
			else if ((strlen(command) == 4) && (strncasecmp("USER", command, 4) == 0))
            {
                ReplyForNoImplementationOfSuperflous(controlSocket);
            }
            
			
			else if ((strlen(command) == 4) && (strncasecmp("PASS", command, 4) == 0))                                      
            {
                ReplyForNoImplementationOfSuperflous(controlSocket);
            }
			
			
			else if ((strlen(command) == 4) && (strncasecmp("SYST", command, 4) == 0))
            {
                SYST_Command(controlSocket);

            }
			
			
			else if ((strlen(command) == 3) && (strncasecmp("PWD", command, 3) == 0))
            {
                PWD_Command(controlSocket);

            }
            
			
			else if ((strlen(command) == 3) && (strncasecmp("MKD", command, 3) == 0))
            {
                MKD_Command(controlSocket, arg);

            }
			
			else if ((strlen(command) == 3) && (strncasecmp("RWD", command, 3) == 0))
            {
                RWD_Command(controlSocket, arg);

            }
			
			else if ((strlen(command) == 4) && (strncasecmp("TYPE", command, 4) == 0))
            {
                TYPE_Command(controlSocket, arg);

            }
            
			else if ((strlen(command) == 3) && (strncasecmp("CWD", command, 3) == 0))
            {
                CWD_Command(controlSocket, arg);

            }
            
            
			else if ((strlen(command) == 4) && (strncasecmp("CDUP", command, 4) == 0))
            {
                CDUP_Command(controlSocket);

            }
			
			
			else if ((strlen(command) == 4) && (strncasecmp("RETR", command, 4) == 0))
            {
                RETR_Command(controlSocket, arg , 0);

            }
           
		   else if ((strlen(command) == 4) && strncasecmp("STOR", command, 4) == 0)
            {
                STOR_Command(controlSocket, arg);
            }
            
			
			else if ((strlen(command) == 4) && strncasecmp("PASV", command, 4) == 0)
            {
                PASV_Command(controlSocket);
            }
            
			
			else if ((strlen(command) == 4) && strncasecmp("NOOP", command, 4) == 0)
            {
                NOOP_Command(controlSocket);
            }
			
			
            else if ((strlen(command) == 4) && strncasecmp("HELP", command, 4) == 0)
            {
                HELP_Command(controlSocket, arg);
            }
           
			/*
			
			else if ((strlen(command) == 3) && (strncasecmp("PORT", command, 3) == 0))
            {
               // port(controlSocket, arg);
			   void PORT_Command(int controlSocket, char *argv[]);
			   //void	port(t_cli *cli);

            }
			
			*/
			
			
			else
            {
                ReplyForUnknownCmd(controlSocket);

            }

		}
	
    }
}


// PORT COMMAND

/*

void PORT_Command(int controlSocket,char *argv[]) 
{
    
    struct sockaddr_in servaddr;
    char tempStr[MAX_SIZE];
    unsigned int ip;
    unsigned short port;
    uint16_t PredefinedPortNumber;
    int len;
	char *newport = argv[1];

    // Data Socket
    dataSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (dataSocket == 1)
    {
        perror("[Error]:  calling socket().");
        exit(8);
    }


    srand(time(NULL));
    PredefinedPortNumber = newport;

    memset(&servaddr, 0, sizeof(servaddr));
    len = sizeof(servaddr);

    getsockname(controlSocket, (struct sockaddr*)&servaddr, &len);
    servaddr.sin_port = htons(PredefinedPortNumber);;


    getsockname(dataSocket, (struct sockaddr*)&servaddr, &len);

   
    ip = ntohl(servaddr.sin_addr.s_addr);
    port = ntohs(servaddr.sin_port);
	//
    //snprintf(tempStr, MAX_SIZE - 1, "Reply [227]: Entering ACTIVE Mode (%d,%d,%d,%d,%d,%d).\r\n",
    //         (unsigned int)((ip >> 24) & 0xff), (unsigned int)((ip >> 16) & 0xff),
    //         (unsigned int)((ip >> 8) & 0xff), (unsigned int)(ip & 0xff),
    //         (unsigned int)(port >> 8), (unsigned int)(port & 0xff));
	//

    printf("Opened passive connection : Ip_address->%s : Port->%d\n", inet_ntoa(servaddr.sin_addr), port);

    write_message(controlSocket, tempStr);
}


*/

 