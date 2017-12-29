//
// Created by amir on 28/12/17.
//

#include <cstdlib>
#include <unistd.h>
#include "JoinCommand.h"
JoinCommand ::JoinCommand(vector<GameInfo>* games) : Command() {
    gamesList = games;
}

void JoinCommand::execute(vector<string> args) {
    //args[0] - the later (second) client socket, args[1] - room name

    //Get client info into 'int client'
    string str = args[0];
    int secondClient = atoi(str.c_str());
    string nameOfGame = args[1];


//    //If the games's list is empty
//    pthread_mutex_lock(&mutex);
//    if (gamesList->empty()) {
//        int n = write(client, &msg, sizeof(msg));
//        if (n == -1) {
//            throw "Error on writing to socket";
//        }
//        //We don't want to continue
//        return;
//    }
//    pthread_mutex_unlock(&mutex);

    //Search for the game
    vector<GameInfo>::iterator it;
    bool found = false;
    pthread_mutex_lock(&mutex);
    for (it = (*gamesList).begin(); it != (*gamesList).end(); it++) {
        //Compare the input name to the names in the game list
        if ((*it).getName().compare(nameOfGame) == 0) {

            found = true;
            //1 for signing that it's OK
            char msg[this->msgLength] = "1Connecting to game...\n";
            int n = write(secondClient , &msg, sizeof(msg));
            if (n == -1) {
                throw "Error on writing to socket";
            }
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    //if not found
    if (!found) {
        char msg[this->msgLength] = "-1There is no game with this name!\n";
        int n = write(secondClient , &msg, sizeof(msg));
        if (n == -1) {
            throw "Error on writing to socket";
        }
        //We don't want to continue
        return;
    }

    int firstClient = it->getClientSocket();

    //Gives the priorities

    int turn =1;
    // give 1 to the first client
    int n = write(firstClient, &turn, sizeof(turn));
    if(n == -1) {
        cout << "Error writing to socket who's turn it is." << endl;
    }
    turn ++;
    n = write(secondClient, &turn, sizeof(turn));
    if(n == -1) {
        cout << "Error writing to socket who's turn it is." << endl;
    }

    //Handeling the game
    int i = 0;
    bool flag = true;
    while(flag){
        if (i % 2 == 0) {
            flag = doMove(firstClient, secondClient);

        } else {
            flag = doMove(secondClient, firstClient);

        }
        i++;
    }
    // Close communication with the client
    close(firstClient);
    close(secondClient);
}

bool JoinCommand::doMove(int fromSocket, int toSocket) {
    int move[2];
    ssize_t n = read(fromSocket, &move, sizeof(move));
    if (n == -1) {
        cout << "Error reading " << endl;
        return false;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return false;
    }
    cout << "Got move: " << move[0] + 1 << "," << move[1] + 1 << endl;
    if ((move[0] == -1) && (move[1] == -1)) {
        return false;
    }


    n = write(toSocket, &move, sizeof(move));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    cout << "Sent move: " << move[0] + 1 << "," << move[1] + 1 << endl;
}