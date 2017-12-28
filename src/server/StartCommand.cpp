//
// Created by or on 22/12/17.
//

#include <unistd.h>
#include <cstdlib>
#include "StartCommand.h"

StartCommand ::StartCommand(vector<GameInfo>* games) : Command() {
    gamesList = games;
}

void StartCommand::execute(vector<string> args) {
    string str = args[0];
    int client = atoi(str.c_str());
    int msg;

    if(!(*gamesList).empty()) {
        vector<GameInfo>::iterator it;

        pthread_mutex_lock(&mutex);

        for (it = (*gamesList).begin(); it != (*gamesList).end(); it++) {
            //Compare the input name to the names in the game list
            //Return -1 if already in the list
            if ((*it).getName().compare(args[1]) == 0) {
                msg = -1;
                int n = write(client, &msg, sizeof(msg));
                if (n == -1) {
                    throw "Error on writing to socket";
                }
                //We don't want to continue
                return;
            }
        }
        pthread_mutex_unlock(&mutex);
    }
    //The returned massage
    msg = 1;

    //Push the game to
    pthread_mutex_lock(&mutex);
    (*gamesList).push_back(GameInfo(args[1], client));
    pthread_mutex_unlock(&mutex);

    //Write result to client
    int n = write(client,&msg, sizeof(msg));
    if (n == -1) {
        throw "Error on writing to socket";
    }
}