//
// Created by Katarína Kalusová on 05/01/2022.
//

#ifndef UNTITLED5_CLIENT_H
#define UNTITLED5_CLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <string>
#include <iostream>

class Client {
private:
    std::string name;
    int cislo;
    int points;

public:
    Client();
    int makeClient(const char* port, const char* host);
};


#endif //UNTITLED5_CLIENT_H
