//
// Created by Dominika Barbieriková & Katarína Kalusová on 29. 12. 2020.
//
#include <string>
#include <iostream>
#include <unistd.h>
#include "Logika.h"

#ifndef SEMESTRALKA_HADIK_H
#define SEMESTRALKA_HADIK_H

using namespace std;

class Hadik{
public:
    explicit Hadik( Logika *pPravidla);
    bool move(char znak);
    std::string getFarba() const;
    void setFarba(const std::string &pfarba);
    int getX() const;
    void setX(int px);
    int getY() const;
    void setY(int py);
    void goTo(int px, int py);
    void pridajDlzku();
    void setSmer(char pSmer);
    void vlozDoPola();
    int getBodyCislo();
    std::string getBody() const;

    void setPoradie(int poradie);

    int getPoradie() const;

private:
    int x;
    int y;
    int dlzka;
    std::string** pole;
    std::string smer;
    std::string farba;
    Logika *pravidla;
    int body;
    bool koniec;
    int poradie;

};

#endif //SEMESTRALKA_HADIK_H