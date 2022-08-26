

// ASP PROJECT: SIMULATION OF FTP PROTOCOL

// SECTION-2

// JAY PARESHKUMAR SHAH (110072802)
// MANSI MITESHKUMAR SHAH (110073005)




typedef struct Users
{
	char UsrName[300];
	char Pass[300];
	struct Users *next;
} User;


void UserAdd(User **r, char *UsrName, char *Pass);
void UserNames(User **r);
int UserNameChecker(char *UsrName, char **CurrentUser);
int UserPasswordChecker(char *UsrName, char *Pass);


extern enum states state ; //Diffrent User States
extern int dataSocket; //For Data Connection
extern char *CurrentUser; //Name Of Client WHO LOGGED

// Important Functions 

int createServer(int PredefinedPortNumber); //For Create Server
int open_data_connection(); // OPen Connection for client
int doProcessing(int controlSocket, enum states *ptrState);
void paramerterChecker(int argc); //Paremeter Checker
void write_message(int controlSocket, char *strMsg); //write a Message To a Client.


// functions For Diffrent commands
 
void USER_Command(char *UsrName, enum states *ptrState, int controlSocket);
void PASS_Command(char *Pass, enum states *ptrState, int controlSocket);
void CDUP_Command(int controlSocket);
void PASV_Command(int controlSocket);
void PWD_Command(int controlSocket);
void CWD_Command(int controlSocket, char *destination);
void MKD_Command(int controlSocket, char *dir);
void RWD_Command(int controlSocket, char *dir);
void TYPE_Command(int controlSocket, char *type);
void LIST_Command(int controlSocket);
void RETR_Command(int controlSocket, char *filename, intmax_t position);
void SYST_Command(int controlSocket);
void STOR_Command(int controlSocket, char *filename);
void NOOP_Command(int controlSocket);
void HELP_Command(int controlSocket, char *cmd);
void QUIT_Command(int controlSocket, enum states *ptrState);
void REIN_Command(int controlSocket, enum states *ptrState);
//void PORT_Command(int controlSocket, char *argv[]);
//void port(t_cli *cli);
//void port(int controlSocket, char **params);



//  functions for Positive Reply from server to client  as a responses.

void ReplyForASCII(int controlSocket, char *file);
void ReplyForTransfer(int controlSocket, int numBytes);
void ReplyForHelp(int controlSocket, char *cmd);
void ReplyForCmdOk(int controlSocket);
void ReplyForCmdSuccessful(int controlSocket, char *cmd);
void ReplyForConEstablished(int controlSocket);
void ReplyForPASVSwitch(int controlSocket);


//  functions for Negative Reply from server to client  as a responses.

void ReplyForNotLogged(int controlSocket);
void ReplyForUnableToOpenData(int controlSocket);
void ReplyForNoFile(int controlSocket);
void ReplyForUnknownCmd(int controlSocket);
void ReplyForNoCommand(int controlSocket);
void ReplyForNoImplementationOfSuperflous(int controlSocket);
void ReplyForFailToOpen(int controlSocket);
void ReplyForFileNotFound(int controlSocket);
void ReplyForNoCommandPermission(int controlSocket);
void ReplyForCloseDataConection(int controlSocket) ;