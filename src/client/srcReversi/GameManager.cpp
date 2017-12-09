
#include <iostream>
#include <cstdlib>
#include "../include/GameManager.h"
#include "../include/ConsolePrinter.h"
#include "../include/HumanPlayer.h"
#include "../include/ComputerPlayer.h"
#include "../include/Client.h"
#include "../include/RemotePlayer.h"

using namespace std;

GameManager::GameManager() : board(), logic(), players(), printer(), tie() {
    initialize(8);
}
GameManager::GameManager(const int &size) : board(), logic(), players(), printer(), tie() {
    initialize(size);
}
GameManager::~GameManager() {
    delete(players[0]);
    delete(players[1]);
    delete[] players;
    delete(logic);
    delete(board);
    delete(printer);
    if (isClientPlay) {
        delete(client);
    }

}
void GameManager::initialize(const int &size) {

    const Value p1Token = Black;
    const Value p2Token = White;
    printer = new ConsolePrinter();
    board = new Board(size, p1Token, p2Token);
    logic = new NormalLogic(board);
    players = new Player*[2];
    char gameMode ,flag = 1;
    printer->massage("Choose a game mode:\n\n1) Player vs Player\n\n2)"
                             " Player vs Computer\n\n3) Player vs Remote Player\n\n");

    while(flag) {
        cin >> gameMode;
        switch (gameMode) {
            case '1':
                players[0] = new HumanPlayer(p1Token);
                players[1] = new HumanPlayer(p2Token);
                flag = 0;
                break;
            case '2':
                players[0] = new HumanPlayer(p1Token);
                players[1] = new ComputerPlayer(p2Token);
                flag = 0;
                break;
            case '3': {
                isClientPlay = true;
                int priority = clientCase();
                if (priority == 1) {
                    players[0] = new HumanPlayer(p1Token);
                  //  players[1] = new ComputerPlayer(p2Token);
                    // players[1] = new RemotePlayer(p2Token);
                } else {
                    players[1] = new HumanPlayer(p2Token);
                //    players[0] = new ComputerPlayer(p1Token);
                    //   players[0] = new RemotePlayer(p1Token);
                }

                break;
            }
            default:
                printer->massage("Please press legal number\n");
                break;
        }
    }
}
int GameManager::clientCase() {
   // client = new Client("127.0.0.1", 8001);
    client = new Client("../exe/setting_client.txt");
    try {
        client->connectToServer();

    } catch (const char *msg) {
        cout << "Failed to connect to server. Reason:   " << msg << endl;
        delete[] players;
        delete(printer);
        exit(-1);
    }
    int priority = client->getPriorityValue();
    cout << "priority: \n" << priority;
    return priority;
}

void GameManager::run() {
    tie = 0; //updates when player cant move
    int turn = 0;
    while(!board->isFull()) {
        playTurn(players[turn]); // play current turn

        if (tie == 2) { // if both players cant move
           printer->noMoreMoves();
            break;
        }
        turn = 1 - turn; // switch the turn to other player
        logic->endTurn();
    }
    endGame();
}
void GameManager::playTurn(Player *&player) {
    printer->printBoard(board);
    const Value token = player->getToken();
    printer->yourTurn(token);

    set<Coordinate> availableMoves = logic->availableMoves(token); // Get available moves

    if (!availableMoves.empty()) { //Check if there are avaliable moves for the player
        printer->availableMoves(availableMoves); // Print available moves
        putNext(player, availableMoves); //Player puts his token
        tie = 0;
    } else {
        tie++; //if it equals to 2 - theres a tie
        printer->cantMove(); //print that the player cant move
        char pressAnyKey;
        cin >> pressAnyKey; //wait for user to press any key
    }
}

void GameManager::putNext(Player *&p, set<Coordinate> &availableMoves) const{
    bool flag = true;

    while (flag) {
        Coordinate position(p->makeTurn(logic, board, printer, availableMoves)); //Get coordinate by player's choose
        if (logic->isLegal(position)) { //Check if the move is legal
            flag = false;
            printer->playingMove(position);
            board->update(position, p->getToken()); //update this one token
            logic->flip(position, p->getToken()); // flip other tokens
        } else {
            printer->massage("Illegal move\n");
        }
    }
}


void GameManager::winner() const{
    Value p1 = players[0]->getToken();
    Value p2 = players[1]->getToken();
    int score1 = 0;
    int score2 = 0;

    for (int x = 0;x < board->getSize();x++) {
        for(int y = 0;y < board->getSize();y++) {
            if (board->getValue(x, y) == p1) {
                score1++;
            } else if (board->getValue(x, y) == p2) {
                score2++;
            }
        }
    }
    printer->winner(p1, p2, score1, score2);
}

void GameManager::endGame() {
    printer->printBoard(board);
    winner();
}

