# Project: Simulation of File Transfer Protocol

Implementing an FTP application between a server and a client is the main goal of this project. Unix Sockets are used to implement the application, which is console-based. The project is being created in C.

An application layer protocol called File Transfer Protocol (FTP) is used to transfer data between local and distant file systems. The client opens a TCP connection with the server side to begin an FTP session between the two parties. The client must log in via FTP, which employs the standard username and password format to provide access. 

Here The "USER" command and the "PASS" command are used to communicate the username and password to the server, respectively. If the server accepts the client's information, the server will give the client a welcome, and the connection will start. Here, I created a multiclient environment using Fork().

I have generated 17 commands for the various operations we can perform using this file transfer protocol. Following is a list of all commands;
USER, PASS, HELP, QUIT, PWD, CWD, CDUP, MKD, RMD, LIST, NOOP, PASV, REIN, RETR, STOR, SYST, TYPE

======================= Important Instructions :=======================

For the Client-Server Communication, i used Predefind PORT NUMBER as 21 For both Client And Server. 

The main reason for choosing PORT Number 21 is that it is commonly associated with FTP and controls the FTP session. 

Some commands Need a passive Mode. For that, Please use the "PASV" command first and then the required command that you want an execution

================================ SERVER ================================

-> cd FTPServer

-> sudo gcc -o server FTPServer.c FTPServerCreate.c FTPServerProcess.c Command_Cdup.c Command_Cwd.c Command_Help.c Command_List.c Command_Mkd.c Command_Noop.c Command_Pass.c Command_Pasv.c Command_Pwd.c Command_Quit.c Command_Rein.c Command_Retr.c Command_Rwd.c Command_Stor.c Command_Syst.c Command_Type.c Command_User.c RepliesNegative.c RepliesPositive.c User_Add.c User_Name_Check.c User_Names.c User_Password_Check.c

-> sudo ./server

================================ CLIENT ================================

-> cd FTPClient

-> sudo gcc -o client FTPClient.c CreateClientSocket.c CreateData.c DirectoryCheck.c GetFile.c ProcessList.c ProcessPasv.c ProcessRetr.c ProcessStor.c ReadResponse.c

-> sudo ./client 127.0.0.1

======================= UserName And Passwords =======================


Here i implemented Username And Password Authentication for connection establishment between server and client

All username-password is case sensitive

				
================================

For Normal Users
				
Name:: 					Password
				

->  aznam::				  yacoub

->  jay::			          admin

->  mansi::				  shah

->  karan::			          GA
				
================================		
				
For Super Users (No password Needed For Super Users)
						
-> Professor

-> AZNAM
        
-> JAY
						
================================
