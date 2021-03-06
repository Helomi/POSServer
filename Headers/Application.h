//
// Created by helom on 26. 12. 2021.
//

#ifndef SEMESTRALKASERVER_APPLICATION_H
#define SEMESTRALKASERVER_APPLICATION_H

#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <string>

using namespace std;

class User;
class Server;

class Application {
private:
    pthread_mutex_t mutexServerPole;
    int sockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    Server* servery[5];
    pthread_t* vlaknaServer = new pthread_t[10];
    User* users[2];

public:
    Application(int argc, char *argv[]);
    ~Application();
    bool vytvorServer(string nazovServeru, int mapa, User* user);
    Server* getServer(int id);
    int getPocetServerov() const;


};


#endif //SEMESTRALKASERVER_APPLICATION_H