/**
 * @file main.cpp
 * @authors Dominika Barbierikova, Katarina Kalusova
 * @date 15.12.2021
 */

#include "Server.h"
#include "Client.h"

int main(int argc, char const *argv[]){
   if(argc > 1){
        if(*argv[1] == 's'){
            //spusti server ./hadik s 4412
            Server* server = new Server();
            server->makeServer(argv[2]);
            delete(server);
        }
        else if (*argv[1] == 'c'){
            //spusti client ./hadik c 4412
            Client* client = new Client();
            client->makeClient(argv[2], "localhost");
            delete(client);
        }
        else {
            std::cout << "nevhodny parameter, pouzi c ako client alebo s ako server";
        }
    }  else {
        std::cout << "male/velke mnozstvo parametrov";
    }
    return 0;
}