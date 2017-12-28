//
// Created by or on 22/12/17.
//

#include <unistd.h>
#include <cstdlib>
#include "StartCommand.h"

StartCommand ::StartCommand(vector<GameInfo> *gamesList) : Command() {
    this->gamesList = gamesList;
}

void StartCommand::execute(vector<string> args) {
        string str = args[0];
        int client = atoi(str.c_str());
        int msg;
        if(!(*gamesList).empty()){
            vector<GameInfo>::iterator it;
            for (it = (*gamesList).begin();it!=(*gamesList).end(); it++) {
                //Compare the input name to the names in the game list
                //Return -1 if already in the list
                if ((*it).getName().compare(args[1]) == 0) {
                    msg = -1;
                    write(client, &msg, sizeof(msg));
                }
            }
            msg = 1;
            pthread_mutex_lock(&mutex);
            (*gamesList).push_back(GameInfo(args[1], client));
            pthread_mutex_unlock(&mutex);
            write(client,&msg, sizeof(msg));
        }
    }