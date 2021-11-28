#We use -std=c++17 because the "inline" keyword was used in the header files to prevent the "multiple definition" Error.

all: myClient myServer

clean:
	rm -f myClient myServer
	clear

myClient: client.cpp clientFunctions.cpp myClientHeader.h;
	g++ -g -Wall -std=c++17 client.cpp clientFunctions.cpp -o myClient
		
myServer: server.cpp serverFunctions.cpp myServerHeader.h; 
	g++ -pthread -g -Wall -std=c++17 server.cpp serverFunctions.cpp -o myServer -lldap -llber
