//
// Created by Dominika Barbieriková & Katarína Kalusová on 29. 12. 2021.
//

#include "Server.h"
#include "Client.h"

int main(int argc, char const *argv[]){
   if(argc > 1){
        if(*argv[1] == 's'){
            //spusti server ./hadik s 4412
            Server* server = new Server();
            server->makeServer(argv[2]);


        }
        else if (*argv[1] == 'c'){
            //spusti client ./hadik c 4412
            Client* client = new Client();
            client->makeClient(argv[2], "localhost");
        }
        else {
            std::cout << "nevhodny parameter, pouzi c ako client alebo s ako server";
        }
    }  else {
        std::cout << "male/velke mnozstvo parametrov";
    }
    return 0;
}