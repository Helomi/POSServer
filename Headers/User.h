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
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;



class User {
private:
    int newsockfd;
    char buffer[256];
    int n;
public:
    User(int pnewsockfd);
};


#endif //SEMESTRALKASERVER_USER_H
