//
// Created by or on 22/12/17.
//

#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <vector>
#include <string>
#include "Game.h"

using namespace std;
class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}
private:
    vector<Game*> listOfGame;
};

#endif //REVERSI_COMMAND_H
