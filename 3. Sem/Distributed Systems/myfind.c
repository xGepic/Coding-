#include "myHeader.h"

using namespace std;

//Function printUsage to print out the usage message
void printUsage()
{
    cout << "Usage: ./myfind [-R] [-i] searchpath filename 1 [filename2] ...  [filenameN]\n";
}

int main(int argc, char *argv[])
{
    pid_t pid; //process id
    int op;
    int one = 1;
    unsigned int rFlagCount = 0;
    unsigned int iFlagCount = 0;
    string filenames[argc - optind];
    string path;

    //Loop through all the flags
    while ((op = getopt(argc, argv, "af:")) != EOF)
    {
        switch (op)
        {
        case 'r':
            rFlagCount++;
            break;
        case 'i':
            iFlagCount++;
            break;
        case '?':
            printUsage();
            exit(-1);
            break;
        }
    }

    //get directory and files that follow after the flags
    for (int i = optind; i < argc; i++)
    {
        if (i == optind)
        {
            path = argv[i];
        }
        else
        {
            filenames[i - optind - 1] = argv[i];
        }
    }

    //Printing out what the program is going to do
    cout << "Searching in Directory: '" << path << "' for files: ";
    for (int i = 0; i < argc - optind - 1; i++)
    {
        cout << "'" << filenames[i] << "'";
    }
    cout << "\n";
}
