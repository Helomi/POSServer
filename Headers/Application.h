//
// Created by helom on 26. 12. 2021.
//

#ifndef SEMESTRALKASERVER_APPLICATION_H
#define SEMESTRALKASERVER_APPLICATION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

class Application {
private:
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
public:
    Application(int argc, char *argv[]);
};


#endif //SEMESTRALKASERVER_APPLICATION_H
