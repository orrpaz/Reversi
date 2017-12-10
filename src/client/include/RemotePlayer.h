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
    int priority;

public:
    RemotePlayer(const Value t ,const  Client* client, int priority);
    void sendCoordinate(Coordinate &coordinate) const;
    void getCoordinateFromServer(Coordinate &coordinate) const;
    void setPriority(int a);
    virtual Coordinate makeTurn(Logic* l, Board* b, Printer* printer, set<Coordinate> availableMoves);

    virtual void startTurn(Printer* printer, const Value &sign, Coordinate c) const;
    virtual void cantMove(Printer* printer, Logic* l) const;
};


#endif //REVERSI_REMOTEPLAYER_H
