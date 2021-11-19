#include "myServerHeader.h"

////////////////////////////////////////////////////////////////////////////
// Function clientCommunication to handle the Client Communication
void *clientCommunication(void *data)
{
    int size;
    char buffer[BUFFER];
    int *current_socket = (int *)data;

    ////////////////////////////////////////////////////////////////////////////
    // SEND welcome message - this is from the Client Server Example in Moodle
    strcpy(buffer, "\nWelcome to the TWMailer!\r\n\nPlease enter your commands...\r\n");
    if (send(*current_socket, buffer, strlen(buffer), 0) == -1)
    {
        perror("send failed");
        return NULL;
    }

    do
    {
        /////////////////////////////////////////////////////////////////////////
        // RECEIVE - this is from the Client Server Example in Moodle
        size = recv(*current_socket, buffer, BUFFER - 1, 0);
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
            mySend(buffer);
            if (send(*current_socket, "OK", 3, 0) == -1)
            {
                perror("error");
                return NULL;
            }
            break;
        case 'R':
            myRead(buffer, current_socket);
            break;
        case 'L':
            myList(buffer, current_socket);
            break;
        case 'D':
            myDelete(buffer);
            if (send(*current_socket, "OK", 3, 0) == -1)
            {
                perror("error");
                return NULL;
            }
            break;
        case 'Q':
            abortRequested = true;
            break;
        }
        memset(buffer, 0, strlen(buffer));
    } while (strcmp(buffer, "QUIT") != 0 && !abortRequested);

    // closes/frees the descriptor if not already - this is from the Client Server Example in Moodle
    if (*current_socket != -1)
    {
        if (shutdown(*current_socket, SHUT_RDWR) == -1)
        {
            perror("shutdown new_socket");
        }
        if (close(*current_socket) == -1)
        {
            perror("close new_socket");
        }
        *current_socket = -1;
    }

    return NULL;
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
    char *path = const_cast<char *>(dirName.c_str());
    char actualpath[PATH_MAX];
    realpath(path, actualpath);

    dir = opendir(actualpath);
    if (!dir)
    {
        cout << "[Error] Directory not found" << endl;
    }

    //The assignment says "Consider to use getline() function" - lets do that then

    //Copy Buffer into string
    string myString = (string)buffer;
    //Copy String into stringstream
    stringstream myStringStream(myString);

    //we have to get the line three time 1. SEND, 2. Sender and 3. = receiver
    getline(myStringStream, receiver, '\n');
    getline(myStringStream, receiver, '\n');
    getline(myStringStream, receiver, '\n');

    //Get the SEND out of the string
    myString.erase(0, 5);
    strcpy(buffer, myString.c_str()); //update buffer

    char *receiverChar = const_cast<char *>(receiver.c_str());
    string receiverpath = (string)actualpath + "/" + receiver;
    char *receiverPathChar = const_cast<char *>(receiverpath.c_str());

    //Idea from my MyFind
    while ((direntp = readdir(dir)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
        {
            if (strcmp(direntp->d_name, receiverChar) == 0)
            {
                isExisting = true;
                fstream file(receiverpath + "/index.txt");
                getline(file, stringMsgNumber);
                int intMsgnumber = stoi(stringMsgNumber);
                intMsgnumber += 1;
                stringMsgNumber = to_string(intMsgnumber);
                file.close();

                ofstream indexFile(receiverpath + "/index.txt", ofstream::trunc);
                indexFile << stringMsgNumber << '\n';
                indexFile.close();

                ofstream msgFile(receiverpath + "/" + stringMsgNumber + ".txt");
                msgFile << buffer << endl;
                msgFile.close();
            }
        }
    }

    if (isExisting == false)
    {
        int startIndex = 0;
        mkdir(receiverPathChar, 0700); //0700 is permission

        ofstream indexFile(receiverpath + "/index.txt");
        indexFile << startIndex << endl;
        indexFile.close();

        ofstream msgFile(receiverpath + "/0.txt");
        msgFile << buffer << endl;
        msgFile.close();
    }

    closedir(dir);
}

/////////////////////////////////////////////////////////////////////////
//Function LIST to list all messages of a user
void myList(char buffer[BUFFER], void *data)
{
    //structure is the same as in mySend
    int *current_socket = (int *)data;
    char actualpath[PATH_MAX];
    char *pathChar = const_cast<char *>(dirName.c_str());
    realpath(pathChar, actualpath);

    string myString = (string)buffer;      
    stringstream myStringStream(myString);  
    getline(myStringStream, userName, '\n');
    getline(myStringStream, userName, '\n');

    myString.erase(0, 5);
    strcpy(buffer, myString.c_str());

    string userPath = (string)actualpath + "/" + userName;
    char *userPathChar = const_cast<char *>(userPath.c_str());

    dir = opendir(userPathChar);
    if (!dir)
    {
        cout << "[Error] Directory not found" << endl;
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
            transform(subject.begin(), subject.end(),subject.begin(), ::toupper);
            msgList.append(name + ": " + subject + '\n');
            file.close();
        }
    }
    if (send(*current_socket, msgList.c_str(), strlen(msgList.c_str()), 0) == -1) //send recieved message to socket
    {
        perror("send answer failed");
        //return NULL;
    }
    memset(buffer, 0, strlen(buffer));
}

/////////////////////////////////////////////////////////////////////////
//Function READ to display a message of a user
void myRead(char buffer[BUFFER], void *data)
{
    //structure is the same as in mySend
    int *current_socket = (int *)data;
    char actualpath[PATH_MAX];
    char *pathChar = const_cast<char *>(dirName.c_str());
    realpath(pathChar, actualpath);

    string myString= (string)buffer;
    stringstream myStringStream(myString);
    getline(myStringStream, userName, '\n');
    getline(myStringStream, userName, '\n');
    getline(myStringStream, messageNumber, '\n');

    myString.erase(0, 5);
    strcpy(buffer, myString.c_str());

    string userpath = (string)actualpath + "/" + userName;
    char *userPathChar = const_cast<char *>(userpath.c_str());

    dir = opendir(userPathChar);
    if (!dir)
    {
        cout << "[Error] Directory not found" << endl;
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
        fullMessage.append("Sender: " + sender + '\n' + "Reciever: " + receiver + '\n' + "Subject: " + subject + '\n' + "Message: " + message + '\n');
        file.close();
    }

    if (send(*current_socket, fullMessage.c_str(), strlen(fullMessage.c_str()), 0) == -1)
    {
        perror("send answer failed");
    }
    memset(buffer, 0, strlen(buffer));
}

/////////////////////////////////////////////////////////////////////////
//Function DEL to remove a message
void myDelete(char buffer[BUFFER])
{
    //structure is the same as in mySend
    char *pathChar = const_cast<char *>(dirName.c_str());
    char actualpath[PATH_MAX];
    realpath(pathChar, actualpath);

    dir = opendir(actualpath);
    if (!dir)
    {
        cout << "[Error] Directory not found" << endl;
    }

    string myString = (string)buffer; 
    stringstream myStringStream(myString); 
    getline(myStringStream, userName, '\n');
    getline(myStringStream, userName, '\n'); 
    getline(myStringStream, messageID, '\n'); 

    myString.erase(0, 4);             
    strcpy(buffer, myString.c_str());

    char *userNameChar = const_cast<char *>(userName.c_str());
    string usernamePath = (string)actualpath + "/" + userName;
    string messageIDpath = usernamePath + "/" + messageID + ".txt";
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