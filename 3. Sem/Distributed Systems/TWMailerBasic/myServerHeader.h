#ifndef MYSERVERHEADER_H
#define MYSERVERHEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>

#define PORT 4848
#define BUFFER 1024

using namespace std;

inline struct sockaddr_in address, cliaddress;
inline bool abortRequested = false;
inline int new_socket = -1;
inline int create_socket = -1;
inline char buffer[BUFFER];
inline int reuseValue = 1;
inline bool isExisting = false;
inline int myCounter = 0;
inline DIR *dir;
inline struct dirent *direntp;
inline string dirName;
inline socklen_t addrlen;
inline string stringMsgNumber;
inline string msgList;
inline string userName; 
inline string fullMessage;
inline string messageNumber; 
inline string sender, receiver, subject, message;
inline string temp, myNewLine = "\n";
inline string messageID;

void *clientCommunication(void *data);
void signalHandler(int sig);
void mySend(char buffer[BUFFER]);
void myList(char buffer[BUFFER], void *data);
void myRead(char buffer[BUFFER], void *data);
void myDelete(char buffer[BUFFER]);

#endif