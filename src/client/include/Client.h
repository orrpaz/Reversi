//
// Created by or on 06/12/17.
//

#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H

//#include "Cell.h"

class Client {
public:
    Client(const char *serverIP, int serverPort);
    Client(const char* fileName);
    void connectToServer();
    int getPriorityValue();
    const char * getserverip(){
        return serverIP;
    }
private:
    char serverIP[16];
    int serverPort;
    int clientSocket;
};


#endif //REVERSI_CLIENT_H