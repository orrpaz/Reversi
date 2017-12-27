//
// Created by or on 22/12/17.
//

#include <unistd.h>
#include "StartCommand.h"


void StartCommand::execute(vector<string> args, vector<Game> *games, int client) {
        int msg;
        pthread_mutex_t startMutex;
        if(!(*games).empty()){
            vector<Game>::iterator it;
            for (it = (*games).begin();it!=(*games).end(); it++) {
     צריך להבין איך לפענח את הסטרינג
                if ((*it).getName().compare(args[0]) == 0) {
                    msg = -1;
                    write(client, &msg, sizeof(msg));

                }
            }
            msg = 1;
            pthread_mutex_lock(&startMutex);
            (*games).push_back(Game(args[0], client));
            pthread_mutex_unlock(&startMutex);
            write(client,&msg, sizeof(msg));
//        }
    }