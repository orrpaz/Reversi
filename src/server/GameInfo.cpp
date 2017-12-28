//
// Created by or on 24/12/17.
//

#include "GameInfo.h"

GameInfo::GameInfo(string gameName, int clientSocket) {
    gameName_= gameName;
    clientSocket_ = clientSocket;
}
string& GameInfo::getName() const {
    return gameName_;
}
int GameInfo::getClientSocket() const {
    return clientSocket_;
}
