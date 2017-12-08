//
// Created by or on 05/12/17.
//

#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;
int main() {
    int port;
    ifstream inFile;
    inFile.open("../exe/setting_server.txt");
    if(!inFile.is_open()) {
        throw "Can't open file";
    }
    inFile >> port;
    Server server(port);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        server.stop();
        exit(-1);
    }
}
