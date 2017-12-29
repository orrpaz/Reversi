//
// Created by or on 24/12/17.
//

#include "GameInfo.h"

GameInfo::GameInfo(string name, int socket) {
    gameName= name;
    clientSocket = socket;
}
string GameInfo::getName() const {
    return gameName;
}
int GameInfo::getClientSocket() const {
    return clientSocket;
}
