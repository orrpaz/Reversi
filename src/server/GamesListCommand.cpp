//
// Created by or on 27/12/17.
//

#include <list>
#include <cstdlib>
#include <unistd.h>
#include "GamesListCommand.h"
GamesListCommand ::GamesListCommand(vector<GameInfo> *gamesList) {
    this->gamesList = gamesList;
}
void GamesListCommand :: execute(vector<string> args) {
    //args contains: args[0]-client, args[1]- nothing
    string str = args[0];
    int client = atoi(str.c_str());

    list<string> gamesNames;
    vector<GameInfo>::iterator it;

    pthread_mutex_lock(&mutex);
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        gamesNames.push_back((*it).getName());
    }
    pthread_mutex_unlock(&mutex);

    //Make it as one long string, to send it as string
    string namesInString = "-1"; //-1 to info the client it should send another command
    list<string>::iterator listIT;
    for (listIT = gamesNames.begin(); listIT  != gamesNames.end();) {
        namesInString.append(*(listIT));
        //join "\n" except from the last time
        if (++listIT != gamesNames.end()) {
            namesInString.append("\n");
        }
    }
    const char* toSend = namesInString.c_str();

    int n = write(client,&toSend, sizeof(toSend));
    if (n==-1) {
        throw "Error while writing to socket";
    }

}