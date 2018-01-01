//
// Created by or on 05/12/17.
//

#include "Server.h"

#include "Server.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port,ClientHandler &clientHandler): port(port), serverSocket(0),clientHandler(clientHandler) {
    cout << "Server" << endl;
}

void Server::start() {
    // Create a socket point
    pthread_t closeThread;
    int rc =pthread_create(&closeThread, NULL,startClose, (void*)this);  // לבדוק
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
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
    socklen_t clientAddressLen = sizeof((struct sockaddr *)&clientAddress);
//    socklen_t clientAddressLen = sizeof(struct sockaddr);


    //

    cout << "Waiting for client connections..." << endl;
    while (true) {
        // Accept a new client connection
        int firstClient = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (firstClient == -1)
            throw "Error on accept Client 1";
        //התקבל קליינט

        //יוצרים טרדים
        clientHandler.acceptClient(firstClient);

    }

    //
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

        int i = 0;
        bool flag = true;
        while(flag){
            if (i % 2 == 0) {
                flag = handleClient(firstClient, secondClient);

            } else {
                flag = handleClient(secondClient, firstClient);

            }
            i++;
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

//bool Server::handleClient(int fromSocket, int toSocket) {
//
//    char request[20];
//    ssize_t n = read(fromSocket, &request, sizeof(request));
//
//




//
//    int move[2];
//    ssize_t n = read(fromSocket, &move, sizeof(move));
//    if (n == -1) {
//        cout << "Error reading " << endl;
//        return false;
//    }
//    if (n == 0) {
//        cout << "Client disconnected" << endl;
//        return false;
//    }
//    cout << "Got move: " << move[0] + 1 << "," << move[1] + 1 << endl;
//    if ((move[0] == -1) && (move[1] == -1)) {
//        return false;
//    }
//
//
//    n = write(toSocket, &move, sizeof(move));
//    if (n == -1) {
//        cout << "Error writing to socket" << endl;
//        return false;
//    }
//    cout << "Sent move: " << move[0] + 1 << "," << move[1] + 1 << endl;
//}

void Server::stop() {
    close(serverSocket);
}

void* Server::startClose(void *object) {

    Server *ptr = (Server *) object;
    ptr->close_();
}

void Server::close_() {
    bool flag = true;
    string str;
    while(flag) {
        cin >> str;
        if (str.compare("exit") == 0) {
            flag = false;
            clientHandler.handleExit();
        }
    }
    // close threads.
}