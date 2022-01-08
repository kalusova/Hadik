/**
 * @file Server.cpp
 * @authors Dominika Barbierikova, Katarina Kalusova
 * @date 15.12.2021
 */

#include "Server.h"
#include "Hadik.h"

/**
 * Konštruktor triedy Server
 *
 * Inicializuje privátne premenné triedy
 * Reprezentuje server na ktorý sa pripájajú klienti
 * Použitý protokol TCP
 */
Server::Server() {
    pocetHracov = 0;
    pocetPripojenych = 0;
}

/**
 * Zdieľané dáta thread_data
 */
struct thread_data {
    volatile int socket[4];
    pthread_mutex_t *mutex;
    Logika *logika;
    int poradie;
    int body[4][2];
    int pocetHrac;
    int pocetPripoj;
};

/**
 * Metóda makeServer() vytvára samotný server
 * @param port určuje číslo portu na ktorý sa budú moct klienti pripajat
 * @return 0 ak vsetko dopadlo dobre, inak ak nastala chyba
 */
int Server::makeServer(char const *port) {
    char buffer[1000];
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    std::string s;

    srand(time(NULL));

    // ZISTOVANIE POCTU HRACOV
    printf("Prosím zadajte pocet hracov: \n(cislo od 1 do 4)");
    bzero(buffer, 1000);
    fgets(buffer, 1000, stdin);

    char znak = buffer[0];
    int cislo = znak - '0';

    //KONTROLA spravne zadaneho cisla
    if (strlen(buffer) > 2) {
        printf("Zadana hodnota musi byt cislo! Skus znova. Ak znovu zadáš zle, hra sa vypne.\n");
        fgets(buffer, 1000, stdin);
        char znak = buffer[0];
        int cislo = znak - '0';

        if (strlen(buffer) > 2) {
            printf("Zadana hodnota musi byt cislo! Ukoncujem.\n");
        } else {
            if (!(cislo > 0 && cislo < 5)) {
                printf("Zadana hodnota musi byt od 1 do 4.\n");
                return 1;
            } else {
                this->pocetHracov = cislo;
            }
        }
    } else {
        if (!(cislo > 0 && cislo < 5)) {
            printf("Zadana hodnota musi byt od 1 do 4.\n");
            return 1;
        } else {
            this->pocetHracov = cislo;
        }
    }

    //vynulujeme a zinicializujeme cielovu adresu
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(port));

    //vytvorenie socketu v domene AF_INET
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    //Priradíme vyplnenú sieťovú adresu vytvorenému socketu.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
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
    threadData.logika = new Logika();
    threadData.pocetHrac = 0;
    threadData.pocetPripoj = 0;

    for (int i = 0; i < 4; i++) {
        threadData.body[i][1] = 0;
        threadData.body[i][0] = 0;
    }

    for (int i = 0; i < 4; ++i) {
        threadData.socket[i] = 0;
    }


    //vytvorenie tolkych vlakien kolko je pocet hracov
    pthread_t clients[this->pocetHracov];
    for (int i = 0; i < this->pocetHracov; i++) {
        //blokuje server az pokym sa klient nepripoji
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                           &cli_len);  //Počkáme na a príjmeme spojenie od klienta.
        printf("client cislo %i sa PRIPOJIL\n", pocetPripojenych + 1);
        pthread_mutex_lock(
                threadData.mutex); //zamknutie mutexu kt. riadi pristup k datam - zabezpecenie jedinecneho pristupu
        threadData.socket[i] = newsockfd; //socket pre dane vlakno
        threadData.poradie = i;
        threadData.pocetHrac = pocetHracov;

        //informovanie klienta o tom ze sa este vsetci nepripojili
        if (i == pocetHracov - 1) {
            s = "Vsetci hraci pripojeni";
        } else {
            s = "Caka sa na pripojenie vsekych hracov!";
        }
        bzero(buffer, 1000);
        for (int j = 0; j < s.length(); j++) {
            buffer[j] = s[j];
        }
        int n = write(newsockfd, buffer, strlen(buffer)); //posielanie
        if (n < 0) {
            perror("Error writing to socket");
        }

        pthread_mutex_unlock(threadData.mutex); //povolenie pristupu k zapisu do zdielanych dat

        if (pthread_create(&clients[i], NULL, &(Server::hra), &threadData) !=
            0) { // Vytvoríme nové vlákno so zadanými atribútmi, spustíme v ňom funkciu thread_main s ukazovateľom na inštanciu thread_data.
            printf("Failed to create thread\n");
        } else {
            pocetPripojenych++;
            pthread_mutex_lock(threadData.mutex);
            threadData.pocetPripoj = pocetPripojenych;
            pthread_mutex_unlock(threadData.mutex);
        }
    }

    /*  if(buffer[0] == 'x' && strlen(buffer) == 2){
          for (int i = 0; i < 2; ++i) {
              n = write(threadData.socket[i], buffer, strlen(buffer)); //posielanie
              if (n < 0) {
                  perror("Error writing to socket");
              }
          }
      }*/



    for (int k = 0; k < this->pocetHracov; k++) {
        pthread_join(clients[k], NULL);//Počkáme na dokončenie všetkých spustených vlákien.
    }

    pthread_mutex_lock(threadData.mutex);

    if (pocetHracov == 1) {
        s = "Ziskal si " + std::to_string(threadData.body[0][1]);
        s += " bodov\n";
    } else {
        int pom = -1;
        int pocetRovnakych = 0;
        int cisloHraca = 0;
        int rovnake[4];
        for (int i = 0; i < 4; i++) {
            rovnake[i] = -1;
        }
        for (int i = 0; i < pocetHracov; i++) {
            if (threadData.body[i][1] > pom) {
                pom = threadData.body[i][1];
                cisloHraca = threadData.body[i][0];
            }
        }
        for (int i = 0; i < pocetHracov; i++) {
            if (pom == threadData.body[i][1]) {
                rovnake[pocetRovnakych] = threadData.body[i][0];
                pocetRovnakych++;
            }
        }
        if (pocetRovnakych == 1) {
            s = "Vyhral hrac cislo: " + std::to_string(cisloHraca);
            s += " , s poctom bodov: " + std::to_string(pom);
            s += "\n";
            printf("Vyhral hrac cislo: %d , s poctom bodov: %d\n", cisloHraca, pom);
        } else {
            s = "REMIZA: \n";
            printf("REMIZA:\n");
            for (int i = 0; i < pocetRovnakych; i++) {
                s += "Hrac cislo: " + std::to_string(rovnake[i]);
                s += " , s poctom bodov: " + std::to_string(pom);
                s += "\n";
                printf("Hrac cislo: %d , s poctom bodov: %d\n", rovnake[i], pom);
            }
        }
    }
    pthread_mutex_unlock(threadData.mutex);

    bzero(buffer, 1000);
    for (int j = 0; j < s.length(); j++) {
        buffer[j] = s[j];
    }
    for (int i = 0; i < pocetHracov; i++) {
        n = write(threadData.socket[i], buffer, strlen(buffer)); //posielanie
        if (n < 0) {
            perror("Error writing to socket");
        }
    }

    pthread_mutex_lock(threadData.mutex);
    delete threadData.logika;
    threadData.logika = nullptr;
    pthread_mutex_unlock(threadData.mutex);

    bzero(buffer, 1000);
    pthread_mutex_destroy(&mutex);
    printf("Server sa ukoncuje!\n");
    close(newsockfd);
    close(sockfd);

    return 0;
}

/**
 * Metóda hra spusta hru jednotlivym klientom/vlaknam, zavolana je pri vytvoreni vlakna
 * @param thread_data ako paramteter dostáva ukazovateľ na štruktúru zdieľaných dát
 * @return nullptr ak vsetko dobre dopadlo
 */
void *Server::hra(void *thread_data) {
    char buffer[1000];
    bool koniec = false;
    struct thread_data *data = (struct thread_data *) thread_data;
    pthread_mutex_lock(data->mutex);
    int socket = data->socket[data->poradie];

    Hadik *hadik = new Hadik(data->logika);

    switch (data->poradie) {
        case 0:
            hadik->setPoradie(1);
            hadik->setXY(2, 2);
            hadik->setFarba("\033[31m");
            break;
        case 1:
            hadik->setPoradie(2);
            hadik->setXY(2, 4);
            hadik->setFarba("\033[32m");
            break;
        case 2:
            hadik->setPoradie(3);
            hadik->setXY(2, 6);
            hadik->setFarba("\033[33m");
            break;
        case 3:
            hadik->setPoradie(4);
            hadik->setXY(2, 8);
            hadik->setFarba("\033[34m");
            break;
    }
    pthread_mutex_unlock(data->mutex);
    hadik->vlozDoPola();
    std::string plocha = "";
    printf("Pocet pripojenych : %d, pocet hracov : %d\n", data->pocetPripoj, data->pocetHrac);
    while (!koniec) {
        if (data->pocetPripoj == data->pocetHrac) {
            plocha = data->logika->printBorder();
            plocha += hadik->getBody();
            bzero(buffer, 1000);
            for (int i = 0; i < plocha.length(); ++i) {
                buffer[i] = plocha[i];
            }

            int n = write(socket, buffer, strlen(buffer)); //posielanie
            if (n < 0) {
                perror("Error writing to socket");
            }

            bzero(buffer, 1000);
            n = read(socket, buffer, 1000);
            if (n < 0) {
                perror("Error reading from socket");
                exit(4);
            }

            if ((buffer[0] == 'x' || buffer[0] == 'X') && strlen(buffer) == 2) {
                koniec = true;
                pthread_mutex_lock(data->mutex);
                data->body[hadik->getPoradie() - 1][0] = hadik->getPoradie();
                data->body[hadik->getPoradie() - 1][1] = hadik->getBodyCislo();
                pthread_mutex_unlock(data->mutex);

                bzero(buffer, 1000);
                break;
            } else {
                hadik->move(buffer[0]);
                bzero(buffer, 1000);
            }
        }
    }
    delete (hadik);
    return nullptr;
}

/**
 * Destruktor Servera
 */
Server::~Server() = default;

