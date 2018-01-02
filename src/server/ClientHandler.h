//
// Created by amir on 26/12/17.
//

#ifndef REVERSI_CLIENTHANDLER_H
#define REVERSI_CLIENTHANDLER_H


#include <vector>
#include "GameInfo.h"
#include "CommandManager.h"

class ClientHandler {

    struct DataOfClient{
        ClientHandler *clientHandler;
        long clientSocket;
    };

private:
    vector<GameInfo> *gamesList;
    CommandManager* commandManager;
    vector<pthread_t> threads;
    pthread_t getGet;
public:
    ClientHandler();
    ~ClientHandler();
    static void* handleClient(void *data);
    //void closeThreads();
    void acceptClient(int client);
    void analayzeCommand(int client);
    void handleExit();
    void getClients(long &serverSocket);
    static void* getMore(void* data);

};





#endif //REVERSI_CLIENTHANDLER_H
