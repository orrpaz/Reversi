//
// Created by or on 24/12/17.
//

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H


#include <iostream>
using namespace std;
class GameInfo {
public:
    /**
     * constructor.
     * @param gameName  - the name of room
     * @param clientSocket 
     */
    GameInfo(string gameName, int clientSocket);
    /**
     * @return the name
     */
    string getName() const;
    /**
     * @return the first client socket 
     */
    int getFirstClient() const;
    /**
     * 
     * @return the second client socket 
     */
    int getSecondClient() const;
    /**
     * set new socket
     * @param socket 
     */
    void setSecondClient(int &socket);


private:
    string gameName;
    int clientFirst;
    int clientSecond;
};

#endif //REVERSI_GAME_H
