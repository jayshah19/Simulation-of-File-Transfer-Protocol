


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



void LIST_Command(int controlSocket) 
{
    char pathName[MAX_SIZE];
    char tempStr[MAX_SIZE];
    struct stat statBuf;
    struct dirent *dirp;
    DIR *dp;
    int fd;
    intmax_t totalSize = 0;

    if (dataSocket == 0 )
    {
        ReplyForPASVSwitch(controlSocket);
        return;

    }
    if (getcwd(pathName, MAX_SIZE - 1) == NULL)
    {
        ReplyForNoCommandPermission(controlSocket);
        return;
    }
    if ( (dp = opendir(pathName)) == NULL)
    {
        ReplyForNoCommandPermission(controlSocket);
    }
    else
    {
        ReplyForASCII(controlSocket, "LIST");
        fd = open_data_connection();
		
        if (!fd) 
		{
            ReplyForUnableToOpenData(controlSocket);
            return;
        }
        while ((dirp = readdir(dp)) != NULL)
        {
            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
                continue;
            if (lstat(dirp->d_name, &statBuf) == 0)
            {
                if (S_ISREG(statBuf.st_mode) && statBuf.st_size != 0)
                {
                   
                    totalSize += (intmax_t)statBuf.st_size;
                   
                }

            }
        }

        char control[100];
        
		sprintf(control, "ls -l -B -h -c %s | tail -n+2 > .Temporary.txt", pathName);
        
		int rs = system(control);
        if (rs < 0) 
		{
            return;
        }
        FILE* f = fopen(".Temporary.txt", "r");
        if (!f) 
		{
            printf("Not the File\n");
        }
        char buffer[MAX_SIZE];
        int n;

        do 
		{
            n = fread(buffer, 1, 8190, f);
            send(fd, buffer, n, 0);

        } while (n > 0);

        fclose(f);
        system("rm .Temporary.txt");

        closedir(dp);
        close(fd);
        if (totalSize != 0 ) ReplyForTransfer(controlSocket, totalSize);
        else ReplyForNoFile(controlSocket);

    }
}