//
// Created by helom on 31. 12. 2021.
//


#include "../Headers/Server.h"
#include "../Headers/User.h"


Server::Server(string pNazovServeru, int pMapa, User* pHrac1, pthread_t* pVlakno) {
    nazovServeru = pNazovServeru;
    mapa = pMapa;
    jePrazdny = true;
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
    int i = 0;
    while (server->hrac2 == nullptr && i <= 10) {
        cout << server->nazovServeru << ": Čakám než sa pripojí ďalší hráč\n";
        sleep(5);
        i++;
    }
    if (i >= 10 && server->hrac2 == nullptr) {
        server->hrac1->odosliSpravu("OOT");
        cout << server->nazovServeru << ": Server uzavretý, vypršal čas na pripojenie 2. hráča\n";
        server->hrac1->setKoniec(true);
        server->jePrazdny = false;
    } else {
        cout << server->nazovServeru << ": Hráč sa pripojil zapíname hru!\n";
        server->hrac1->odosliSpravu("STR|" + to_string(server->mapa));
        server->hrac2->odosliSpravu("STR|" + to_string(server->mapa));
        sleep(2);
        server->hrac1->odosliSpravu("DTN|");
        bool koniecZapasu = false;
        while(!koniecZapasu) {
            koniecZapasu = tah(server->hrac1, server->hrac2, server, 'O');
            if (!koniecZapasu) {
                koniecZapasu = tah(server->hrac2, server->hrac1, server, 'X');
            }
        }

    }
}

bool Server::tah(User *hrac, User *hrac2, Server *server, char znak) {
    string pomocna;
    int x;
    int y;
    pomocna = hrac->primiSpravu();
    stringstream check1(pomocna);
    string pomocna2;
    getline(check1, pomocna2, '|');
    if (pomocna2.compare("UPD") == 0) {
        getline(check1, pomocna2, '|');
        x = stoi(pomocna2);
        getline(check1, pomocna2, '|');
        y = stoi(pomocna2);
        server->pole[y][x] = znak;
        if (vyhral(x, y, server, znak)) {
            hrac2->odosliSpravu("LOS|" + to_string(x) + "|" + to_string(y)); // LOS - Prehra + posledný ťah súpera
            hrac->odosliSpravu("WIN");// WIN - Výhra
            return true;
        } else {
            if (server->obsadenePolicka == (server->mapa * server->mapa)-1) {
                hrac2->odosliSpravu("DRW|" + to_string(x) + "|" + to_string(y)); // DRW - Draw (remíza)
                hrac->odosliSpravu("DRW"); // DRW - Draw (remíza)
                return true;
            } else {
                hrac2->odosliSpravu("DTU|" + to_string(x) + "|" + to_string(y)); // DTU - Daj ťah update
            }
        }
    } else {
        hrac2->odosliSpravu("QUT");
        hrac->odosliSpravu("QUT");
        return true;
    }
    server->obsadenePolicka++;
    return false;
}


string Server::getNazovServeru() {
    return nazovServeru;
}

bool Server::getJePrazdny() {
    return jePrazdny;
}

void Server::pridajHraca(User* phrac2) {
    hrac2 = phrac2;
    jePrazdny = false;
}



bool Server::vyhral(int x, int y, Server* server, char znak) {
    // Kontola \ smeru
    int x_ = x;
    int y_ = y;
    int rovnake = 1;
    x_++;
    y_++;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        x_++;
        y_++;
    }
    x_ = x;
    y_ = y;
    x_--;
    y_--;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        x_--;
        y_--;
    }
    // Kontrola / smeru
    x_ = x;
    y_ = y;
    rovnake = 1;
    x_++;
    y_--;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        x_++;
        y_--;
    }
    x_ = x;
    y_ = y;
    x_--;
    y_++;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        x_--;
        y_++;
    }

    // Kontrola | smeru
    x_ = x;
    y_ = y;
    rovnake = 1;
    y_++;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        y_++;
    }
    x_ = x;
    y_ = y;
    y_--;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        y_--;
    }
    // Kontrola - smeru
    x_ = x;
    y_ = y;
    rovnake = 1;
    x_++;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        x_++;
    }
    x_ = x;
    y_ = y;
    x_--;
    while(x_ < server->mapa && y_ < server->mapa && x_ >= 0 && y_ >= 0) {
        if (server->pole[y_][x_] == znak) {
            rovnake++;
        } else {
            break;
        }
        if (rovnake == 3) {
            return true;
        }
        x_--;
    }
    return false;
}




