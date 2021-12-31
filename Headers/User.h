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
#include <sstream>
#include <iostream>
#include "Application.h"

using namespace std;



class User {
private:
    int newsockfd;
    char buffer[256];
    string meno;
    int n;
    Application *application;
    pthread_t* vlakno;

public:
    User(int pnewsockfd, Application *pApplication, pthread_t *pVlakno);
    void zacniPracovat();
    static void *pracuj(void *data);

    char *primiSpravu();
    void odosliSpravu(string sprava);
};


#endif //SEMESTRALKASERVER_USER_H