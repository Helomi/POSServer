//
// Created by helom on 31. 12. 2021.
//


#include "../Headers/Server.h"
#include "../Headers/User.h"


Server::Server(string pNazovServeru, int pMapa, User* pHrac1, pthread_t* pVlakno) {
    nazovServeru = pNazovServeru;
    mapa = pMapa;
    hrac1 = pHrac1;
    vlakno = pVlakno;
    pole = new char* [pMapa];
    for (int i = 0; i < pMapa; ++i) {
        pole[i] = new char[pMapa];
    }
}

Server::~Server(){
    for (int i = 0; i < mapa; ++i) {
        delete[] pole[i];
    }
    delete[] pole;
}

void Server::zacniPracovat() {
    pthread_create(vlakno, NULL, &Server::pracuj, this);
}

void *Server::pracuj(void *data) {
    Server* server = (Server*) data;
    while (server->hrac2 == nullptr) {
        cout << "Čakám než sa pripojí ďalší hráč\n";
        sleep(5);
    }
    cout << "Hráč sa pripojil zapíname hru!\n";
}

string Server::getNazovServeru() {
    return nazovServeru;
}

void Server::pridajHraca(User* phrac2) {
    hrac2 = phrac2;
}
