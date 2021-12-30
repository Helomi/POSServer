//
// Created by helom on 29. 12. 2021.
//

#ifndef SEMESTRALKASERVER_USER_H
#define SEMESTRALKASERVER_USER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include "Application.h"

using namespace std;



class User {
private:
    int newsockfd;
    char buffer[256];
    int n;
    Application *application;
    pthread_t* vlakno;

public:
    User(int pnewsockfd, Application *pApplication, pthread_t *pInt);
    void zacniPracovat();
    static void *pracuj(void *data);
};


#endif //SEMESTRALKASERVER_USER_H