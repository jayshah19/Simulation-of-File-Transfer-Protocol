


// ASP PROJECT: SIMULATION OF FTP PROTOCOL

// SECTION-2

// JAY PARESHKUMAR SHAH (110072802)
// MANSI MITESHKUMAR SHAH (110073005)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


typedef struct Users
{
	char UsrName[300];
	char Pass[300];
	struct Users *next;
} User;



void UserNames(User **r);
int UserNameChecker(char *UsrName, char **CurrentUser);
int UserPasswordChecker(char *UsrName, char *Pass);


void UserAdd(User **r, char *UsrName, char *Pass)
{
    User *user = malloc(sizeof(User));
    
	if (!user)
	{	
		//printf("[Error: Unable to add users ]");
		exit(8);
	}
	
		strcpy(user->UsrName, UsrName);
		strcpy(user-> Pass, Pass);
		user->next = *r;
		*r = user;
	
	
}