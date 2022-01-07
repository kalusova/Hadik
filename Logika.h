//
// Created by Dominika Barbieriková & Katarína Kalusová on 30/12/2020.
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
    //std::string vypisPole();
    std::string **getPole();
    void setPole(std::string **pole);

    ~Logika(){
        for(int i = 0; i < 20; i++) {
            delete[] pole[i];
        }
        delete[] pole;
    }

private:
    std::string** pole = new string*[20];

};

#endif //SEMESTRALKA_PRAVIDLA_H
