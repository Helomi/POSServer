//
// Created by helom on 29. 12. 2021.
//

#include "../Headers/User.h"
#include "../Headers/Application.h"

User::User(int pnewsockfd, Application *pApplication, pthread_t *pVlakno) {
    newsockfd = pnewsockfd;
    application = pApplication;
    vlakno = pVlakno;
}

void *User::pracuj(void *data) {
    User* user = (User*) data;
    for (int i = 0; i < 5; ++i) {
        bzero(user->buffer,256);
        user->n = read(user->newsockfd, user->buffer, 255);
        if (user->n < 0)
        {
            perror("Error reading from socket");
            exit(4);
        }
        printf("Here is the message: %s\n", user->buffer);

        string msg = "asdfgjkl|šdfghjkln|sfgdnjkl|END|";
        user->n = write(user->newsockfd, msg.c_str(), strlen(msg.c_str())+1);
        if (user->n < 0)
        {
            perror("Error writing to socket");
            exit(5);
        }
    }
    close(user->newsockfd);
}

void User::zacniPracovat() {
    pthread_create(vlakno, NULL, &User::pracuj, this);
}