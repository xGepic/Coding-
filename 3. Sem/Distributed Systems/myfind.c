#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//Function printUsage to print out the usage message
void printUsage()
{
    fprintf(stderr, "Usage: ./myfind [-R] [-i] searchpath filename 1 [filename2] ... [filenameN]\n");
}

int main(int argc, char *argv[])
{
    int op;
    unsigned int rFlagCount = 0;
    unsigned int iFlagCount = 0;

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
            break;
        }
    }
}
