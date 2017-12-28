//
// Created by or on 24/12/17.
//

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H


#include <iostream>
using namespace std;

class GameInfo {
public:
    GameInfo(string gameName, int clientSocket);
    string& getName() const;
    int getClientSocket() const;


private:
    string gameName;
    int clientSocket;
};

#endif //REVERSI_GAME_H
