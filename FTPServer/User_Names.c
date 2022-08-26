
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


void UserAdd(User **r, char *UsrName, char *Pass);
int UserNameChecker(char *UsrName, char **CurrentUser);
int UserPasswordChecker(char *UsrName, char *Pass);

void UserNames(User **r) 
{
    
	UserAdd(r, "aznam", "yacoub");
	UserAdd(r, "jay", "admin");
    UserAdd(r, "mansi", "shah");
    UserAdd(r, "karan", "GA");
    
}
