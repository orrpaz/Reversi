#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;
int main() {
    int port;
    ifstream inFile;
    inFile.open("../exe/setting_server.txt");
    if(!inFile.is_open()) {
        throw "Can't open file";
    }
    string line;
    while (getline(inFile,line)) {
        if(line[0] == '#') continue;

        stringstream(line) >> port;
    }
    Server server(port);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        server.stop();
        exit(-1);
    }
}