//
// Created by or on 06/12/17.
//

#ifndef REVERSI_REMOTEPLAYER_H
#define REVERSI_REMOTEPLAYER_H

#include "Player.h"
#include "Client.h"

class RemotePlayer : public Player {
private:
    const Client *client;
    int priority;
    Printer* printer;

public:
    RemotePlayer(const Value t ,const  Client* client, Printer* printer, int priority);
    void sendCoordinate(Coordinate &coordinate) const;
    void getCoordinateFromServer(Coordinate &coordinate) const;
    void setPriority(int a);
    virtual Coordinate makeTurn(Logic* l, Board* b, set<Coordinate> availableMoves);

    virtual void startTurn(const Value &sign, Coordinate c) const;
    virtual void cantMove(Logic* l) const;
};


#endif //REVERSI_REMOTEPLAYER_H
