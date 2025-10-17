#ifndef METODYPOMOCNICZE_H
#define METODYPOMOCNICZE_H

#include <iostream>
#include <sstream>
#include <algorithm>


#include "Uzytkownik.h"

using namespace std;

class MetodyPomocnicze
{
public:
    static string konwersjaIntNaString(int liczba);
    static string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst);
    static string wczytajLinie();
    static char wczytajZnak();
    static int wczytajLiczbeCalkowita();
    static string pobierzLiczbe(string tekst, int pozycjaZnaku);
    static int konwersjaStringNaInt(string liczba);
};

#endif
