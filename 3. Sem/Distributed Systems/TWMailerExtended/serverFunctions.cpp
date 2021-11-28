#include "myServerHeader.h"
#include <ldap.h>

////////////////////////////////////////////////////////////////////////////
// Function clientCommunication to handle the Client Communication
void clientCommunication(int current_socket)
{
    int size;
    char buffer[BUFFER];
    string loggedInUser;
    bool loggedIn = false;
    int loginCounts = 0;

    ////////////////////////////////////////////////////////////////////////////
    // SEND welcome message - this is from the Client Server Example in Moodle
    strcpy(buffer, "\nWelcome to the TWMailer!\r\n\nPlease enter your commands...\r\n");
    if (send(current_socket, buffer, strlen(buffer), 0) == -1)
    {
        perror("send failed");
        return;
    }

    do
    {
        /////////////////////////////////////////////////////////////////////////
        // RECEIVE - this is from the Client Server Example in Moodle
        size = recv(current_socket, buffer, BUFFER - 1, 0);
        if (size == -1)
        {
            if (abortRequested)
            {
                perror("recv error after aborted");
            }
            else
            {
                perror("recv error");
            }
            break;
        }

        if (size == 0)
        {
            cout << "Client closed remote socket" << endl;
            break;
        }

        // remove ugly debug message, because of the sent newline of client - this is from the Client Server Example in Moodle
        if (buffer[size - 2] == '\r' && buffer[size - 1] == '\n')
        {
            size -= 2;
        }
        else if (buffer[size - 1] == '\n')
        {
            --size;
        }

        buffer[size] = '\0';

        switch (buffer[0])
        {
        case 'S':
            if (loggedIn)
            {
                mySend(buffer);
                if (send(current_socket, "OK", 3, 0) == -1)
                {
                    perror("error");
                    return;
                }
            }
            else
            {
                notLoggedIn(buffer, current_socket);
            }
            break;
        case 'R':
            if (loggedIn)
            {
                myRead(buffer, current_socket);
            }
            else
            {
                notLoggedIn(buffer, current_socket);
            }
            break;
        case 'L':
            if (buffer[1] == 'I')
            {
                if (loggedIn)
                {
                    myList(buffer, current_socket);
                }
                else
                {
                    notLoggedIn(buffer, current_socket);
                }
            }
            else if (buffer[1] == 'O')
            {
                loggedInUser = myLogin(buffer, current_socket, &loggedIn, &loginCounts);
            }
            break;
        case 'D':
            if (loggedIn)
            {
                myDelete(buffer);
                if (send(current_socket, "OK", 3, 0) == -1)
                {
                    perror("error");
                    return;
                }
            }
            else
            {
                notLoggedIn(buffer, current_socket);
            }
            break;
        case 'Q':
            abortRequested = true;
            break;
        }
        memset(buffer, 0, strlen(buffer));
    } while (strcmp(buffer, "QUIT") != 0 && !abortRequested);

    // closes/frees the descriptor if not already - this is from the Client Server Example in Moodle
    if (current_socket != -1)
    {
        if (shutdown(current_socket, SHUT_RDWR) == -1)
        {
            perror("shutdown new_socket");
        }
        if (close(current_socket) == -1)
        {
            perror("close new_socket");
        }
        current_socket = -1;
    }

    return;
}

/////////////////////////////////////////////////////////////////////////
//Signal Handler - this is from the Client Server Example in Moodle
void signalHandler(int sig)
{
    if (sig == SIGINT)
    {
        cout << "abort Requested..." << endl;
        abortRequested = true;

        if (new_socket != -1)
        {
            if (shutdown(new_socket, SHUT_RDWR) == -1)
            {
                perror("shutdown new_socket");
            }
            if (close(new_socket) == -1)
            {
                perror("close new_socket");
            }
            new_socket = -1;
        }

        if (create_socket != -1)
        {
            if (shutdown(create_socket, SHUT_RDWR) == -1)
            {
                perror("shutdown create_socket");
            }
            if (close(create_socket) == -1)
            {
                perror("close create_socket");
            }
            create_socket = -1;
        }
    }
    else
    {
        exit(sig);
    }
}

/////////////////////////////////////////////////////////////////////////
//Function SEND to send a message to the server
void mySend(char buffer[BUFFER])
{
    lock_guard<mutex> guard(concurrentLock);
    realpath(path, actualpath);
    dir = opendir(actualpath);
    if (!dir)
    {
        cerr << "[Error] Directory not found" << endl;
    }

    //The assignment says "Consider to use getline() function" - lets do that then

    //Copy Buffer into string
    string myString = (string)buffer;
    //Copy String into stringstream
    stringstream myStringStream(myString);

    //we have to get the line three times 1. SEND, 2. Sender and 3. = receiver
    getline(myStringStream, receiver, '\n'); //does not matter into wich variable it is saved, it wont be used
    getline(myStringStream, sender, '\n');   //needed for sentMails folder
    getline(myStringStream, receiver, '\n'); //needed for receivedMails folder

    //Get the SEND out of the string
    myString.erase(0, 5);
    strcpy(buffer, myString.c_str()); //update buffer
    char *receiverChar = const_cast<char *>(receiver.c_str());
    string receiverpath = (string)actualpath + "/" + receiver;
    char *receiverPathChar = const_cast<char *>(receiverpath.c_str());
    char *senderChar = const_cast<char *>(sender.c_str());
    string senderpath = (string)actualpath + "/" + sender;
    char *senderPathChar = const_cast<char *>(senderpath.c_str());
    //saving into ReceivedMails
    //Idea from my MyFind
    while ((direntp = readdir(dir)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
        {
            if (strcmp(direntp->d_name, receiverChar) == 0)
            {
                isExistingReceiver = true;
                char *userPath = const_cast<char *>(actualpath);
                strcat(userPath, "/");
                strcat(userPath, receiver.c_str());
                userDir = opendir(userPath);
                if (!userDir)
                {
                    cerr << "[Error] Directory not found" << endl;
                }
                bool existingFolder = false;
                while ((direntu = readdir(userDir)) != NULL)
                {
                    if (strcmp(direntu->d_name, "ReceivedMails") == 0)
                    {
                        existingFolder = true;
                        receiverDir = opendir(receiverPathChar);
                        if (!receiverDir)
                        {
                            cerr << "[Error] Directory not found" << endl;
                        }
                        strcat(receiverPathChar, "/ReceivedMails");
                        receiverpath = receiverpath + "/ReceivedMails";
                        fstream file(receiverpath + "/index.txt");
                        getline(file, stringMsgNumberReceiver);
                        int intMsgnumber = stoi(stringMsgNumberReceiver);
                        intMsgnumber += 1;
                        stringMsgNumberReceiver = to_string(intMsgnumber);
                        file.close();

                        ofstream indexFile(receiverpath + "/index.txt", ofstream::trunc);
                        indexFile << stringMsgNumberReceiver << '\n';
                        indexFile.close();

                        ofstream msgFile(receiverpath + "/" + stringMsgNumberReceiver + ".txt");
                        msgFile << buffer << endl;
                        msgFile.close();
                        closedir(receiverDir);
                    }
                }
                closedir(userDir);
                if (!existingFolder)
                {
                    int startIndex = 0;
                    strcat(receiverPathChar, "/ReceivedMails");
                    mkdir(receiverPathChar, 0700); //0700 is permission
                    receiverpath = receiverpath + "/ReceivedMails";

                    ofstream indexFileReceiver(receiverpath + "/index.txt");
                    indexFileReceiver << startIndex << endl;
                    indexFileReceiver.close();

                    ofstream msgFile(receiverpath + "/0.txt");
                    msgFile << buffer << endl;
                    msgFile.close();
                }
            }
        }
    }
    if (isExistingReceiver == false)
    {
        int startIndex = 0;
        mkdir(receiverPathChar, 0700); //0700 is permission
        receiverDir = opendir(receiverPathChar);
        if (!receiverDir)
        {
            cerr << "[Error] Directory not found" << endl;
        }
        //Ordner anlegen
        strcat(receiverPathChar, "/ReceivedMails");
        mkdir(receiverPathChar, 0700); //0700 is permission
        receiverpath = receiverpath + "/ReceivedMails";

        ofstream indexFileReceiver(receiverpath + "/index.txt");
        indexFileReceiver << startIndex << endl;
        indexFileReceiver.close();

        ofstream msgFile(receiverpath + "/0.txt");
        msgFile << buffer << endl;
        msgFile.close();
        closedir(receiverDir);
    }
    closedir(dir);
    isExistingReceiver = false; //reset variable
    realpath(path, actualpath);
    dir = opendir(actualpath);
    if (!dir)
    {
        cerr << "[Error] Directory not found" << endl;
    }

    //Saving into SentMails
    //Idea from my MyFind
    while ((direntp = readdir(dir)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
        {
            if (strcmp(direntp->d_name, senderChar) == 0)
            {
                cout << "user existiert schon" << endl;
                isExistingSender = true;
                char *userPath = const_cast<char *>(actualpath);
                strcat(userPath, "/");
                strcat(userPath, sender.c_str());
                userDir = opendir(userPath);
                if (!userDir)
                {
                    cerr << "[Error] Directory not found" << endl;
                }
                bool existingFolder = false;
                while ((direntu = readdir(userDir)) != NULL)
                {
                    if (strcmp(direntu->d_name, "SentMails") == 0)
                    {
                        existingFolder = true;
                        senderDir = opendir(senderPathChar);
                        if (!senderDir)
                        {
                            cerr << "[Error] Directory not found" << endl;
                        }
                        strcat(senderPathChar, "/SentMails");
                        senderpath = senderpath + "/SentMails";
                        fstream file(senderpath + "/index.txt");
                        getline(file, stringMsgNumberSender);
                        int intMsgnumber = stoi(stringMsgNumberSender);
                        intMsgnumber += 1;
                        stringMsgNumberSender = to_string(intMsgnumber);
                        file.close();

                        ofstream indexFile(senderpath + "/index.txt", ofstream::trunc);
                        indexFile << stringMsgNumberSender << '\n';
                        indexFile.close();

                        ofstream msgFile(senderpath + "/" + stringMsgNumberSender + ".txt");
                        msgFile << buffer << endl;
                        msgFile.close();
                        closedir(senderDir);
                    }
                }
                closedir(userDir);
                if (!existingFolder)
                {
                    int startIndex = 0;
                    strcat(senderPathChar, "/SentMails");
                    mkdir(senderPathChar, 0700); //0700 is permission
                    senderpath = senderpath + "/SentMails";

                    ofstream indexFileSender(senderpath + "/index.txt");
                    indexFileSender << startIndex << endl;
                    indexFileSender.close();

                    ofstream msgFile(senderpath + "/0.txt");
                    msgFile << buffer << endl;
                    msgFile.close();
                }
            }
        }
    }

    if (isExistingSender == false)
    {
        int startIndex = 0;
        mkdir(senderPathChar, 0700); //0700 is permission
        senderDir = opendir(senderPathChar);
        if (!senderDir)
        {
            cerr << "[Error] Directory not found" << endl;
        }
        //Ordner anlegen
        strcat(senderPathChar, "/SentMails");
        mkdir(senderPathChar, 0700); //0700 is permission
        senderpath = senderpath + "/SentMails";

        ofstream indexFileSender(senderpath + "/index.txt");
        indexFileSender << startIndex << endl;
        indexFileSender.close();

        ofstream msgFile(senderpath + "/0.txt");
        msgFile << buffer << endl;
        msgFile.close();
        closedir(senderDir);
    }
    closedir(dir);
    isExistingSender = false; //reset variable
}

/////////////////////////////////////////////////////////////////////////
//Function LIST to list all messages of a user
void myList(char buffer[BUFFER], int current_socket)
{
    lock_guard<mutex> guard(concurrentLock);
    //structure is the same as in mySend
    char actualpath[PATH_MAX];
    string msgList;
    char *pathChar = const_cast<char *>(dirName.c_str());
    realpath(pathChar, actualpath);

    string myString = (string)buffer;
    stringstream myStringStream(myString);
    getline(myStringStream, userName, '\n');
    getline(myStringStream, recOrSen, '\n');
    getline(myStringStream, userName, '\n');

    myString.erase(0, 5);
    strcpy(buffer, myString.c_str());

    string userPath = (string)actualpath + "/" + userName;
    if (recOrSen == "REC")
    {
        userPath = userPath + "/ReceivedMails";
    }
    else if (recOrSen == "SEN")
    {
        userPath = userPath + "/SentMails";
    }
    else
    {
        cerr << "Wrong Input!" << endl;
    }
    recOrSen.clear();

    char *userPathChar = const_cast<char *>(userPath.c_str());

    dir = opendir(userPathChar);
    if (!dir)
    {
        cerr << "[Error] Directory not found" << endl;
    }

    while ((direntp = readdir(dir)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
        {
            myCounter++;
        }
    }
    myCounter--;
    msgList = to_string(myCounter) + " mails" + '\n';

    // reset directory stream
    rewinddir(dir);

    while ((direntp = readdir(dir)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, "..") && strcmp(direntp->d_name, "index.txt"))
        {
            string name = direntp->d_name;
            //we pop_back the last for chars ergo the ".txt"
            name.pop_back();
            name.pop_back();
            name.pop_back();
            name.pop_back();
            fstream file(userPath + "/" + direntp->d_name);

            //Get Subject
            getline(file, subject);
            getline(file, subject);
            getline(file, subject);
            //output the subject in uppercase letter
            transform(subject.begin(), subject.end(), subject.begin(), ::toupper);
            msgList.append(name + ": " + subject + '\n');
            file.close();
        }
    }
    if (send(current_socket, msgList.c_str(), strlen(msgList.c_str()), 0) == -1) //send recieved message to socket
    {
        perror("send answer failed");
        //return NULL;
    }
    memset(buffer, 0, strlen(buffer));
}

/////////////////////////////////////////////////////////////////////////
//Function Login to login the User
string myLogin(char buffer[BUFFER], int current_socket, bool *loggedIn, int *loginCounts)
{
    string username, password, responseText;
    if (*loginCounts > 2)
    {
        responseText = "Login failed due to too many retries";
        if (send(current_socket, responseText.c_str(), strlen(responseText.c_str()), 0) == -1)
        {
            perror("send answer failed");
        }
        memset(buffer, 0, strlen(buffer));
        return "";
    }
    lock_guard<mutex> guard(concurrentLock);

    string myString = (string)buffer;
    stringstream myStringStream(myString);
    getline(myStringStream, username, '\n');
    getline(myStringStream, username, '\n');
    getline(myStringStream, password, '\n');

    myString.erase(0, 6);
    strcpy(buffer, myString.c_str());

    LDAP *ld;
    int rc;

    if (ldap_initialize(&ld, HOST))
    {
        perror("ldap_initialize");
    }
    int protocol_version = LDAP_VERSION3;
    rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &protocol_version);

    string baseDn = "uid=" + username + "," + BASEDN;
    rc = ldap_simple_bind_s(ld, baseDn.c_str(), password.c_str());
    if (rc != LDAP_SUCCESS)
    {
        *loginCounts = *loginCounts + 1;
        responseText = "Login failed";
        if (send(current_socket, responseText.c_str(), strlen(responseText.c_str()), 0) == -1)
        {
            perror("send answer failed");
        }
        memset(buffer, 0, strlen(buffer));
        return "";
    }
    else
    {
        responseText = "Successful Login";
        if (send(current_socket, responseText.c_str(), strlen(responseText.c_str()), 0) == -1)
        {
            perror("send answer failed");
        }
        memset(buffer, 0, strlen(buffer));
        *loggedIn = true;
        return username;
    }
}

/////////////////////////////////////////////////////////////////////////
//Function READ to display a message of a user
void myRead(char buffer[BUFFER], int current_socket)
{
    lock_guard<mutex> guard(concurrentLock);
    //structure is the same as in mySend
    char actualpath[PATH_MAX];
    string fullMessage, messageNumber;
    char *pathChar = const_cast<char *>(dirName.c_str());
    realpath(pathChar, actualpath);

    string myString = (string)buffer;
    stringstream myStringStream(myString);
    getline(myStringStream, userName, '\n'); //gets dumped
    getline(myStringStream, recOrSen, '\n');
    getline(myStringStream, userName, '\n');
    getline(myStringStream, messageNumber, '\n');

    myString.erase(0, 5);
    strcpy(buffer, myString.c_str());

    string userpath = (string)actualpath + "/" + userName;
    if (recOrSen == "REC")
    {
        userpath = userpath + "/ReceivedMails";
    }
    else if (recOrSen == "SEN")
    {
        userpath = userpath + "/SentMails";
    }
    else
    {
        cerr << "Wrong Input!" << endl;
    }
    recOrSen.clear();

    char *userPathChar = const_cast<char *>(userpath.c_str());

    dir = opendir(userPathChar);
    if (!dir)
    {
        cerr << "[Error] Directory not found" << endl;
    }

    fstream file(userpath + "/" + messageNumber + ".txt");
    if (file.is_open())
    {
        getline(file, sender);
        getline(file, receiver);
        getline(file, subject);
        message.append(myNewLine);
        while (getline(file, temp))
        {
            message.append(temp + '\n');
        }
        fullMessage.append("Sender: " + sender + '\n' + "Reciever: " + receiver + '\n' + "Subject: " + subject + '\n' +
                           "Message: " + message + '\n');
        file.close();
    }

    if (send(current_socket, fullMessage.c_str(), strlen(fullMessage.c_str()), 0) == -1)
    {
        perror("send answer failed");
    }
    memset(buffer, 0, strlen(buffer));
}

/////////////////////////////////////////////////////////////////////////
//Function DEL to remove a message
void myDelete(char buffer[BUFFER])
{
    lock_guard<mutex> guard(concurrentLock);
    //structure is the same as in mySend
    char *pathChar = const_cast<char *>(dirName.c_str());
    char actualpath[PATH_MAX];
    realpath(pathChar, actualpath);

    dir = opendir(actualpath);
    if (!dir)
    {
        cerr << "[Error] Directory not found" << endl;
    }

    string myString = (string)buffer;
    stringstream myStringStream(myString);
    getline(myStringStream, userName, '\n');
    getline(myStringStream, recOrSen, '\n');
    getline(myStringStream, userName, '\n');
    getline(myStringStream, messageID, '\n');

    myString.erase(0, 4);
    strcpy(buffer, myString.c_str());

    char *userNameChar = const_cast<char *>(userName.c_str());
    string usernamePath = (string)actualpath + "/" + userName;
    string messageIDpath;
    if (recOrSen == "REC")
    {
        usernamePath = usernamePath + "/ReceivedMails";
        messageIDpath = usernamePath + "/" + messageID + ".txt";
    }
    else if (recOrSen == "SEN")
    {
        usernamePath = usernamePath + "/SentMails";
        messageIDpath = usernamePath + "/" + messageID + ".txt";
    }
    else
    {
        cerr << "Wrong Input!" << endl;
    }
    recOrSen.clear();
    char *messageIDpathChar = const_cast<char *>(messageIDpath.c_str());

    while ((direntp = readdir(dir)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
        {
            if (strcmp(direntp->d_name, userNameChar) == 0)
            {
                isExisting = true;
                remove(messageIDpathChar);
            }
        }
    }
    if (isExisting == false)
    {
        cout << "[Error] There is no such User!" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////
//Function printUsage to display the Usage Message
void printUsage()
{
    cout << "Usage: ./myServer <port> <mail-spool-directoryname>" << endl;
}

/////////////////////////////////////////////////////////////////////////
//Function notLoggedIn to notify if the user is not logged in
void notLoggedIn(char buffer[BUFFER], int current_socket)
{
    string resMsg = "You are not logged in.";
    if (send(current_socket, resMsg.c_str(), strlen(resMsg.c_str()), 0) == -1)
    {
        perror("send answer failed");
    }
    memset(buffer, 0, strlen(buffer));
}