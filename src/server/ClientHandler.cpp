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
    this->gamesList = new vector<Game>();
    this->commandManager = new CommandManager(this->gamesList);
}

void* ClientHandler::handleClient(void* socket) {

    char request[REQ];

    // נכון?
    int socket_=(int)socket;

    ssize_t n = read(socket_, &request, sizeof(request));
    if (n == -1) {
        throw "Error reading from socket";
    }
    string strBuff(request);
    istringstream buf(strBuff);
    istream_iterator<string> begin(buf);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    // copy the first string to command
    string command = vstrings.at(0);
    // delete the first string in vector.
    vstrings.erase(vstrings.begin());
    //
    // קריאה של הארגומנטים
    // צריך לשלוח גם את הסוקט?

    this->commandManager->executeCommand(command, vstrings);






}