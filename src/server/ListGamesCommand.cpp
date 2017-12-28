//
// Created by or on 27/12/17.
//

#include <list>
#include <cstdlib>
#include <unistd.h>
#include "ListGamesCommand.h"
ListGamesCommand ::ListGamesCommand(vector<GameInfo> *gamesList) {
    this->gamesList = gamesList;
}
void ListGamesCommand :: execute(vector<string> args) {
    string str = args[0];
    int client = atoi(str.c_str());

    list<string> gamesNames;
    vector<GameInfo>::iterator it;

    pthread_mutex_lock(&mutex);
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        gamesNames.push_back((*it).getName());
    }
    pthread_mutex_unlock(&mutex);
    int n = write(client,&gamesNames, sizeof(gamesNames));
    if (n==-1) {
        throw "Error while writing to socket"
    }

}