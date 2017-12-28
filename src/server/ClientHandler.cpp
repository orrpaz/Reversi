//
// Created by amir on 26/12/17.
//

#include <unistd.h>
#include <iterator>
#include <sstream>
#include "ClientHandler.h"
#define REQ 30
using namespace std;

ClientHandler::ClientHandler() {
    this->gamesList = new vector<GameInfo>();
    this->commandManager = new CommandManager(this->gamesList);
}

void* ClientHandler::handleClient(void* socket) {

    char request[REQ];

    // נכון?
    int clientSocket=(int)socket;

    ssize_t n = read(clientSocket, &request, sizeof(request));
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



    commandManager->executeCommand(command, vstrings);






}