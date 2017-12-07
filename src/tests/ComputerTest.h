//
// Created by amir on 27/11/17.
//

#ifndef REVERSI_COMPUTERTEST_H
#define REVERSI_COMPUTERTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/include/ComputerPlayer.h"
#include "../client/include/NormalLogic.h"

using namespace std;


class ComputerTest: public testing::Test {
public:

    ComputerTest(): player(ComputerPlayer(White)){
    }

    virtual void SetUp() {
        cout << "Setting up" << endl;
        board = new Board(8, Black, White);
        logic = new NormalLogic(board);
    }
    virtual void TearDown() {
        cout << "Tearing down" << endl;
        delete (board);
        delete(logic);
    }

protected:
    Logic* logic;
    Board* board;
    ComputerPlayer player;
};


#endif //REVERSI_COMPUTERTEST_H
