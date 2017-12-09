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
    cout << "My priority: " << priority << endl;
}
void RemotePlayer::setPriority(int a) {
    priority = a;
}

Coordinate RemotePlayer::makeTurn(Logic* logic, Board* originalBoard, Printer* printer,
                                    set<Coordinate> availableMoves) const {
    Coordinate c = logic->getLastMove();
    cout << "Last move:" << c.getRow() << "," << c.getCol() << endl;
   // if (priority == 1) {
    sendCoordinate(c);
//    }
    getCoordinateFromServer(c);
    cout << "The gotted move:" << c.getRow() << "," << c.getCol() << endl;
    return c;
}



void RemotePlayer::sendCoordinate(Coordinate &coordinate) const{
    cout << "Send: " << coordinate.getRow() << "," << coordinate.getCol() << endl;
    int move[2];
    move[0] = coordinate.getRow();
    move[1] = coordinate.getCol();
    ssize_t n = write(client->getClientSocket(),&move ,sizeof (move));
    if (n == -1) {

        throw "Error writing x to socket";
    }
}

void RemotePlayer::getCoordinateFromServer(Coordinate &coordinate) const{
    int move[2];
    ssize_t n = read(client->getClientSocket(),&move ,sizeof (move));
    cout << "Got: " << coordinate.getRow() << "," << coordinate.getCol() << endl;
    if (n == -1) {

        throw "Error writing x to socket";
    }
    coordinate = Coordinate(move[0], move[1]);
}

void RemotePlayer::startTurn(Printer* printer) const {
    printer->massage("waiting for other player's move...\n");
}
void RemotePlayer::cantMove(Printer* printer) const {
    printer->cantMove();
}










