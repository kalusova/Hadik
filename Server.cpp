//
// Created by Katarína Kalusová on 05/01/2022.
//

#include "Server.h"

Server::Server(){
    pocetHracov = 0;
    pocetPripojenych = 0;
}

struct thread_data {
    volatile int socket;
    pthread_mutex_t *mutex;
};

int Server::makeServer(char const* port)
{
    char buffer[256];
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    bool koniec = false;
    std::string s;

    // ZISTOVANIE POCTU HRACOV
    printf("Prosím zadajte pocet hracov: \n(cislo od 1 do 4)");
    bzero(buffer,256);
    fgets(buffer, 255, stdin);

    char znak = buffer[0];
    int cislo = znak - '0';

    //KONTROLA spravne zadaneho cisla
    if (strlen(buffer)>2){
        printf("Zadana hodnota musi byt cislo! Skus znova. Ak znovu zadáš zle, hra sa vypne.\n");
        fgets(buffer, 255, stdin);
        char znak = buffer[0];
        int cislo = znak - '0';

        if (strlen(buffer)>2){
            printf("Zadana hodnota musi byt cislo! Ukoncujem.\n");
        } else {
            if (!(cislo > 0 && cislo < 5)) {
                printf("Zadana hodnota musi byt od 1 do 4.\n");
                return 1;
            } else {
                this->pocetHracov = cislo;
            }
        }
    } else{
        if (!(cislo > 0 && cislo < 5)) {
            printf("Zadana hodnota musi byt od 1 do 4.\n");
            return 1;
        } else {
            this->pocetHracov = cislo;
        }
    }

    //vynulujeme a zinicializujeme cielovu adresu
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(port));

    //vytvorenie socketu v domene AF_INET
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    //Priradíme vyplnenú sieťovú adresu vytvorenému socketu.
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket address");
        return 2;
    }

    //Pripravíme socket pre príjmanie spojení od klientov. Maximálna dĺžka fronty neobslúžených spojení je 4.
    listen(sockfd, 4);
    cli_len = sizeof(cli_addr);

    //vytvorenie spolocneho mutexu a jeho inicializacia
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    //vlozenie do zdielanych dat
    struct thread_data threadData;
    threadData.mutex = &mutex;

    //vytvorenie tolkych vlakien kolko je pocet hracov
    pthread_t clients [this->pocetHracov];
    for (int i = 0; i < this->pocetHracov; i++) {
        //blokuje server az pokym sa klient nepripoji
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &cli_len);  //Počkáme na a príjmeme spojenie od klienta.
        printf("client cislo %i sa PRIPOJIL\n", pocetPripojenych + 1);
        pthread_mutex_lock(threadData.mutex); //zamknutie mutexu kt. riadi pristup k datam - zabezpecenie jedinecneho pristupu
        threadData.socket = newsockfd; //socket pre dane vlakno

        bzero(buffer,256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            return 4;
        }
        printf("Meno hraca cislo %d: %s\n",i+1, buffer);

        //informovanie klienta o tom ze sa este vsetci nepripojili
        if (i == pocetHracov-1){
            s = "Vsetci hraci pripojeni";
        } else {
            s = "Caka sa na pripojenie vsekych hracov!";
        }
        bzero(buffer, 255);
        for (int j = 0; j < 255; j++) {
            buffer[j] = s[j];
        }
        int n = write(newsockfd, buffer, strlen(buffer)); //posielanie
        if (n < 0) {
            perror("Error writing to socket");
        }

        pthread_mutex_unlock(threadData.mutex); //povolenie pristupu k zapisu do zdielanych dat
        if (pthread_create(&clients[i], NULL, &(Server::hra), &threadData) != 0){ // Vytvoríme nové vlákno so zadanými atribútmi, spustíme v ňom funkciu thread_main s ukazovateľom na inštanciu thread_data.
            printf("Failed to create thread\n");
        } else {
            pocetPripojenych++;
        }
    }

    for (int k = 0; k < this->pocetHracov; k++) {
        pthread_join(clients[k], NULL); //Počkáme na dokončenie všetkých spustených vlákien.
    }

    pthread_mutex_destroy(&mutex);
    close(newsockfd);
    close(sockfd);

    return 0;
}

void *Server::hra(void *thread_data) {
    //printf("hra");
    return nullptr;
}

