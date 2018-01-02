//
// Created by or on 27/12/17.
//

#include <list>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "GamesListCommand.h"
GamesListCommand ::GamesListCommand(vector<GameInfo> *games) {
    gamesList = games;
}
void GamesListCommand :: execute(vector<string> args) {
    //args contains: args[0]-client, args[1]- nothing
    string str = args[0];
    int client = atoi(str.c_str());
    cout << "try to Mutex locked:\n";
    cout << "Mutex locked:\n";

    list<string> gamesNames;
    vector<GameInfo>::iterator it;

    cout << "Here 3 before:\n";
    // pthread_mutex_lock(&mutex);
    cout << "Here2:\n";
    pthread_mutex_lock(&mutex);
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        if (it->getSecondClient() == -1) { //means that no one already connected to game
            gamesNames.push_back((*it).getName());
//        cout << "List: \n";
//        cout  << (*it).getName() << endl;
//        cout  << (*it).getFirstClient() << endl;
//        cout  << (*it).getSecondClient() << endl;
        }
    }
    pthread_mutex_unlock(&mutex);
    cout << "Mutex unlocked:\n";
    // pthread_mutex_unlock(&mutex);

    //Make it as one long string, to send it as string
    string namesInString = "-1"; //-1 to info the client it should send another command
    list<string>::iterator listIT;
    for (listIT = gamesNames.begin(); listIT  != gamesNames.end();) {
        namesInString.append(*(listIT));
        //join "\n" except from the last time
        if (++listIT != gamesNames.end()) {
            namesInString.append(", ");
        } else {
            namesInString.append("\0");
        }
    }
    cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAA: \n";
    cout << namesInString << endl;
    cout << "BBBBBBBBBBBBBBBBBBBBBBBBBBBBB: \n";
    const char* toSend = namesInString.c_str();
    cout << toSend << endl;
    char msg[this->msgLength];
    strcpy(msg, toSend);
    cout << "CCCCCCCCCCCCCCCCCCCCCCCCCCCC: \n";
    cout << msg;

    //char *msg= &namesInString[0];
    //   strcpy(&msg, namesInString.c_str());
//    memcpy(msg, )
    int n = write(client,msg, sizeof(msg));
    if (n==-1) {
        throw "Error while writing to socket";
    }

    //At the end, the player get the list, and we close the socket
    close(client);

}