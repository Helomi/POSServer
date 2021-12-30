//
// Created by helom on 26. 12. 2021.
//

#include "../Headers/Application.h"
#include "../Headers/User.h"

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


    int pocetUzivatelov = 5;
    int i = 0;
    User* users[pocetUzivatelov];
    pthread_t* vlaknaUsers = new pthread_t[pocetUzivatelov];

    while (true) {
        newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(3);
        }
        users[i] = new User(newsockfd, this, &vlaknaUsers[i]);
        users[i]->zacniPracovat();
        i++;
    }
    close(sockfd);
}