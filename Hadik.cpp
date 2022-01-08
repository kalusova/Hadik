/**
 * @file Hadik.cpp
 * @authors Dominika Barbierikova, Katarina Kalusova
 * @date 15.12.2021
 */

#include "Hadik.h"

#define RED      "\033[31m"     /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */

/**
 * Konstruktor triedy Hadik
 * @param pPravidla su ukazovatelom na triedu Logika kde su definovane dalsie pravidla pre spravanie hadika
 *
 * konstruktor inicializuje privatne premenne
 */
Hadik::Hadik(Logika *pPravidla) {
    this->x = 0;
    this->y = 0;
    this->pole =  pPravidla->getPole();
    this->smer = "pravo";
    this->pravidla = pPravidla;
    this->body = 0;
    this->poradie = 0;
}

/**
 * Metoda setPoradie nastavi privatny paramter poradie na hodnotu paramtra
 * @param poradie nesie hodnotu, ktora je nestavena
 */
void Hadik::setPoradie(int poradie) {
    Hadik::poradie = poradie;
}

/**
 * Metoda getPoradie vrati hodnotu ktora sa nachadza v priavtnom parametri poradie
 * @return poradie hadika
 */
int Hadik::getPoradie() const {
    return poradie;
}

/**
 * Metoda goTo posunie hadika na hracom poli na suradnice px a py
 * @param px suradnica x na hracom poli
 * @param py suradnica y na hracom poli
 */
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

/**
 * Metoda getBody spracuje aktualny pocet bodov na string a vrati tuto hodnotu v retazci tak aby mohla byt poslana ako text
 * @return s , s je string obsahujuci retazec ozrejmnujuci hracovi ake je cislo a kolko ma bodov: "Si hrac cislo: * a tvoje skore je: #"
 */
std::string Hadik::getBody() const {
    std::string s = "Si hrac cislo " + std::to_string(this->poradie);
        s += " a tvoje skore je: " + std::to_string(this->body);
    return s + "\n";
}

/**
 * Metoda getBodyCislo vracia hodnotu bodov ako integer
 * @return body hadika
 */
int Hadik::getBodyCislo(){
    return this->body;
}

/**
 * Metoda move spracuje znak ktory dostane a urci ci sa hadik bude posuvat hore, dole, vpravo alebo v lavo. Taktiez zistuje ci sa este moze posuvat.
 * @param znak je znak ktory zada pouzivatel do inputu
 * @return true alebo false na zaklade toho ci sa hadik moze alebo nemoze posunut. False vrati aj v tom pripade ze nastala chyba.
 */
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

/**
 * Metoda setFarba nastavi hadikovu jeho farbu
 * @param pfarba je farba ktora bude hadikovi pridelena
 */
void Hadik::setFarba(const string &pfarba) {
    this->farba = pfarba;
}

/**
 * Metoda setY nastavuje privatny parameter y na pxy * @param py
 */
void Hadik::setX(int px) {
    this->x = px;
}

/**
 * Metoda setY nastavuje privatny parameter y na pxy * @param py
 */
void Hadik::setY(int py) {
    this->y = py;
}

/**
 * Metoda setSmer nastavuje privatny parameter hadika smer na hodnotu hore, dole, pravo, lavo na zaklade toho aky znak bol zadany
 * @param pSmer moze prist pismeno w,a,s,d
 */
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

/**
 * metoda vlozDoPola vlozi znak hadika do hracieho pola
 */
void Hadik::vlozDoPola() {
    this->pole[this->x][this->y] = this->farba + ">" + "\033[0m";
}

/**
 * Metoda setXY nastavi naraz oba parametre x,y na hodnoty px a py
 * @param pX
 * @param pY
 */
void Hadik::setXY(int pX, int pY){
    this->x = pX;
    this->y = pY;
}


