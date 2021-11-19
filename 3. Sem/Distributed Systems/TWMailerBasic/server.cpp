#include "myServerHeader.h"

int main(int argc, char **argv)
{
    //- this is from the Client Server Example in Moodle
    dirName = argv[2];

    ////////////////////////////////////////////////////////////////////////////
    //Signal Handler - this is from the Client Server Example in Moodle
    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        perror("signal can not be registered");
        return EXIT_FAILURE;
    }

    ////////////////////////////////////////////////////////////////////////////
    //Create socket - this is from the Client Server Example in Moodle
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket error");
        return EXIT_FAILURE;
    }

    ////////////////////////////////////////////////////////////////////////////
    // SET SOCKET OPTIONS - this is from the Client Server Example in Moodle
    if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEADDR, &reuseValue, sizeof(reuseValue)) == -1)
    {
        perror("set socket options - reuseAddr");
        return EXIT_FAILURE;
    }

    if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEPORT, &reuseValue, sizeof(reuseValue)) == -1)
    {
        perror("set socket options - reusePort");
        return EXIT_FAILURE;
    }

    ////////////////////////////////////////////////////////////////////////////
    // INIT ADDRESS - this is from the Client Server Example in Moodle
    memset(&address, 0, sizeof(address)); 
    address.sin_family = AF_INET;         
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    ////////////////////////////////////////////////////////////////////////////
    // ASSIGN AN ADDRESS WITH PORT TO SOCKET - this is from the Client Server Example in Moodle
    if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("bind error");
        return EXIT_FAILURE;
    }

    ////////////////////////////////////////////////////////////////////////////
    // ALLOW CONNECTION ESTABLISHING - this is from the Client Server Example in Moodle
    if (listen(create_socket, 5) == -1)
    {
        perror("listen error");
        return EXIT_FAILURE;
    }

    while (!abortRequested)
    {
        cout << "Waiting for connections..." << endl;

        /////////////////////////////////////////////////////////////////////////
        // ACCEPTS CONNECTION SETUP - this is from the Client Server Example in Moodle
        addrlen = sizeof(struct sockaddr_in);
        if ((new_socket = accept(create_socket, (struct sockaddr *)&cliaddress, &addrlen)) == -1)
        {
            if (abortRequested)
            {
                perror("accept error after aborted");
            }
            else
            {
                perror("accept error");
            }
            break;
        }

        /////////////////////////////////////////////////////////////////////////
        // START CLIENT - this is from the Client Server Example in Moodle
        cout << "Client connected from " << inet_ntoa(cliaddress.sin_addr) << ":" << ntohs(cliaddress.sin_port) << endl;
        clientCommunication(&new_socket); // returnValue can be ignored
        new_socket = -1;
    }
    return EXIT_SUCCESS;
}