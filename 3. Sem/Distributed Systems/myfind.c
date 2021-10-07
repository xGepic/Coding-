#include "myHeader.h" //all headers in an external file

using namespace std;

//Function printUsage to print out the usage message
void printUsage()
{
    fprintf(stderr, "Usage: ./myfind [-R] [-i] searchpath filename 1 [filename2] ...  [filenameN]\n");
}

int main(int argc, char *argv[])
{
    pid_t pid;                       //process ID
    char op;                         //operator
    bool rFlag = false;              //bool for R Flag
    bool iFlag = false;              //bool for i Flag
    string files[argc - optind - 1]; //string for the filnames, as big as necessary
    string dir;                      //string for directory
    int status = 0;                  //status

    //Loop through all the flags
    while ((op = getopt(argc, argv, "Ri:")) != EOF)
    {
        switch (op)
        {
        case 'R':
            rFlag = true;
            break;
        case 'i':
            iFlag = true;
            break;
        case '?':
            printUsage();
            exit(EXIT_FAILURE);
            break;
        }
    }
    //Get directory and files that follow after the flags
    for (int i = optind; i < argc; i++)
    {
        if (i == optind)
        {
            dir = argv[i];
        }
        else
        {
            files[i - optind - 1] = argv[i];
        }
    }
    //Print what the programm will do
    cout << "\nSearching in: '" << dir << "' for: ";
    for (int i = 0; i < argc - optind - 1; i++)
    {
        cout << "'" << files[i] << "'";
    }
    cout << "\n\n";
    //search
    for (int i = optind + 1; i < argc; i++)
    {
        pid_t pid = fork();
        switch (pid)
        {
        //If -1 --> Child Process Error
        case -1:
            cout << "Child process error" << endl;
            exit(EXIT_FAILURE);
            break;
        //If 0 --> We are in the Child Process
        case 0:
            bool found = false;
            bool *foundP = &found;
            if (rFlag)
            {
                //recursive search
            }
            else
            {
                //search
            }
            if (!*foundP)
            {
                cout << "File not found: " << argv[i] << endl;
            }
            exit(EXIT_SUCCESS);
            break;
        }
        if (pid > 0)
        {
            wait(&status);
        }
    }
    return 0;
}
