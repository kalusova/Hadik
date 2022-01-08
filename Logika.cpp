/**
 * @file Logika.cpp
 * @authors Dominika Barbierikova, Katarina Kalusova
 * @date 15.12.2021
 */

#include "Logika.h"

/**
 * Konstruktor triedy Logika
 * inicializuje pole na biele znaky " "
 * inicializuje parameter zjedeny - indikuje ci bolo ovocie zjedene a ci sa ma vytvorit nove
 */
Logika::Logika() {
    for (int i = 0; i < 20; i++) {
        pole[i] = new std::string[20];
        for (int j = 0; j < 20; j++) {
            pole[i][j] = " ";
        }
    }
    this->zjedeny = true;
}

/**
 * Metoda printBorder urcuje na ktorych miestav v poli sa maju nachadzat znaky * ktore oznacuju ohranicenie hracej plochy
 * @return s - string v ktorom je zapisane pole
 */
std::string Logika::printBorder() {
    std::string s = "" ;

    for (int i = 0; i < 20; i++) {
        pole[0][i] = "*";
        pole[19][i] = "*";
        pole[i][0] = "*";
        pole[i][19] = "*";
    }

    this->vytvorOvocie();

    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < 20; i++) {
            s += pole[j][i] ;
        }
        s += "\n";
    }
    return s + "\n";
}

/**
 * Metoda getPole vracia pole
 * @return pole
 */
std::string **Logika::getPole() {
    return pole;
}

/**
 * Metoda vytvorOvocie vytvara ovocie pre hadika, ktore zbiera a nasledne za to ziskava body
 * V tejto metode sa len urcuje na akych suradniciach sa ovocie zobrazi
 */
void Logika::vytvorOvocie() {
    if(zjedeny== true){
      this->ovocieX = rand() % 17 + 1;
      this->ovocieY = rand() % 17 + 1;
        this->pole[ovocieX][ovocieY] = "?";
        this->zjedeny = false;
    }
}

/**
 * Metoda getOvocieX vracia hodnotu x-ovej suradnice ovocia
 * @return ovocieX
 */
int Logika::getOvocieX() const {
    return ovocieX;
}

/**
 * Metoda getOvocieY vracia hodnotu y-ovej suradnice ovocia
 * @return ovocieY
 */
int Logika::getOvocieY() const {
    return ovocieY;
}

/**
 * Metoda setZjedeny nastavuje hodnotu parametra zjedeny na hodnotu z parametra
 * @param zjedeny urcuje aka hodnota bude nastavena
 */
void Logika::setZjedeny(bool zjedeny) {
    Logika::zjedeny = zjedeny;
}




