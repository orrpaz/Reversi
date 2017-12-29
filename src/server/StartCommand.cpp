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
    //args[0] - client socket, args[1] - room name
    string str = args[0];
    int client = atoi(str.c_str());
    // '-1' for siging that the name is already taken
    char msg[this->msgLength] = "-1There is already a game with this name!";
    if(!(*gamesList).empty()) {
        vector<GameInfo>::iterator it;

        pthread_mutex_lock(&mutex);

        for (it = (*gamesList).begin(); it != (*gamesList).end(); it++) {
            //Compare the input name to the names in the game list
            //Return -1 if already in the list
            if ((*it).getName().compare(args[1]) == 0) {
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

    //Push the game to
    pthread_mutex_lock(&mutex);
    (*gamesList).push_back(GameInfo(args[1], client));
    pthread_mutex_unlock(&mutex);

    // '1' for siging thats ok
    msg = "1Waiting for the other player...\n";

    //Write result to client
    int n = write(client,&msg, sizeof(msg));
    if (n == -1) {
        throw "Error on writing to socket";
    }
}