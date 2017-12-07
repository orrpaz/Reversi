//
// Created by or on 05/12/17.
//

#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    Server server(8001);
    try {
        server.start();
        server.stop();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
