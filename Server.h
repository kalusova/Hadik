//
// Created by Katarína Kalusová on 05/01/2022.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cctype>
#include <pthread.h>
#include <string>
//#include "Ovocie.h"

#ifndef UNTITLED5_SERVER_H
#define UNTITLED5_SERVER_H



class Server {
private:
    int pocetHracov ;
    int pocetPripojenych;

public:
    Server();
    int makeServer(const char* port);
    static void* hra(void * thread_data);

    static int getPocetHracov() ;

    static int getPocetPripojenych() ;

};


#endif //UNTITLED5_SERVER_H
