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

class Application {
private:
    pthread_mutex_t serverPole;
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
public:
    Application(int argc, char *argv[]);
};


#endif //SEMESTRALKASERVER_APPLICATION_H
cmake_minimum_required(VERSION 3.7.2)
project(SemestralkaServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(SemestralkaServer main.cpp Sources/Application.cpp Headers/Application.h Sources/User.cpp Headers/User.h)

target_link_libraries(SemestralkaServer pthread)