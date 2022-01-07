//
// Created by Dominika Barbieriková & Katarína Kalusová on 29. 12. 2020.
//



#include "Hadik.h"

#define RED      "\033[31m"     /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */

Hadik::Hadik(Logika *pPravidla) {
    this->x = 0;
    this->y = 0;
    this->pole =  pPravidla->getPole();
    this->smer = "pravo";
    this->dlzka = 0;
    this->pravidla = pPravidla;
    this->koniec = false;
    this->body = 0;
    this->poradie = 0;
}

void Hadik::setPoradie(int poradie) {
    Hadik::poradie = poradie;
}

int Hadik::getPoradie() const {
    return poradie;
}

const std::string &Hadik::getMeno() const {
    return meno;
}

void Hadik::setMeno(const std::string &meno) {
    Hadik::meno = meno;
}

void Hadik::goTo(int px, int py) {
    this->pole[this->x][this->y] = " ";
    this->setX(px);
    this->setY(py);
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    if(this->smer == "pravo") {
        this->pole[this->x][(this->y)+i] = this->farba + ">" + "\033[0m";
        this->pole[this->x][(this->y)+i-1] = " ";
        pravidla->printBorder();
        i++;
      //  usleep(1000000);
    }
    if(this->smer == "lavo") {
        this->pole[this->x][this->y-j] = this->farba + "<" + "\033[0m";
        this->pole[this->x][this->y-j+1] = " ";
        pravidla->printBorder();
        j++;
      //  usleep(1000000);
    }
    if(this->smer == "hore") {
        this->pole[this->x-k][this->y] = this->farba + "A" + "\033[0m";
        this->pole[this->x-k+1][this->y] = " ";
        pravidla->printBorder();
        k++;
     //   usleep(1000000);
    }
    if(this->smer == "dole") {
        this->pole[this->x+l][this->y] = this->farba + "v" + "\033[0m";
        this->pole[this->x+l-1][this->y] = " ";
        pravidla->printBorder();
        l++;
      //  usleep(1000000);
    }

    if(this->x == this->pravidla->getOvocieX() && this->y == this->pravidla->getOvocieY()) {
        this->pravidla->setZjedeny(true);
        this->body += 10;
    }
}

std::string Hadik::getBody() const {
    std::string s = "Si hrac cislo " + std::to_string(this->poradie);
        s += " a tvoje skore je: " + std::to_string(this->body);
    return s + "\n";
}

int Hadik::getBodyCislo(){
    return this->body;
}

bool Hadik::move(char znak) {
        this->setSmer(znak);
        if(this->smer == "hore"){
            if(this->x-1 > 0) {
                int px = this->x-1;
                this->goTo(px, this->y);
                return true;
            } else {
                cout << "Sem uz nemozes ist";
                return false;
            }
        } else if(this->smer == "lavo"){
            if(this->y-1 > 0) {
                int py = this->y-1;
                this->goTo(this->x,py);
                return true;
            } else {
                cout << "Sem uz nemozes ist";
                return false;
            }
        } else if(this->smer == "dole"){
            if(this->x+1 < 19) {
                int px = this->x+1;
                this->goTo(px,this->y);
                return true;
            } else {
                cout << "Sem uz nemozes ist";
                return false;
            }
        } else if(this->smer == "pravo"){
            if(this->y+1 < 19) {
                int py = this->y+1;
                this->goTo(this->x,py);
                return true;
            } else {
                cout << "Sem uz nemozes ist";
                return false;
            }
        }
        cout << "ERROR in function Hadik::move()";
        return false;
}

std::string Hadik::getFarba() const {
    return this->farba;
}

void Hadik::setFarba(const string &pfarba) {
    this->farba = pfarba;
}

int Hadik::getX() const {
    return this->x;
}

void Hadik::setX(int px) {
    this->x = px;
}

int Hadik::getY() const {
    return this->y;
}

void Hadik::setY(int py) {
    this->y = py;
}

void Hadik::pridajDlzku() {
    this->dlzka++;
}

void Hadik::setSmer(char pSmer) {
    if(pSmer == 'W' || pSmer == 'w') {
        this->smer = "hore";
    } else if(pSmer == 'A' || pSmer == 'a'){
        this->smer = "lavo";
    } else if(pSmer == 'S' || pSmer == 's'){
        this->smer = "dole";
    } else if(pSmer == 'D' || pSmer == 'd'){
        this->smer = "pravo";
    }
}

void Hadik::vlozDoPola() {
    this->pole[this->x][this->y] = this->farba + ">" + "\033[0m";
}

void Hadik::setXY(int pX, int pY){
    this->x = pX;
    this->y = pY;
}


