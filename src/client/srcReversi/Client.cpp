//
// Created by or on 06/12/17.
//

#include "../include/Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;
Client::Client(const char *serverIP, int serverPort):
        serverIP(serverIP), serverPort(serverPort),
        clientSocket(0) {
    cout << "Client" << endl;
}

Client::Client(char* fileName) {
    ifstream file;
    file.open(fileName, ios::in);
    if (!file.is_open())
        throw "Error opening the settings file!";
    else {

        string buffer, ip;
        getline(file, buffer);
        serverIP = buffer.c_str();
        getline(file, buffer);
        serverPort = atoi(buffer.c_str());
    }
}
void Client::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct hostent *server;
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }

    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr,(char *)server->h_addr, server->h_length);
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl << "Waiting for the other players..." << endl;
}

int Client::getPriorityValue() {
    int priority;
    ssize_t n = read(clientSocket, &priority, sizeof(priority));
    return priority;
}
