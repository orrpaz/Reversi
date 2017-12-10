//
// Created by or on 05/12/17.
//

#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H


class Server {
private:
    int port;
    int serverSocket;
    bool handleClient(int firstClient, int secondClient);
    void givePriority(int firstClient, int secondClient);

public:
    Server(int port);
    Server(char *file);
    void start();
    void stop();
};


#endif //REVERSI_SERVER_H
