//
// Created by or on 24/12/17.
//

#include "Game.h"

Game::Game(string gameName, int clientSocket) {
    gameName_= gameName;
    clientSocket_ = clientSocket;
}
string& Game::getName() const {
    return gameName_;
}
int Game::getClientSocket() const {
    return clientSocket_;
}
