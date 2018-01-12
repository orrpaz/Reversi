//
// Created by or on 22/12/17.
//


#define MSG_LENGTH 200

#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <vector>
#include <string>
#include "GameInfo.h"

using namespace std;
class Command {
public:
    /**
     * run the command
     * @param args  - argument 
     */
    virtual void execute(vector<string> args) = 0;
    /**
     * destructor
     */
    virtual ~Command() {}

protected:
    static const int msgLength = MSG_LENGTH;
    pthread_mutex_t mutex;
};

#endif //REVERSI_COMMAND_H
