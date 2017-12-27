//
// Created by or on 05/12/17.
//

#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H


#include "ClientHandler.h"

class Server {
private:
    int port;
    int serverSocket;
    ClientHandler &clientHandler;

    bool handleClient(int firstClient, int secondClient);

    void givePriority(int firstClient, int secondClient);

public:
    Server(int port,ClientHandler &clientHandler);

    Server(char *file);

    void start();

    void stop();

    static void *startClose(void *object);

    void close_();
};

#endif //REVERSI_SERVER_H
