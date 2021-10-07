#include "myHeader.h"

using namespace std;

//Function printUsage to print out the usage message
void printUsage()
{
    fprintf(stderr, "Usage: ./myfind [-R] [-i] searchpath filename 1 [filename2] ...  [filenameN]\n");
}

int main(int argc, char *argv[])
{
    pid_t pid;               //process ID
    char op;                 //operator
    bool rFlagCount = false; //bool for R Flag
    bool iFlagCount = false; //bool for i Flag
    string files[argc - optind]; //string for the filnames, as big as necessary
    string directory;

    //Loop through all the flags
    while ((op = getopt(argc, argv, "Ri:")) != EOF)
    {
        switch (op)
        {
        case 'R':
            rFlagCount = true;
            break;
        case 'i':
            iFlagCount = true;
            break;
        case '?':
            printUsage();
            exit(EXIT_FAILURE);
            break;
        }
    }
    // get directory and files that follow after the flags
    for (int i = optind; i < argc; i++)
    {
        if (i == optind)
        {
            directory = argv[i];
        }
        else
        {
            files[i - optind - 1] = argv[i];
        }
    }
}
