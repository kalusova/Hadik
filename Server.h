//
// Created by Katarína Kalusová on 05/01/2022.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

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
};


#endif //UNTITLED5_SERVER_H
