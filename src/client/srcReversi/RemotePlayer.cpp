//
// Created by or on 06/12/17.
//
#include <iostream>
#include "../include/RemotePlayer.h"


using namespace std;
RemotePlayer::RemotePlayer(const Value t, const Client *client) : Player(t), client(client) {}

Coordinate RemotePlayer::makeTurn(Logic* logic, Board* originalBoard, Printer* printer,
                                    set<Coordinate> availableMoves) const {

}

void RemotePlayer::sendCoordinate(int x, int y) {

}

void RemotePlayer::getCoordinateFromServer(int x, int y) {

}









