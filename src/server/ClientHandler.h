//
// Created by amir on 26/12/17.
//

#ifndef REVERSI_CLIENTHANDLER_H
#define REVERSI_CLIENTHANDLER_H


#include <vector>
#include "Game.h"
#include "CommandManager.h"

class ClientHandler {
private:
    vector<Game> gamesList;
    CommandManager commandManager;
public:
    void *handleClient(void * socket);
};


#endif //REVERSI_CLIENTHANDLER_H
