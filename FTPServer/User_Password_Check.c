


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
void UserNames(User **r);
int UserNameChecker(char *UsrName, char **CurrentUser);



int UserPasswordChecker(char *UsrName, char *Pass) 
{
    User *r = NULL; 
	
	User *Temporary = NULL;
    
	UserNames(&r);
    
	Temporary = r;
    
	
	while (Temporary && strcmp(Temporary->UsrName, UsrName)) 
	{
				Temporary = Temporary->next;
	}
	
	if (Temporary && !strcmp(Temporary->Pass, Pass)) 
	{
		//Printf("[ERROR]: Password Check");
		return 1;
	}
	
	
	
			
   
    return 0;
}
