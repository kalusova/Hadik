/**
 * @file Client.h
 * @authors Dominika Barbierikova, Katarina Kalusova
 * @date 15.12.2021
 */

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
public:
    Client();
    int makeClient(const char* port, const char* host);
};

#endif //UNTITLED5_CLIENT_H
