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
    bool koniec = false;

public:
    User(int pnewsockfd, Application *pApplication, pthread_t *pVlakno);
    ~User();
    void zacniPracovat();
    static void *pracuj(void *data);
    void setKoniec(bool koniec);
    char *primiSpravu();
    void odosliSpravu(string sprava);
    string getMeno();
};


#endif //SEMESTRALKASERVER_USER_H