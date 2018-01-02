//////
////// Created by or on 05/12/17.
//////
////
//#include "Server.h"
//
//#include "Server.h"
//#include "ClientHandler.h"
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <unistd.h>
//#include <string.h>
//#include <iostream>
//#include <stdio.h>
//#include <vector>
//#include <cstdlib>
//
//using namespace std;
//#define MAX_CONNECTED_CLIENTS 2
//
//Server::Server(int port,ClientHandler &clientHandler): port(port), serverSocket(0),clientHandler(clientHandler) {
//    cout << "Server" << endl;
//}
//
//void Server::start() {
//    // Create a socket point
//    pthread_t closeThread;
//    int rc =pthread_create(&serverThreadId, NULL,startClose, (void*)this);  // לבדוק
//    if (rc) {
//        cout << "Error: unable to create thread, " << rc << endl;
//        exit(-1);
//    }
//    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//    if (serverSocket == -1) {
//        throw "Error opening socket";
//    }
//
//    // Assign a local address to the socket
//    struct sockaddr_in serverAddress;
//    bzero((void *)&serverAddress, sizeof(serverAddress));
//    serverAddress.sin_family = AF_INET;
//    serverAddress.sin_addr.s_addr = INADDR_ANY;
//    serverAddress.sin_port = htons(port);
//    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
//        throw "Error on binding";
//    }
//    // Start listening to incoming connections
//    listen(serverSocket, MAX_CONNECTED_CLIENTS);
//    // Define the client socket's structures
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
//        //התקבל קליינט
//
//        //יוצרים טרדים
//        clientHandler.clientThreads(firstClient);
//
//    }
//
//}
//
//void Server::givePriority(int firstClient, int secondClient){
//    ssize_t n;
//    int turn =1;
//    // give 1 to the first client
//    n = write(firstClient, &turn, sizeof(turn));
//    if(n == -1) {
//        cout << "Error writing to socket who's turn it is." << endl;
//    }
//    turn ++;
//    n = write(secondClient, &turn, sizeof(turn));
//    if(n == -1) {
//        cout << "Error writing to socket who's turn it is." << endl;
//    }
//}
//
//void Server::stop() {
////    pthread_cancel(serverThreadId);
//    close(serverSocket);
//    cout << "Server stopped" << endl;
//}
//
//void* Server::startClose(void *object) {
//
//    Server *ptr = (Server *) object;
//    ptr->close_();
//}
//
//void Server::close_() {
//    bool isExit = false;
//    string str;
//    while(!isExit) {
//        cin >> str;
//        if (str == "exit") {
//            isExit = true;
//            clientHandler.handleExit();
//            stop();
//        }
//    }
//    // close threads.
//}


#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define MAX_CONNECTED_CLIENTS 10
#define MAX_COMMAND_LEN 20
static void *acceptClients(void *);

struct info {
    int serverSocket;
    ClientHandler *handler;
};

Server::Server(int port,ClientHandler *clientHandler): port(port), serverSocket(0),clientHandler(clientHandler) {
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
    if (bind(serverSocket, (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connection requests
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    info info_;
    info_.serverSocket = serverSocket;
    info_.handler = clientHandler;

    int rc = pthread_create(&serverThreadId, NULL, &acceptClients, &info_);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        return;
    }
    string exitCommand;
    do {
        cin >> exitCommand;
    }
    while (exitCommand != "exit");
    clientHandler->handleExit();
    stop();



}
static void *acceptClients(void *args) {
    struct info *information = (struct info *) args;
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(information->serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";
        information->handler->clientThreads(clientSocket);


//        pthread_t threadId;
//        pthread_create(&threadId, NULL, &handleClient, (void *)clientSocket);
    }
}


void Server::stop() {
    pthread_cancel(serverThreadId);
    close(serverSocket);
    cout << "Server stopped" << endl;
}

void Server::close_() {
    bool isExit = false;
    string str;
    while (!isExit) {
        cin >> str;
        if (str == "exit") {
            isExit = true;
            clientHandler->handleExit();
            stop();
        }
    }
}
//}