#include "myClientHeader.h"

////////////////////////////////////////////////////////////////////////////
// Function printMenu to cout the Menu
void printMenu()
{
    cout << "SEND - Send a message to the server" << endl;
    cout << "LIST - List all messages of a user" << endl;
    cout << "READ - Display a message of a user" << endl;
    cout << "DEL - Remove a message" << endl;
    cout << "QUIT - Logout" << endl;
}

////////////////////////////////////////////////////////////////////////////
// Function printUsage to cout the Usage Message
void printUsage()
{
    cout << "Error - Use one of the following Commands:  SEND - LIST - READ - DEL - QUIT" << endl;
}

/////////////////////////////////////////////////////////////0///////////////
// Function prinserverCommunication to handle the server Communication
void serverCommunication()
{
    int size;

    //Get Data from Socket - this is from the Client Server Example in Moodle
    size = recv(create_socket, buffer, BUFFER - 1, 0);
    buffer[size] = '\0'; //null termination
    cout << buffer;

    do
    {
        char input[BUFFER];
        string savedMessage = "";

        printMenu();
        cout << endl << ">> ";

        do
        {
            fgets(input, BUFFER, stdin);
            cout << "INPUT:" << input << endl;
            myCommand = (string)input;
            if (myCommand == "SEND\n" || myCommand == "LIST\n" || myCommand == "READ\n" || myCommand == "DEL\n" || myCommand == "QUIT\n")
            {
                inputCorrect = true;
            }
            else
            {
                printUsage();
            }
        } while (inputCorrect == false);

        isReady = true;

        //////////////////////////////////////////////////////////////////////
        // SEND DATA
        if ((string)input == "SEND\n")
        {
            savedMessage = savedMessage + input;

            do
            {
                cout << "Please enter the Senders-Username (Max eight characters):" << endl << ">> ";
                fgets(input, BUFFER, stdin);
            } while (strlen(input) > 9 || !inputValidation(input));

            savedMessage = savedMessage + input;

            do
            {
                cout << "Please enter the Recivers-Username (Max eight characters):" << endl << ">> ";
                fgets(input, BUFFER, stdin);
            } while (strlen(input) > 9 || !inputValidation(input));

            savedMessage = savedMessage + input;

            do
            {
                cout << "Please enter the Subject:(Max 80 characters):" << endl << ">> ";
                fgets(input, BUFFER, stdin);
            } while (strlen(input) > 81);

            savedMessage = savedMessage + input;

            cout << "Please enter the your Message:" << endl << ">> ";
            while ((string)fgets(input, BUFFER, stdin) != ".\n")
            {
                savedMessage = savedMessage + input;
            }

            strcpy(buffer, savedMessage.c_str());
        }

        //////////////////////////////////////////////////////////////////////
        // READ DATA
        else if ((string)input == "READ\n")
        {
            savedMessage = savedMessage + input;

            cout << "Username:" << endl << ">> ";
            fgets(input, BUFFER, stdin);

            savedMessage = savedMessage + input;

            cout << "Message Number:" << endl << ">> ";
            fgets(input, BUFFER, stdin);

            savedMessage = savedMessage + input;

            strcpy(buffer, savedMessage.c_str());
            isReady = false;
        }

        //////////////////////////////////////////////////////////////////////
        // LIST DATA
        else if ((string)input == "LIST\n")
        {
            savedMessage = savedMessage + input;

            cout << "Username:" << endl << ">> ";
            fgets(input, BUFFER, stdin);

            savedMessage = savedMessage + input;

            strcpy(buffer, savedMessage.c_str());
            isReady = false;
        }

        //////////////////////////////////////////////////////////////////////
        // DELETE DATA
        else if ((string)input == "DEL\n")
        {
            savedMessage = savedMessage + input;

            cout << "Username:" << endl << ">> ";
            fgets(input, BUFFER, stdin);

            savedMessage = savedMessage + input;

            do
            {
                cout << "Message Number:" << endl << ">> ";
                fgets(input, BUFFER, stdin);
            } while (!isNumeric(input));

            savedMessage = savedMessage + input;

            strcpy(buffer, savedMessage.c_str());
        }
        
        //////////////////////////////////////////////////////////////////////
        // QUIT
        else if ((string)input == "QUIT\n")
        {
            strcpy(buffer, input);
        }

        if (buffer != NULL)
        {
            int size = strlen(buffer);

            // remove new-line signs from string at the end - this is from the Client Server Example in Moodle
            if (buffer[size - 2] == '\r' && buffer[size - 1] == '\n')
            {
                size -= 2;
                buffer[size] = 0;
            }
            else if (buffer[size - 1] == '\n')
            {
                --size;
                buffer[size] = 0;
            }
            isQuit = strcmp(buffer, "QUIT") == 0;

            if ((send(create_socket, buffer, strlen(buffer), 0)) == -1)
            {
                perror("send error");
                break;
            }

            size = recv(create_socket, buffer, BUFFER - 1, 0);
            if (size < 1)
            {
                perror("recv error");
                break;
            }
            else
            {
                buffer[size] = '\0'; //null termination
                cout << "<< " << buffer << endl;
                if (isReady)
                {
                    if (strcmp("OK", buffer) != 0)
                    {
                        fprintf(stderr, "[Server Error]\n");
                        break;
                    }
                }
            }
            memset(buffer, 0, strlen(buffer));
        }
    } while (!isQuit);
}

////////////////////////////////////////////////////////////////////////////
// Function inputValidation to validate the Input
bool inputValidation(char input[BUFFER])
{

    for (int i = 0; i < (int)strlen(input) - 1; i++)
    {
        if (islower(input[i]) || isdigit((int)input[i]))
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////
// Function isNumeric to check if the input is a number
bool isNumeric(char input[BUFFER])
{
    for (int i = 0; i < (int)strlen(input) - 1; i++)
    {
        if (isdigit((int)input[i]) == true)
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}