//
// Created by or on 22/12/17.
//

#include "CommandManager.h"
#include "StartCommand.h"
#include "GamesListCommand.h"
#include "JoinCommand.h"

CommandManager::CommandManager(vector<GameInfo> *gameList) {
    // here we crate all the options of command
    // ctrate StartCommand,CloseCommand,Join,listGame

    commandsMap["join"] = new JoinCommand(gameList);
    commandsMap["list_games"] = new GamesListCommand(gameList);
//    commandsMap["play"] = new PlayCommand();
    commandsMap["start"] = new StartCommand(gameList);

}



void CommandManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}

CommandManager::~CommandManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
