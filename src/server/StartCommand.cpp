//
// Created by or on 22/12/17.
//

#include <unistd.h>
#include "StartCommand.h"

StartCommand ::StartCommand(vector<Game> *gamesList) : Command() {
    this->gamesList = gamesList;
}

void StartCommand::execute(vector<string> args, int client) {
        int msg;
        pthread_mutex_t startMutex;
        if(!(*gamesList).empty()){
            vector<Game>::iterator it;
            for (it = (*gamesList).begin();it!=(*gamesList).end(); it++) {
                if ((*it).getName().compare(args[0]) == 0) {
                    msg = -1;
                    write(client, &msg, sizeof(msg));

                }
            }
            msg = 1;
            pthread_mutex_lock(&startMutex);
            (*gamesList).push_back(Game(args[0], client));
            pthread_mutex_unlock(&startMutex);
            write(client,&msg, sizeof(msg));
        }
    }