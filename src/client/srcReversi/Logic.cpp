//
// Created by amir on 02/11/17.
//

#include "../include/Board.h"
#include "../include/Logic.h"

using namespace std;
Logic::Logic(Board*& b) {
    board = b;
    size = b->getSize();
}

Logic::~Logic() {}

void Logic::calculateAll(const Value &player) {
    for (int row = 0; row < board->getSize(); row++) {
        for (int col = 0; col < board->getSize(); col++) {
            if (board->getValue(row, col) == player) {
                Coordinate coordinate(row,col);
                calculate(coordinate, player);
            }
        }
    }
}

void Logic::endTurn() {
  //  temp_board->clear();
    canMove.clear();
}
