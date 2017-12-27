//
// Created by or on 27/12/17.
//

#include "ListGamesCommand.h"
ListGamesCommand ::ListGamesCommand(vector<Game> *gamesList) {
    this->gamesList = gamesList;
}
void ListGamesCommand :: execute(vector<string> args) {
    vector<Game>::iterator it;
    pthread_mutex_t listMutex;
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        //
        //
        //
    }
}