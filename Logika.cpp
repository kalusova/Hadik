//
// Created by Dominika Barbieriková & Katarína Kalusová on 15. 12. 2021.
//

#include "Logika.h"

Logika::Logika() {
    for (int i = 0; i < 20; i++) {
        pole[i] = new std::string[20];
        for (int j = 0; j < 20; j++) {
            pole[i][j] = " ";
        }
    }
    this->zjedeny = true;
}

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


std::string **Logika::getPole() {
    return pole;
}

void Logika::vytvorOvocie() {
    if(zjedeny== true){
      this->ovocieX = rand() % 17 + 1;
      this->ovocieY = rand() % 17 + 1;
        this->pole[ovocieX][ovocieY] = "?";
        this->zjedeny = false;
    }
}

int Logika::getOvocieX() const {
    return ovocieX;
}

int Logika::getOvocieY() const {
    return ovocieY;
}


void Logika::setZjedeny(bool zjedeny) {
    Logika::zjedeny = zjedeny;
}




