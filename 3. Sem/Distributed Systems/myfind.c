#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

char *programName = NULL;

//Function printUsage to print out the usage message
void printUsage()
{
    fprintf(stderr, "Usage: %s [-R] [-i] searchpath filename 1 [filename2] ... [filenameN]\n", programName);
    exit(EXIT_FAILURE);
}

//Output Format: <pid>: <filename>: <complete-path-to-found-file>\n

int main(int argc, char *argv[])
{
    int op;
    while ((op = getopt(argc, argv, "af:")) != EOF)
    {
        //todo
    }
}
