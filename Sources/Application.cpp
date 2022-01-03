//
// Created by helom on 26. 12. 2021.
//


#include <iostream>
#include "../Headers/Application.h"
#include "../Headers/User.h"
#include "../Headers/Server.h"

Application::Application(int argc, char *argv[]) {
    if (argc < 2)
    {
        fprintf(stderr,"usage %s port\n", argv[0]);
        exit(1);
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket address");
        exit(2);
    }
    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);
    int i = 0;

    pthread_t* vlaknaUsers = new pthread_t[pocetUzivatelov];
    int newsockfd[pocetUzivatelov];

    while (i != 10) {
        newsockfd[i] = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
        if (newsockfd[i] < 0)
        {
            perror("ERROR on accept");
            exit(3);
        }
        cout << "Pripaja sa uživateľ s ID: " << i << "\n";
        users[i] = new User(newsockfd[i], this, &vlaknaUsers[i]);
        users[i]->zacniPracovat();
        i++;
    };


    for (int j = 0; j < pocetUzivatelov; ++j) {
        pthread_join(vlaknaUsers[j], NULL);
        close(newsockfd[j]);
    }
    for (int j = 0; j < 6; ++j) {
        pthread_join(vlaknaServer[j], NULL);
    }
    close(sockfd);
    delete[] vlaknaUsers;
}

bool Application::vytvorServer(string nazovServeru, int mapa, User* user) {
    int i = 0;

    while (servery[i] != nullptr)
    {
        i++;
    }
    if (i <= 4) {
        servery[i] = new Server(nazovServeru, mapa, user, &vlaknaServer[i]);
        servery[i]->zacniPracovat();
        return true;
    } else {
        return false;
    }

}

Server *Application::getServer(int id) {
    if (servery[id] == nullptr) {
        return nullptr;
    } else {
        return servery[id];
    }

}

Application::~Application() {
    for (int i = 0; i < pocetUzivatelov; ++i) {
        delete users[i];
    }
    for (int i = 0; i < 6; ++i) {
        delete servery[i];
    }
    delete[] vlaknaServer;
}

int Application::getPocetServerov() const {
    return pocetServerov;
}




