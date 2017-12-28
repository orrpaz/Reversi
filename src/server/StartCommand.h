//
// Created by or on 22/12/17.
//

#ifndef REVERSI_STARTCOMMAND_H
#define REVERSI_STARTCOMMAND_H


#include "Command.h"

class StartCommand : public Command {
public:
    StartCommand (vector<GameInfo> *gamesList);
    virtual void execute(vector<string> args);
    virtual ~StartCommand();

private:
    vector<GameInfo> *gamesList;
};


#endif //REVERSI_STARTCOMMAND_H

// כאן ניצור משחק חדש בשם Name
// נצטרך להוסיף לליסט את שם המשחק
// הוא יחזיק סרבר?