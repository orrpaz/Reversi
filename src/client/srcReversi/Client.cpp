//
// Created by or on 06/12/17.
//

#include "../include/Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sstream>

using namespace std;


Client::Client(const char* fileName) {
    ifstream file;
    file.open(fileName, ios::in);
    if (!file.is_open())
        throw "Error opening the settings file!";
    else {
        string ip,buffer;
        file >> ip;
        strcpy(this->serverIP , ip.c_str());
        file >> this->serverPort;
        this->clientSocket = 0;

    }
    file.close();
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
//    cout << "Connected to server" << endl << "Waiting for the other players..." << endl;
}

int Client::getCommand(Printer* printer) {
    bool flag;
    string toSend, serverAnswer;
    do {
        flag = false;
        printer->massage("Please enter one of the following commands: start <name>, "
                                 "close <name>, join <name>, list_games\n");
        printer->getInput(toSend);

        //Send Command to server
        ssize_t n = write(clientSocket,&toSend ,sizeof (toSend));
        if (n == -1) {
            throw "Error writing move to socket";
        }

        //Get Server response
        n = read(clientSocket,&serverAnswer ,sizeof (serverAnswer));
        if (n == -1) {
            throw "Error reading move from socket";
        }

        //get the
        string msg;
        stringstream stream(serverAnswer);
        int num;
        //Split the info-num from server and the message
        while(stream >> num) {
            getline(stream, msg);
        }

        if(strcmp(toSend, "list_games") == 0) {
            flag = true;
            //Prints the list of the games
            printer->massage(serverAnswer);
        }
    } while (flag); //Repeat if it was a "list_games" request

    //For 'join' command, need to get the priority
    if(strcmp(toSend, "join") == 0) {
        flag = true;
        //Prints the list of the games
        printer->massage(serverAnswer);
        int priority = getPriorityValue();
        return priority;
    }
    return 0;
}

int Client::getClientSocket() const{
    return clientSocket;
}

int Client::getPriorityValue() {
    int priority;
    ssize_t n = read(clientSocket, &priority, sizeof(priority));
    return priority;
}
void Client::closeClient(){
    close(clientSocket);
}

