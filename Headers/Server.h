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
    int obsadenePolicka;
    int mapa;
    bool jePrazdny;
    char** pole;
    User* hrac1;
    User* hrac2;
    pthread_t* vlakno;
    static bool vyhral(int x, int y, Server* server, char znak);
    static bool tah(User* hrac, User* hrac2, Server* server, char znak);
public:
    Server(string pNazovServeru, int pMapa, User* pHrac1, pthread_t* pVlakno);
    ~Server();
    void zacniPracovat();
    static void *pracuj(void *data);
    string getNazovServeru();
    bool getJePrazdny();
    void pridajHraca(User* phrac2);
};


#endif //SEMESTRALKASERVER_SERVER_H
