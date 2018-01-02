//
// Created by or on 06/12/17.
//

#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H

#include "Printer.h"

#define SIZEIP 16

class Client {
public:
    /**
     * constructor
     * @param serverIP 
     * @param serverPort 
     */
    Client(const char *serverIP, int serverPort);
    /**
     * constructor
     * @param fileName 
     */
    Client(const char* fileName);
    /**
     * connecting to server.
     */
    void connectToServer();
    /**
     * close socket.
     */
    void closeClient();
    /**
     * 
     * @return the client socket 
     */
    int getClientSocket() const;
    /**
     * 
     * @return the priority. 
     */
    int getPriorityValue();
    /**
     * get command from user.
     * @param p - printer
     * @param first - boolean 
     * @return 
     */
    int getCommand(Printer* p, bool first);
    const char * getServerIp(){
        return serverIP;
    }

private:
    char serverIP[SIZEIP];
    int serverPort;
    int clientSocket;
};


#endif //REVERSI_CLIENT_H