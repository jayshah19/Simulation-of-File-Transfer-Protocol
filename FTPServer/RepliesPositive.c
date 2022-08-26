

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

//=========== Functions For Positive Reply From Server ===============


void ReplyForASCII(int controlSocket, char *file) 
{
    char tempStr[MAX_SIZE];
    snprintf(tempStr, MAX_SIZE - 1, "Reply [150]: Opening ASCII mode data connection for : %s \r\n", file);
    write_message(controlSocket, tempStr);
	
}

void ReplyForTransfer(int controlSocket, int numBytes) {
    char tempStr[MAX_SIZE];
    snprintf(tempStr, MAX_SIZE - 1, "Reply [226]: Transfer complete (%d) Bytes, Closed data connection.\r\n", numBytes);
    write_message(controlSocket, tempStr);
}

void ReplyForCmdOk(int controlSocket) {
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [200]: Command okay.\r\n");
    write_message(controlSocket, tempStr);
}

void ReplyForCmdSuccessful(int controlSocket, char *cmd) 
{
    char tempStr[MAX_SIZE];
    snprintf(tempStr, MAX_SIZE - 1, "Reply [250]: %s Command successful.\r\n", cmd);
    write_message(controlSocket, tempStr);
}

void ReplyForConEstablished(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    snprintf(tempStr, MAX_SIZE - 1, "Reply [220]: Connecting To FTP Server\r\n");
    write_message(controlSocket, tempStr);
}

void ReplyForHelp(int controlSocket, char *cmd) 
{

    if (!strcmp(cmd, ""))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]: The Commands Are:\n"
               "USER\tPASS\tCWD\tCDUP\tQUIT\tPASV\tRETR\tTYPE\tREIN\nSYST\tSTOR\tMKD\tPWD\tLIST\tPORT\tHELP\tNOOP\tRWD\n"
               "Reply [200]: Command okay.\r\n");
        write_message(controlSocket, tempStr);
        return;
    }
    if(!strcasecmp(cmd, "USER"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: USER <SP> Username <CRLF>.\n");
        
		write_message(controlSocket, tempStr);
    }
    
	else if (!strcasecmp(cmd, "PASS"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: PASS <SP> Password <CRLF>.\n"
               "Reply [214]:-After sending the USER command\n"
               "Reply [214]: Send this command to complete the login process.\r\n");
        write_message(controlSocket, tempStr);
    }
    else if (!strcasecmp(cmd, "CDUP"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: CDUP <CRLF>.\n"
               "Reply [214]: Makes the parent of the current directory be the current directory.\r\n");
        write_message(controlSocket, tempStr);
    }
	
	else if (!strcasecmp(cmd, "CWD"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: CWD <SP> Path <CRLF>.\n"
               "Reply [214]: Makes the given directory be the current directory on the remote host.\r\n");
        write_message(controlSocket, tempStr);
    }
   
   else if (!strcasecmp(cmd, "PASV"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: PASV <CRLF>.\n");
        write_message(controlSocket, tempStr);
    }
    
	else if (!strcasecmp(cmd, "TYPE"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: TYPE <SP> Type-Character <CRLF>.\n");
        write_message(controlSocket, tempStr);
    }
	else if (!strcasecmp(cmd, "QUIT"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: QUIT <CRLF>.\n"
               "Reply [214]: Terminates the command connection.\r\n");
        write_message(controlSocket, tempStr);
    }
    
	else if (!strcasecmp(cmd, "LIST"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: LIST <CRLF>.\n"
               "Reply [214]: Sends information about each file in the current directory\r\n");
        write_message(controlSocket, tempStr);
    }
    else if (!strcasecmp(cmd, "HELP"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: HELP [<SP> Command] <CRLF>.\n"
               "Reply [214]:-If a command is given, returns help on that command\n"
               "Reply [214]: Otherwise, returns general help for the FTP server\r\n");
        write_message(controlSocket, tempStr);
    }
	
	else if (!strcasecmp(cmd, "SYST"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: SYST <CRLF>.\n"
               "Reply [214]: Return system type .\r\n");
        write_message(controlSocket, tempStr);
    }
    
    else if (!strcasecmp(cmd, "RETR"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: RETR <SP> File-name <CRLF>.\n"
               "Reply [214]: Begins transmission of a file from the remote host\r\n");
        write_message(controlSocket, tempStr);
    }
    
    else if (!strcasecmp(cmd, "STOR"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: STOR <SP> File-name <CRLF>.\n"
               "Reply [214]: Begins transmission of a file to the remote site\r\n");
        write_message(controlSocket, tempStr);
    }
    else if (!strcasecmp(cmd, "MKD"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: MKD <SP> Directory-name <CRLF>.\n"
               "Reply [214]: Creates the named directory on the remote host.\r\n");
        write_message(controlSocket, tempStr);
    }
    else if (!strcasecmp(cmd, "PWD"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: PWD <CRLF>.\n"
               "Reply [214]: Returns the name of the current directory on the remote host.\r\n");
        write_message(controlSocket, tempStr);
    }
    
    else if (!strcasecmp(cmd, "NOOP"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: NOOP <CRLF>.\n"
               "Reply [214]: Does nothing except return a response\r\n");
        write_message(controlSocket, tempStr);
    }
	
	
	else if (!strcasecmp(cmd, "REIN"))
    {
        char tempStr[MAX_SIZE];
        strcpy(tempStr, "Reply [214]:-Syntax: NOOP <CRLF>.\n"
               "Reply [214]: Does nothing except return a response\r\n");
        write_message(controlSocket, tempStr);
    }
	
	
    else
    {
        char tempStr[MAX_SIZE];
        snprintf(tempStr, MAX_SIZE - 1, "Reply [502]: Unknown command %s.\r\n", cmd);
        write_message(controlSocket, tempStr);
    }
}

void ReplyForPASVSwitch(int controlSocket) 
{
    char tempStr[MAX_SIZE];
    strcpy(tempStr, "Reply [500]: Command unrecognized,Try switching to passive mode by using PASV Command.\r\n");
    write_message(controlSocket, tempStr);
}