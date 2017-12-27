//
// Created by or on 22/12/17.
//

#ifndef REVERSI_COMMANDMANAGER_H
#define REVERSI_COMMANDMANAGER_H


#include <map>
#include "Command.h"

class CommandManager {
public:
    CommandManager();
    ~CommandManager();
    void executeCommand(string command,
                        vector<string> args);
private:
    map<string, Command *> commandsMap;
};


#endif //REVERSI_COMMANDMANAGER_H