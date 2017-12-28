//
// Created by amir on 28/12/17.
//

#ifndef REVERSI_JOINCOMMAND_H
#define REVERSI_JOINCOMMAND_H


#include "Command.h"

class JoinCommand : public Command {
public:
    JoinCommand (vector<GameInfo> *gamesList);
    virtual void execute(vector<string> args);
    virtual ~JoinCommand();

private:
    vector<GameInfo>* gamesList;
};

#endif //REVERSI_JOINCOMMAND_H
