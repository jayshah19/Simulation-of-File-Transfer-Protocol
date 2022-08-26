

// ASP PROJECT: SIMULATION OF FTP PROTOCOL

// SECTION-2

// JAY PARESHKUMAR SHAH (110072802)
// MANSI MITESHKUMAR SHAH (110073005)


#define MAX_LENGTH 1024
#define SEPCHARS " \t\r\n"
#define PORT "21"

extern enum BOOLEAN bool;
typedef enum BOOLEAN boolean;

int CreateSocketClient(char *port, char *ipAdd); //Create  client socket
void clientparamerterChecker(int argc); //Paremeter Checker
void PASV_Process(char *response); //Open the passive mode. passive mode response Syntax: (a1,a2,a3,a4,p1,p2)
void Read_Res(int controlSocket, char response[MAX_LENGTH]); //server response reader.
void RETR_Process(char command[], int sock_data); //In order to create a new file and add it to our directory. 
void LIST_Process(int sock_data); //List of current directory
void STOR_Process(char command[], int sock_data); //Process The STOR command
void GET_File(char command[], char filename[]); //Get file name
void CREATE_ConncetData(char command[], char ip[]); //whenever a client enters a LIST, RETR, or STOR command, it creates a data connection. 

boolean check_directory(char command[]); //This is used to verify if a file is indeed there in the client directory. By actually attempting to open the file, this is done. We can be certain a file doesn't exist if we are unable to open it. 






