//
// Created by or on 06/12/17.
//

#ifndef REVERSI_REMOTEPLAYER_H
#define REVERSI_REMOTEPLAYER_H

#include "Player.h"
class Client;
class RemotePlayer : public Player {
private:
    const Client *client;

public:
    RemotePlayer(const Value t ,const  Client* client);
    void sendCoordinate(int x, int y);
    void getCoordinateFromServer(int x, int y);
    virtual Coordinate makeTurn(Logic* l, Board* b, Printer* printer, set<Coordinate> availableMoves) const;
};


#endif //REVERSI_REMOTEPLAYER_H
