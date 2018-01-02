//
// Created by or on 22/12/17.
//

#ifndef REVERSI_COMMANDMANAGER_H
#define REVERSI_COMMANDMANAGER_H


#include <map>
#include "Command.h"

class CommandManager {
public:
    /**
     * constructor
     * @param gamesList - list names of games 
     * @param mutex - mutex
     */
    CommandManager(vector<GameInfo>*gamesList, pthread_mutex_t &mutex);
    /**
     * destructor
     */
    ~CommandManager();
    /**
     *  execute the command .
     * @param command 
     * @param args 
     */
    void executeCommand(string command,
                        vector<string> args);
private:
    map<string, Command *> commandsMap;
};


#endif //REVERSI_COMMANDMANAGER_H
