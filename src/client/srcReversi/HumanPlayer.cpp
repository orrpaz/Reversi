//
// Created by amir on 02/11/17.
//

#include <iostream>
#include "../include/Player.h"
#include "../include/HumanPlayer.h"

using namespace std;
    HumanPlayer::HumanPlayer(const Value t): Player(t) {
}
HumanPlayer::~HumanPlayer() {
}
Coordinate HumanPlayer::makeTurn(Logic* l, Board* b, Printer* printer, set<Coordinate> availableMoves){
    printer->availableMoves(availableMoves); // Print available moves
    int row, col;
    printer->massage("\nEnter Row: ");
    cin >> row;
    while ((!cin) || (row < 1)) {
        printer->massage("Input MUST be a positive NUMBER!\n");
        printer->massage("Enter Row: ");
        cin.clear(); // clears error flags
        cin.ignore(9999, '\n');
        cin >> row;
    }
    printer->massage("Enter Col: ");
    cin >> col;
    while ((!cin) || (col < 1)) {
        printer->massage("Input MUST be a positive NUMBER!\n");
        printer->massage("Enter Col: ");
        cin.clear(); // clears error flags
        cin.ignore(9999, '\n');
        cin >> col;
    }
    printer->massage("\n");
    return Coordinate(row - 1, col - 1); //the -- because the input is higher
}
void HumanPlayer::startTurn(Printer* printer, const Value &val, Coordinate c) const {
    printer->playingMove(val, c);
    printer->yourTurn(sign);
}
void HumanPlayer::cantMove(Printer* printer, Logic* l) const {
    l->couldntMove();
    printer->cantMove(); //print that the player cant move
    char pressAnyKey;
    cin >> pressAnyKey; //wait for user to press any key
}
