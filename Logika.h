//
// Created by Dominika Barbieriková & Katarína Kalusová on 15. 12. 2021.
//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <curses.h>

#ifndef SEMESTRALKA_PRAVIDLA_H
#define SEMESTRALKA_PRAVIDLA_H

using namespace std;

class Logika {
public:
    Logika();
    std::string printBorder();
    std::string **getPole();
    void vytvorOvocie();

    int getOvocieX() const;

    int getOvocieY() const;

    void setZjedeny(bool zjedeny);

private:
    std::string** pole = new string*[20];
    bool zjedeny;
    int ovocieX;
    int ovocieY;
};

#endif //SEMESTRALKA_PRAVIDLA_H
