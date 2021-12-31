//
// Created by helom on 31. 12. 2021.
//

#ifndef SEMESTRALKASERVER_SERVER_H
#define SEMESTRALKASERVER_SERVER_H

#include "string"
#include "User.h"

using namespace std;

class Server {
private:
    string nazovServeru;
    int mapa;
    char** pole;
    User* hrac1;
    User* hrac2;
    pthread_t* vlakno;
public:
    Server(string pNazovServeru, int pMapa, User* pHrac1, pthread_t* pVlakno);
    ~Server();
    void zacniPracovat();
    static void *pracuj(void *data);
    string getNazovServeru();
    void pridajHraca(User* phrac2);
};


#endif //SEMESTRALKASERVER_SERVER_H
