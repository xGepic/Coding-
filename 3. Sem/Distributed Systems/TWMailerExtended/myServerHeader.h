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
#include <thread>
#include <mutex>

#define BUFFER 1024
#define HOST "ldap://ldap.technikum-wien.at:389"
#define BASEDN "ou=people,dc=technikum-wien,dc=at"
#define LDAP_DEPRECATED 1

using namespace std;

inline struct sockaddr_in address, cliaddress;
inline bool abortRequested = false;
inline int new_socket = -1;
inline int create_socket = -1;
inline int reuseValue = 1;
inline bool isExistingSender = false;
inline bool isExistingReceiver = false;
inline bool isExisting = false;
inline int myCounter = 0;
inline DIR *dir;
inline DIR *receiverDir;
inline DIR *senderDir;
inline DIR *userDir;
inline struct dirent *direntp;
inline struct dirent *direntu;
inline string dirName;
inline socklen_t addrlen;
inline string stringMsgNumberSender;
inline string stringMsgNumberReceiver;
inline string recOrSen;
inline string userName;
inline string sender, receiver, subject, message;
inline string temp, myNewLine = "\n";
inline string messageID;
inline mutex concurrentLock;
inline char *path = const_cast<char *>(dirName.c_str());
inline char actualpath[PATH_MAX];

void clientCommunication(int current_socket);
void signalHandler(int sig);
void mySend(char buffer[BUFFER]);
void myList(char buffer[BUFFER], int current_socket);
string myLogin(char buffer[BUFFER], int current_socket, bool *loggedIn, int *loginCounts);
void myRead(char buffer[BUFFER], int current_socket);
void myDelete(char buffer[BUFFER]);
void printUsage();
void notLoggedIn(char buffer[BUFFER], int current_socket);

#endif