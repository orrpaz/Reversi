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
    threads = new vector<pthread_t>();
    this->commandManager = new CommandManager(gamesList, mutex);
}
ClientHandler::~ClientHandler() {
    cout <<"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    delete gamesList;
    delete threads;
    delete commandManager;

}
void ClientHandler::clientThreads(int client) {
    cout << "Before Size:" << threads->size() << endl;
    pthread_t new_thread;
    DataOfClient *dataOfClient = new DataOfClient();
    dataOfClient->clientHandler = this;
    dataOfClient->clientSocket = client;
    int rc = pthread_create(&new_thread, NULL, handleClient, (void *)dataOfClient);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    pthread_mutex_lock(&threadsMutex);
    threads->push_back(new_thread);
    pthread_mutex_unlock(&threadsMutex);

    cout << "After Size:" << threads->size() << endl;
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

}
void ClientHandler::handleExit() {
    pthread_mutex_lock(&threadsMutex);
    vector<pthread_t>::iterator it;
    cout <<"size \n";
    cout << threads->size() <<endl;
    for (it = threads->begin(); it != threads->end(); ++it) {

        pthread_cancel((*it));

    }
    pthread_mutex_unlock(&threadsMutex);

    vector<GameInfo>::iterator iterGameRoom;
    pthread_mutex_lock(&mutex);
    for (iterGameRoom = gamesList->begin(); iterGameRoom != gamesList->end(); ++iterGameRoom) {
        close((*iterGameRoom).getFirstClient());
        if ((*iterGameRoom).getSecondClient() != -1)
            close((*iterGameRoom).getSecondClient());

    }
    pthread_mutex_unlock(&mutex);


    cout << "\nExit was typed\n";
}

