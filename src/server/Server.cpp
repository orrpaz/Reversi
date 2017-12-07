//
// Created by or on 05/12/17.
//

#include "Server.h"

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }

    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    while (true) {
        cout << "Waiting for client connections..." << endl;

        // Accept a new client connection
        int firstClient = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client 1 connected" << endl;
        if (firstClient == -1)
            throw "Error on accept Client 1";
        int secondClient = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client 2 connected" << endl;
        if (secondClient == -1)
            throw "Error on accept Client 2";


        givePriority(firstClient, secondClient);

        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                handleClient(firstClient, secondClient);

            } else {
                handleClient(secondClient, firstClient);

            }
        }


        // Close communication with the client
        close(firstClient);
        close(secondClient);

    }
}

void Server::givePriority(int firstClient, int secondClient){
    ssize_t n;
    int turn =1;
    // give 1 to the first client
    n = write(firstClient, &turn, sizeof(turn));
    if(n == -1) {
        cout << "Error writing to socket who's turn it is." << endl;
    }
    turn ++;
    n = write(secondClient, &turn, sizeof(turn));
    if(n == -1) {
        cout << "Error writing to socket who's turn it is." << endl;
    }
}

void Server::handleClient(int fromSocket, int toSocket) {
    char move[6];
    while (true) {
        // Read new exercise arguments
        ssize_t n = read(fromSocket, &move, sizeof(move));
        if (n == -1) {
            cout << "Error reading " << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        cout << "Got move: " << move << endl;
        n = write(toSocket, &move, sizeof(move));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        cout << "Sent Move:" << move << endl;

    }
}

void Server::stop() {
    close(serverSocket);
}