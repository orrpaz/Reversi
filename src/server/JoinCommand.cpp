//
// Created by amir on 28/12/17.
//

#include <cstdlib>
#include <zconf.h>
#include "JoinCommand.h"
JoinCommand ::JoinCommand(vector<GameInfo>* games) : Command() {
    gamesList = games;
}

void JoinCommand::execute(vector<string> args) {
    //args[0] - client socket, args[1] - room name

    //Get client info into 'int client'
    string str = args[0];
    int client = atoi(str.c_str());
    string nameOfGame = args[1];
    int msg;

    //If the games's list is empty
    pthread_mutex_lock(&mutex);
    if (gamesList->empty()) {
        msg = -1;
        int n = write(client, &msg, sizeof(msg));
        if (n == -1) {
            throw "Error on writing to socket";
        }
        //We don't want to continue
        return;
    }
    pthread_mutex_unlock(&mutex);

    //Search for the game
    vector<GameInfo>::iterator it;
    pthread_mutex_lock(&mutex);

        for (it = (*gamesList).begin(); it != (*gamesList).end(); it++) {
            //Compare the input name to the names in the game list
            if ((*it).getName().compare(nameOfGame) == 0) {



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