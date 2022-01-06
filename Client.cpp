//
// Created by Katarína Kalusová on 05/01/2022.
//

#include "Client.h"

Client::Client(){
    this->points=0;
}
int Client::makeClient(const char* port, const char* host)
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    bool koniec = false;

    char buffer[256];

    //Použijeme funkciu gethostbyname na získanie informácii o počítači, ktorého hostname je v prvom argumente.
    server = gethostbyname(host);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }

    //Vynulujeme a zinicializujeme adresu, na ktorú sa budeme pripájať.
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(port));

    //Vytvoríme si socket v doméne AF_INET.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 3;
    }

    //Pripojíme sa na zadanú sieťovú adresu.
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting to socket");
        return 4;
    }

    printf("Prosim zadaj meno: ");
    bzero(buffer,256);
    fgets(buffer, 255, stdin);

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    }

    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        return 6;
    }

    printf("%s\n",buffer);

    close(sockfd);
    return 0;
}