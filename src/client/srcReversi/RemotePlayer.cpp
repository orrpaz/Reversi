//
// Created by or on 06/12/17.
//
#include <iostream>
#include <string>
#include <unistd.h>
#include "../include/RemotePlayer.h"
#include "../include/Client.h"



using namespace std;
RemotePlayer::RemotePlayer(const Value t, const Client *client,
                           int p) : Player(t), priority(p), client(client){
}
void RemotePlayer::setPriority(int a) {
    priority = a;
}

Coordinate RemotePlayer::makeTurn(Logic* logic, Board* originalBoard, Printer* printer,
                                    set<Coordinate> availableMoves) {
    Coordinate c = logic->getLastMove();
    if (priority == 1) { //We dont want the second player to send coordinate at first turn
    sendCoordinate(c);
    }

//    if(availableMoves.empty()) { //in the final move, the
  //      return Coordinate(-1,-1);
    //}

    priority = 1;
    getCoordinateFromServer(c);
    return c;
}



void RemotePlayer::sendCoordinate(Coordinate &coordinate) const{
    int move[2];
    move[0] = coordinate.getRow();
    move[1] = coordinate.getCol();
    ssize_t n = write(client->getClientSocket(),&move ,sizeof (move));
    if (n == -1) {
        throw "Error writing move to socket";
    }
}

void RemotePlayer::getCoordinateFromServer(Coordinate &coordinate) const{
    int move[2];
    ssize_t n = read(client->getClientSocket(),&move ,sizeof (move));
    if (n == -1) {

        throw "Error reading move from socket";
    }
    coordinate = Coordinate(move[0], move[1]);
}

void RemotePlayer::startTurn(Printer* printer, const Value &sign, Coordinate c) const {
    printer->massage("waiting for other player's move...\n");
}
void RemotePlayer::cantMove(Printer* printer, Logic* l) const {

    Coordinate c = l->getLastMove();
    sendCoordinate(c);
    getCoordinateFromServer(c);

    /*
    int move[2];
    move[0] = -2;
    move[1] = -2;
    ssize_t n = write(client->getClientSocket(),&move ,sizeof (move));
    if (n == -1) {
        throw "Error writing x to socket";
    }
     */
    if ((c.getRow() == - 2) && (c.getCol() == -2)) {
        l->couldntMove();
    }
}










