//
// Created by amir on 26/12/17.
//

#include <zconf.h>
#include "ClientHandler.h"
void* ClientHandler::handleClient(void* socket) {

    char request[20];
    ssize_t n = read((int)socket, &request, sizeof(request));

    //פיענוח הודעה
    //שליחה לקומנד מנג'ר



}