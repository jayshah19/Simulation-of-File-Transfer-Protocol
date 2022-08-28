# Project: Simulation of File Transfer Protocol

Implementing an FTP application between a server and a client is the main goal of this project. Unix Sockets are used to implement the application, which is console-based. The project is being created in C.

An application layer protocol called File Transfer Protocol (FTP) is used to transfer data between local and distant file systems. The client opens a TCP connection with the server side to begin an FTP session between the two parties. The client must log in via FTP, which employs the standard username and password format to provide access. 

Here The "USER" command and the "PASS" command are used to communicate the username and password to the server, respectively. If the server accepts the client's information, the server will give the client a welcome, and the connection will start. Here, I created a multiclient environment using Fork().

I have generated 17 commands for the various operations we can perform using this file transfer protocol. Following is a list of all commands;
USER, PASS, HELP, QUIT, PWD, CWD, CDUP, MKD, RMD, LIST, NOOP, PASV, REIN, RETR, STOR, SYST, TYPE
