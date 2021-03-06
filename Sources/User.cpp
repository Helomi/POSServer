//
// Created by helom on 29. 12. 2021.
//



#include "../Headers/User.h"
#include "../Headers/Application.h"
#include "../Headers/Server.h"

User::User(int pnewsockfd, Application *pApplication, pthread_t *pVlakno) {
    newsockfd = pnewsockfd;
    application = pApplication;
    vlakno = pVlakno;
}

void *User::pracuj(void *data) {
    User* user = (User*) data;
    user->meno = user->primiSpravu();
    bool pripojeny = false;
    while (!pripojeny) {
        string pomocna;
        pomocna = user->primiSpravu();
        stringstream check1(pomocna);
        string pomocna2;
        getline(check1, pomocna2, '|');
        if (pomocna2.compare("CRT") == 0) {
            string nazovServeru;
            int mapa;
            getline(check1, nazovServeru, '|');
            check1 >> mapa;
            cout << user->meno << ": Pokúšam sa vytvoriť server\n";
            if (user->application->vytvorServer(nazovServeru, mapa, user)) {
                user->odosliSpravu("OK");
                cout << user->meno << ": Server vytvorený úspešne\n";
                pripojeny = true;
            } else {
                user->odosliSpravu("NO");
                cout << user->meno << ": Server sa nepodarilo vytvoriť, kapacita zaplnená\n";
            }
        } else if (pomocna2.compare("DZL") == 0) {
            int i = 0;
            string zoznamServerov;
            for (int j = 0; j < user->application->getPocetServerov(); ++j) {
                if (user->application->getServer(j) != nullptr)
                {
                    if (user->application->getServer(j)->getJePrazdny()) {
                        zoznamServerov += user->application->getServer(j)->getNazovServeru() + "|";
                    } else {
                        zoznamServerov += user->application->getServer(j)->getNazovServeru() + "#|";
                    }
                    i++;
                }
                if (i % 4 == 0 && i != 0) {
                    user->odosliSpravu(zoznamServerov);
                    zoznamServerov = "";
                }
            }
            zoznamServerov += "END|";
            user->odosliSpravu(zoznamServerov);
            if (i != 0) {
                pomocna = user->primiSpravu();
                stringstream check1(pomocna);
                getline(check1, pomocna2, '|');
                if (pomocna2.compare("JOI") == 0) {
                    int idServeru;
                    check1 >> idServeru;
                    if (user->application->getServer(idServeru - 1)->getJePrazdny()) {
                        user->application->getServer(idServeru - 1)->pridajHraca(user);
                        pripojeny = true;
                    } else {
                        user->odosliSpravu("NO");
                    }
                } else {

                }
            } else {

            }
        } else {
            return 0;
        }
    }
//
}








void User::zacniPracovat() {
    pthread_create(vlakno, NULL, &User::pracuj, this);
}

void User::odosliSpravu(string sprava) {
    cout << meno << ": << " << sprava << "\n";
    bzero(buffer,256);
    strcpy(buffer, sprava.c_str());
    n = write(newsockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
        exit(0);
    }
}

char* User::primiSpravu() {
    bzero(buffer,256);
    n = read(newsockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        exit(0);
    }
    cout << meno << ": >> " << buffer << "\n";
    return buffer;
}

void User::setKoniec(bool koniec) {
    User::koniec = koniec;
}

User::~User() {}

string User::getMeno() {
    return meno;
}
