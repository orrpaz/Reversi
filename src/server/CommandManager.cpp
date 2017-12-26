//
// Created by or on 22/12/17.
//

#include "CommandManager.h"
#include "StartCommand.h"

CommandsManager::CommandsManager() {
    // here we crate all the options of command
    // ctrate StartCommand,CloseCommand,Join,listGame

//    commandsMap["close"] = new CloseCommand();
//    commandsMap["join"] = new JoinCommand();
//    commandsMap["list_games"] = new ListGamesCommand();
//    commandsMap["play"] = new PlayCommand();
    commandsMap["start"] = new StartCommand();

}



void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
