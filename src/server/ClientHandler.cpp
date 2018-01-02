//
// Created by amir on 26/12/17.
//

#include <unistd.h>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <netinet/in.h>
#include "ClientHandler.h"
#define REQ 200
#define MAX_COMMAND_LEN 20

//#define commandManager ClientHandler::commandManager;
using namespace std;

ClientHandler::ClientHandler() {
    gamesList = new vector<GameInfo>();
    this->commandManager = new CommandManager(gamesList);
}
ClientHandler::~ClientHandler() {
    cout << "TTTTTTTTTTTTTTTTTTTTTT\n";
    delete gamesList;
    delete commandManager;

}
void ClientHandler::getClients(long &serverSocket) {

    cout << "Here111\n";

    DataOfClient *dataOfClient = new DataOfClient();
    dataOfClient->clientHandler = this;
    dataOfClient->clientSocket = serverSocket;
    int rc = pthread_create(&getGet, NULL, getMore, (void *)dataOfClient);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    cout << "Here111\n";
//    while (true) {
//        ;
//    }

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
//        acceptClient(firstClient);
//    }
}
void* ClientHandler::getMore(void* data) {
    DataOfClient *dataOfClient = (DataOfClient*)data;
    ClientHandler *ptr = dataOfClient->clientHandler;
    long serverSocket = (dataOfClient->clientSocket);


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

        //send it to func that will create a thread
        ptr->acceptClient(firstClient);
    }
}
void ClientHandler::acceptClient(int client) {
    cout << "Before Size:" << threads.size() << endl;
    pthread_t new_thread;
    DataOfClient *dataOfClient = new DataOfClient();
    dataOfClient->clientHandler = this;
    dataOfClient->clientSocket = client;
    int rc = pthread_create(&new_thread, NULL, handleClient, (void *)dataOfClient);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    pthread_mutex_t threadsMutex;
    pthread_mutex_lock(&threadsMutex);

    //insert the tread to the vector
    threads.push_back(new_thread);
    pthread_mutex_unlock(&threadsMutex);

    cout << "After Size:" << threads.size() << endl;
}

 void* ClientHandler::handleClient(void* data) {
    DataOfClient *dataOfClient = (DataOfClient*)data;
    ClientHandler *ptr = dataOfClient->clientHandler;
    ptr->analayzeCommand(dataOfClient->clientSocket);
}
void ClientHandler::analayzeCommand(int client) {
    char request[REQ];

    //long clientSocket=(long)socket;
    int clientSocket = client;
    //ssize_t n = read((int)clientSocket, &request, sizeof(request));
    ssize_t n = read(clientSocket, request, sizeof(request));
    if (n == -1) {
        throw "Error reading from socket";
    }
    cout << request << endl;
    //Convert char into string
    string strBuff(request);
    istringstream buf(strBuff);
    //split by ' '
    istream_iterator<string> begin(buf);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    // get the first string to command
    string command = vstrings.at(0);
    // delete the first string in vector.
    vstrings.erase(vstrings.begin());

    //Convert int into string
    std::ostringstream ss;
    ss << clientSocket;
    //insert the client_socket as the first param in the vector
    vstrings.insert(vstrings.begin(), ss.str());
    cout << "command: " << command << endl;
    vector<string>::iterator it;
    for (it = vstrings.begin(); it != (vstrings).end(); it++) {
        cout << (*it) << endl;
    }

        //Run the command (Start, listGames, join, close)
    commandManager->executeCommand(command, vstrings);
    cout << "I finished\n";
    
    vector<pthread_t>::iterator iter;
    for (iter = threads.begin(); iter != (threads).end(); iter++) {
        if((*iter) == pthread_self()){
            threads.erase(iter);
            break;
        }
    }

}
void ClientHandler::handleExit() {
    pthread_cancel(getGet);
    vector<pthread_t>::iterator it;
    for (it = threads.begin(); it != threads.end();) {
        // לסגור sockets
        pthread_cancel((*it));
        threads.erase(it);
    }
    cout << "Size: " << threads.size() << endl;
    cout << "\nExit was typed\n";
}

//static void *acceptClients(void *socket) {
//    long serverSocket = (long)socket;
//    // Define the client socket's structures
//    struct sockaddr_in clientAddress;
//    socklen_t clientAddressLen = sizeof(clientAddress);
//
//
//    while (true) {
//        cout << "Waiting for client connections..." << endl;
//        // Accept a new client connection
//        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress,
//                                  &clientAddressLen);
//        cout << "Client connected" << endl;
//        if (clientSocket == -1)
//            throw "Error on accept";
//        pthread_t threadId;
//        pthread_create(&threadId, NULL, &handleClient, (void *)clientSocket);
//    }
//}
//static void *handleClient(void *socket) {
//    long clientSocket = (long)socket;
//    char commandStr[MAX_COMMAND_LEN];
//    // Read the command from the socket
//    int n = read(clientSocket, commandStr, MAX_COMMAND_LEN);
//    if (n == -1) {
//        cout << "Error reading command" << endl;
//        return NULL;
//    }
//    cout << "Received command: " << commandStr << endl;
//    // Split the command string to the command name and the arguments
//    string str(commandStr);
//    istringstream iss(str);
//    string command;
//    iss >> command;
//    vector<string> args;
//    while (iss) {
//        string arg;
//        iss >> arg;
//        args.push_back(arg);
//    }
//    CommandsManager::getInstance()->executeCommand(command, args, clientSocket);
//    return NULL;
//}