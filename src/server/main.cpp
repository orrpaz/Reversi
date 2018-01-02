#include "Server.h"
#include "ClientHandler.h"
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
        cout <<"Here";
        throw "Can't open file";
    }
    string line;
    while (getline(inFile,line)) {
        if(line[0] == '#') continue;

        stringstream(line) >> port;
    }
    inFile.close();
    cout << "main\n";
    Server server(port);
    try {
        server.start();
        cout << "JJJJJJJJJJJJJJJJJJJ\n";
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        server.stop();
        exit(-1);
    }
}
