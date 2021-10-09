#include "myHeader.h"

using namespace std;

//Funktion printUsage um die Usage Meldung auszugeben
void printUsage()
{
    fprintf(stderr, "Usage: ./myfind [-R] [-i] searchpath filename 1 [filename2] ...  [filenameN]\n");
}

// Funktion isDirectory prüft ob der gegebene Pfad ein Folder oder ein File ist
bool isDirectory(char const *path)
{
    DIR *dir = NULL;
    dir = opendir(path);
    // Wenn der Folder nicht geöffnet werden kann ist es kein Folder
    if (dir == NULL)
    {
        return false;
    }
    //Wenn es offen ist, machen wir es zu unt returnen true
    else
    {
        closedir(dir);
        return true;
    }
}

//dirName-> jetzige Ordner der durchsucht werden soll, name -> Datei die gesucht wird, iFlag -> Case Sensitive oder nicht, *found Pointer ob die Datei gefunden wurde oder nicht
void recursiveSearch(string dirName, string name, bool iFlag, bool *found)
{
    char finalPath[PATH_MAX + 1];         //Der Pfad zu gefundener Datei oder weiteren Suche
    struct dirent *direntp;               //aktueller Ordner Pointer
    DIR *dirp = opendir(dirName.c_str()); //der Ordner von dirName wird geöffnet

    //die Schleife listet alle Dateien des Ordners auf und geht sie einzeln durch
    while ((direntp = readdir(dirp)) != NULL && *found == false)
    {
        //Hier wird jeder eintrag des aktuellen Arrays finalPath mit 0 überschrieben
        memset(finalPath, 0, PATH_MAX + 1);
        if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
        {
            strcat(finalPath, dirName.c_str()); //hängt den jetztigen Ordner an das Array finalPath an
            strcat(finalPath, "/");             //Hängt den Schrägstrich an
            strcat(finalPath, direntp->d_name); //die Datei aus dem aktuellen Durchlauf der Schleife wird angehängt

            bool compResult = false; //Datei gefunden bool

            //Auf groß und kleinschreibung achten
            if (iFlag)
            {
                compResult = !strcasecmp(direntp->d_name, name.c_str());
            }
            else
            {
                compResult = !strcmp(direntp->d_name, name.c_str());
            }
            //Datei gefunden?
            if (compResult)
            {
                // Datei pfad ausgeben
                cout << getpid() << ": " << direntp->d_name << ": " << finalPath << endl;
                // Gefunden auf wahr setzen
                *found = true;
            }
            //Wenn es ein Ordner ist, dann tiefer gehen (reskursivität)
            if (isDirectory(finalPath))
            {
                recursiveSearch(finalPath, name, iFlag, found);
            }
        }
    }
    closedir(dirp); //Ordner schließen damit man keine Zombie Prozesse hat
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
                cout << "Recursive Search: " << argv[i] << endl;
                recursiveSearch(dir, argv[i], iFlag, foundP);
            }
            else
            {
                cout << "Search: " << dir.c_str() << ", " << files[i] << endl;

                char pathBuf[PATH_MAX + 1];       //Pfad Buffer für Ausgabe
                struct dirent *direntp;           //aktueller Ordner Pointer
                DIR *dirp = opendir(dir.c_str()); //Angegebenen Ordner öffnen

                //Dateien auflisten und nach einander öffnen
                while ((direntp = readdir(dirp)) != NULL && *foundP == false)
                {
                    bool compResult = false; //Gefunden bool
                    if (iFlag)               //Auf groß und kleinschreibung achten
                    {
                        compResult = !strcasecmp(direntp->d_name, argv[i]); //Darauf achten
                    }
                    else
                    {
                        compResult = !strcmp(direntp->d_name, argv[i]); //Nicht darauf achten
                    }
                    if (compResult) //Gefunden?
                    {
                        realpath(direntp->d_name, pathBuf);                                     //Kompletten Pfad bekommen
                        cout << getpid() << ": " << direntp->d_name << ": " << pathBuf << endl; //Gefunden Nachricht ausgeben
                        *foundP = true;                                                         //Gefunden Bool setzen
                    }
                }
                // do this to have no zombies process after
                while ((closedir(dirp) == -1) && (errno == EINTR))
                    ;
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
