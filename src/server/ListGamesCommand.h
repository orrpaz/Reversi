//
// Created by or on 27/12/17.
//

#ifndef REVERSI_LISTGAMESCOMMAND_H
#define REVERSI_LISTGAMESCOMMAND_H


#include "Command.h"

class ListGamesCommand : public Command {
public:
    /**
     * constructor.
     * @param gamesList - vector of the game.
     */
    ListGamesCommand(vector<GameInfo> *gamesList);
    /**
     *
     * @param args
     */
    virtual void execute(vector<string> args);
    /**
     * destrucror
     */
        ~ListGamesCommand() {};
private:
    vector<GameInfo> *gamesList;


};


#endif //REVERSI_LISTGAMESCOMMAND_H
