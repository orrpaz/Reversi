////
//// Created by or on 05/12/17.
////
//
#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H
//
//
#include "ClientHandler.h"



#include <pthread.h>
class Server {
public:
    Server(int port,ClientHandler *clientHandler);
    void start();
    void stop();
    void close_();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    pthread_t serverThreadId;
    ClientHandler* clientHandler;
};

#endif //REVERSI_SERVER_H
