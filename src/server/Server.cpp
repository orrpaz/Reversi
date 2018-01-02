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
#define MAX_CONNECTED_CLIENTS 10

Server::Server(int port):
        port(port), serverSocket(0),serverThreadId(0) {
    clientHandler = new ClientHandler();
    cout << "Server" << endl;
}

//
static void* acceptClients(void*);
static void* handleClient(void*);
//
//void Server::start() {
//    // Create a socket point
//    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//    if (serverSocket == -1) {
//        throw "Error opening socket";
//    }
//    // Assign a local address to the socket
//    struct sockaddr_in serverAddress;
//    bzero((void *)&serverAddress, sizeof(serverAddress));
//    serverAddress.sin_family = AF_INET;
//    serverAddress.sin_addr.s_addr = INADDR_ANY;
//    serverAddress.sin_port = htons(port);
//    if (bind(serverSocket, (struct sockaddr *)&serverAddress,
//             sizeof(serverAddress)) == -1) {
//        throw "Error on binding";
//    }
//    // Start listening to incoming connection requests
//    listen(serverSocket, MAX_CONNECTED_CLIENTS);
//    pthread_create(&serverThreadId, NULL, &acceptClients, (void *)serverSocket);
//}
//
//void Server::stop() {
//    pthread_cancel(serverThreadId);
//    close(serverSocket);
//    cout << "Server stopped" << endl;
//}

void Server::start() {
//    pthread_t closeThread;
//    int rc =pthread_create(&closeThread, NULL,startClose, (void*)this);  // לבדוק
//    if (rc) {
//        cout << "Error: unable to create thread, " << rc << endl;
//        exit(-1);
//    }
//    cout << "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\n";
//    cout << "VVV\n";

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
    clientHandler->getClients(serverSocket);
    cout << "ABCABCABC\n";
    cout << "server\n";
    close_();
    cout << "EEEEEEEEEEEEEEEEEEEEEEEE\n";
    cout << "EEEEEEEEEEEEEEEEEEEEEEEE\n";
    // Define the client socket's structures
//    struct sockaddr_in clientAddress;
//    socklen_t clientAddressLen = sizeof((struct sockaddr *)&clientAddress);
////    socklen_t clientAddressLen = sizeof(struct sockaddr);
//
//
//    //
//
//    cout << "Waiting for client connections..." << endl;
//    while (true) {
//        // Accept a new client connection
//        int firstClient = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
//        cout << "Client connected" << endl;
//        if (firstClient == -1)
//            throw "Error on accept Client 1";
//
//        //send it to func that will create a thread
//        clientHandler.acceptClient(firstClient);
//
//    }
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


void Server::stop() {
    cout << "Amir\n";
    close(serverSocket);
    cout << "aaa\n";
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
        if (str == "exit") {
            flag = false;
            clientHandler->handleExit();

            stop();
        }
    }
    cout << "CCCCCCCCCCCCCCCCCCCCCCCCCCCC\n";
    // close threads.
}