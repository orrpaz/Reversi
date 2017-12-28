//
// Created by or on 22/12/17.
//

#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <vector>
#include <string>
#include "GameInfo.h"

using namespace std;
class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}

protected:
    pthread_mutex_t mutex;
};

#endif //REVERSI_COMMAND_H
