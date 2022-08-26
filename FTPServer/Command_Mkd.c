
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




void MKD_Command(int controlSocket, char *dir) {
    int i;
    char dirname[50];
    strcpy(dirname, dir);
    if ((mkdir(dirname, 00777)) == -1) 
	{
        // Equivalent of 00777 = rwxrwxrwx
        ReplyForNoCommandPermission(controlSocket);
        return;
    }
    else 
	{
        long size;
        char *buf, *ptr, tempStr[MAX_SIZE];
        char path[_PC_PATH_MAX] ;
        snprintf(path, _PC_PATH_MAX , "./%s", dirname);
        size = pathconf(path, _PC_PATH_MAX);
        if ((buf = (char *)malloc((size_t)size)) != NULL)
            ptr = getcwd(buf, (size_t)size);
        snprintf(tempStr, MAX_SIZE - 1, "Reply [257]: File Created \"%s\".\r\n", ptr);
        write_message(controlSocket, tempStr);
    }
}
