//
// Created by or on 06/12/17.
//
#include <iostream>
#include <string>
#include <unistd.h>
#include "../include/RemotePlayer.h"
#include "../include/Client.h"



using namespace std;
RemotePlayer::RemotePlayer(const Value t, const Client *client) : Player(t), client(client) {}

Coordinate RemotePlayer::makeTurn(Logic* logic, Board* originalBoard, Printer* printer,
                                    set<Coordinate> availableMoves) const {

    Coordinate c = originalBoard->getLastMoved();
    sendCoordinate(c);
    getCoordinateFromServer(c);
    return c;
}

void RemotePlayer::sendCoordinate(Coordinate coordinate) const{


    ssize_t n = write(client->getClientSocket(),&coordinate ,sizeof (Coordinate));
    if (n == -1) {

        throw "Error writing x to socket";
    }
}

void RemotePlayer::getCoordinateFromServer(Coordinate coordinate) const{
    ssize_t n = read(client->getClientSocket(),&coordinate ,sizeof (Coordinate));
    if (n == -1) {

        throw "Error writing x to socket";
    }
}









