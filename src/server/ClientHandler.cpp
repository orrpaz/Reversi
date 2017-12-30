//
// Created by amir on 26/12/17.
//

#include <unistd.h>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include "ClientHandler.h"
#define REQ 200
//#define commandManager ClientHandler::commandManager;
using namespace std;

ClientHandler::ClientHandler() {
    gamesList = new vector<GameInfo>();
    this->commandManager = new CommandManager(gamesList);
}
ClientHandler::~ClientHandler() {
    delete gamesList;
    delete commandManager;

}
void ClientHandler::acceptClient(int client) {
    pthread_t new_thread;
    DataOfClient *dataOfClient = new DataOfClient();
    dataOfClient->clientHandler = this;
    dataOfClient->clientSocket = client;
    int rc = pthread_create(&new_thread, NULL, handleClient, (void *)dataOfClient);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    threads.push_back(new_thread);
}

 void* ClientHandler::handleClient(void* data) {
    DataOfClient *dataOfClient = (DataOfClient*)data;
    ClientHandler *ptr = dataOfClient->clientHandler;
    ptr->analayzeCommand(dataOfClient->clientSocket);


//    char request[REQ];
//
//    // נכון?
//    //long clientSocket=(long)socket;
//    int clientSocket=(long)socket;
//    //ssize_t n = read((int)clientSocket, &request, sizeof(request));
//    ssize_t n = read(clientSocket, &request, sizeof(request));
//    if (n == -1) {
//        throw "Error reading from socket";
//    }
//    //Convert char into string
//    string strBuff(request);
//    istringstream buf(strBuff);
//    //split by ' '
//    istream_iterator<string> begin(buf);
//    istream_iterator<string> end;
//    vector<string> vstrings(begin, end);
//    // get the first string to command
//    string command = vstrings.at(0);
//    // delete the first string in vector.
//    vstrings.erase(vstrings.begin());
//
//    //Convert int into string
//    std::ostringstream ss;
//    ss << clientSocket;
//    //insert the client_socket as the first param in the vector
//    vstrings.insert(vstrings.begin(), ss.str());
//
//
//    //Run the command (Start, listGames, join, close)
//    commandManager->executeCommand(command, vstrings);

}
void ClientHandler::analayzeCommand(int client) {
    char request[REQ];

    // נכון?
    //long clientSocket=(long)socket;
    int clientSocket = client;
    //ssize_t n = read((int)clientSocket, &request, sizeof(request));
    ssize_t n = read(clientSocket, request, sizeof(request));
    if (n == -1) {
        throw "Error reading from socket";
    }
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


    //Run the command (Start, listGames, join, close)
    commandManager->executeCommand(command, vstrings);

}