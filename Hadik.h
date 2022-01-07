//
// Created by Dominika Barbieriková & Katarína Kalusová on 29. 12. 2021.
//
#include <unistd.h>
#include "Logika.h"

#ifndef SEMESTRALKA_HADIK_H
#define SEMESTRALKA_HADIK_H

using namespace std;

class Hadik{
public:
    explicit Hadik( Logika *pPravidla);
    bool move(char znak);
    void setFarba(const std::string &pfarba);
    void setX(int px);
    void setY(int py);
    void goTo(int px, int py);
    void setSmer(char pSmer);
    void vlozDoPola();
    int getBodyCislo();
    std::string getBody() const;
    void setPoradie(int poradie);
    int getPoradie() const;
    void setXY(int pX, int pY);
    ~Hadik(){
        for(int i = 0; i < 20; i++) {
            delete[] pole[i];
        }
        delete[] pole;
        //delete(pravidla);
        pravidla = nullptr;
    }

private:
    int x;
    int y;
    std::string** pole;
    std::string smer;
    std::string farba;
    Logika *pravidla;
    int body;
    int poradie;
};

#endif //SEMESTRALKA_HADIK_H