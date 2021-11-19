#include "myClientHeader.h"

int main(int argc, char **argv)
{
    struct sockaddr_in address;

    ////////////////////////////////////////////////////////////////////////////
    // CREATE A SOCKET - this is from the Client Server Example in Moodle
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket error");
        return EXIT_FAILURE;
    }

    ////////////////////////////////////////////////////////////////////////////
    // INIT ADDRESS - this is from the Client Server Example in Moodle
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    //Without this the IP Address in the next isnt shown properly - this is from the Client Server Example in Moodle
    inet_aton(argv[1], &address.sin_addr);

    ////////////////////////////////////////////////////////////////////////////
    // CREATE A CONNECTION - this is from the Client Server Example in Moodle
    if (connect(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
    {
        cout << "Connection with server " << inet_ntoa(address.sin_addr) << " established" << endl;
    }

    serverCommunication();

    ////////////////////////////////////////////////////////////////////////////
    // CLOSES THE DESCRIPTOR - this is from the Client Server Example in Moodle
    close(create_socket);
    return EXIT_SUCCESS;
}