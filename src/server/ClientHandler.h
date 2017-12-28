//
// Created by amir on 26/12/17.
//

#ifndef REVERSI_CLIENTHANDLER_H
#define REVERSI_CLIENTHANDLER_H


#include <vector>
#include "GameInfo.h"
#include "CommandManager.h"

class ClientHandler {
private:
    vector<GameInfo> *gamesList;
    CommandManager* commandManager;
public:
    ClientHandler();
    ~ClientHandler();
    void *handleClient(void * socket);
    void closeThreads();

};


#endif //REVERSI_CLIENTHANDLER_H
