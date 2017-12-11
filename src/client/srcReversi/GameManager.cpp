
#include <iostream>
#include <cstdlib>
#include <zconf.h>
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
        client->closeClient();
        delete(client);
    }

}
void GameManager::initialize(const int &size) {

    const Value p1Token = Black;
    const Value p2Token = White;
    isClientPlay = false;
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
                    players[1] = new RemotePlayer(p2Token, client, priority);
                } else {
                    players[1] = new HumanPlayer(p2Token);
                    players[0] = new RemotePlayer(p1Token, client, priority);
                }
                flag = 0;
                break;
            }
            default:
                printer->massage("Please press legal number\n");
                break;
        }
    }
}

void GameManager::run() {
    tie = 0; //updates when player cant move
    int turn = 0;
    while(!board->isFull()) {
        playTurn(players[turn]); // play current turn

        turn = 1 - turn; // switch the turn to other player

        if (tie == 2) { // if both players cant move
           printer->noMoreMoves();
            break;
        }
        logic->endTurn();
    }
    if (isClientPlay) { //play another turn in order to send the last move to other player
      //  cout << "Here\n";
       // printer->printBoard(board);

       //3 cout << "Turn: " <<turn +1 << endl;
        const Value token = players[turn]->getToken();
        set<Coordinate> finalMove = logic->availableMoves(token); //its empty
        putNext(players[turn], finalMove);
    }
    endGame();
}
void GameManager::playTurn(Player *&player) {
    printer->printBoard(board);
    const Value token = player->getToken();
    set<Coordinate> availableMoves = logic->availableMoves(token); // Get available moves
    player->startTurn(printer, board->getOpponent(player->getToken()), logic->getLastMove());


    if (!availableMoves.empty()) { //Check if there are avaliable moves for the player
        putNext(player, availableMoves); //Player puts his token
        tie = 0;
    } else {
        tie++; //if it equals to 2 - theres a tie
      //  if(!board->isFull()){ //If the board is full the game should be end without this print
            player->cantMove(printer, logic);
        //}
    }
}

void GameManager::putNext(Player *&p, set<Coordinate> &availableMoves) const{
    bool flag = true;

    while (flag) {
        Coordinate position(p->makeTurn(logic, board, printer, availableMoves)); //Get coordinate by player's choose
        if (position.getRow() < 0 || (board->isFull()) || (tie ==2)) { //means that the player couldn't move
            break;
        }

        if (logic->isLegal(position)) { //Check if the move is legal
            flag = false;
            logic->makeMove(position, p->getToken(),board); // flip other tokens
        } else {
            printer->massage("Illegal move\n");
            cout  << position.getRow() << "," << position.getCol() <<"\n";
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
    if (isClientPlay) {
        int move[2];
        move[0] = -1;
        move[1] = -1;
        ssize_t n = write(client->getClientSocket(),&move ,sizeof (move));
        if (n == -1) {
            throw "Error writing x to socket";
        }
    }

    printer->printBoard(board);
    winner();
}

int GameManager::clientCase() {
    client = new Client("../exe/setting_client.txt");
    try {
        client->connectToServer();

    } catch (const char *msg) {
        cout << "Failed to connect to server. Reason:   " << msg << endl;
        delete this; // call the destructor
        exit(-1);
    }
    int priority = client->getPriorityValue();
    cout << "You are player number: " << priority << endl;
    return priority;
}
