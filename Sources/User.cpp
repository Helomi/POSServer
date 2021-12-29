//
// Created by helom on 29. 12. 2021.
//

#include "../Headers/User.h"

User::User(int pnewsockfd) {
    newsockfd = pnewsockfd;
    for (int i = 0; i < 1; ++i) {
        bzero(buffer,256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            exit(4);
        }
        printf("Here is the message: %s\n", buffer);

        string msg = "asdfgjkl|šdfghjkln|sfgdnjkl|END|";
        n = write(newsockfd, msg.c_str(), strlen(msg.c_str())+1);
        if (n < 0)
        {
            perror("Error writing to socket");
            exit(5);
        }
    }
    close(newsockfd);
}
