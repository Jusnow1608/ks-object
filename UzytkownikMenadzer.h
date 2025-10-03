#ifndef UZYTKOWNIKMENADZER_H
#define UZYTKOWNIKMENADZER_H

#include <iostream>
#include <vector>
#include<windows.h>
#include <fstream>
#include <sstream>


#include "Uzytkownik.h"
#include "PlikZUzytkownikami.h"

using namespace std;

class UzytkownikMenadzer
{
    int idZalogowanegoUzytkownika;
    vector <Uzytkownik> uzytkownicy;
    PlikZUzytkownikami plikZUzytkownikami;

    Uzytkownik podajDaneNowegoUzytkownika();
    int pobierzIdNowegoUzytkownika();
    bool czyIstniejeLogin(string login);


public:
    UzytkownikMenadzer(string nazwaPlikuZUzytkownikami): plikZUzytkownikami(nazwaPlikuZUzytkownikami)
    {
    };

    void rejestracjaUzytkownika();
    void wypiszWszystkichUzytkownikow();
    void wczytajUzytkownikowZPliku();
    void logowanieUzytkownika();
    void zmianaHaslaZalogowanegoUzytkownika ();
    void ustawIdZalogowanegoUzytkownika (int noweIdZalogowanegoUzytkownika);
    int pobierzIdZalogowanegoUzytkownika();
    void wylogowanieUzytkownika();
    bool czyUzytkownikZalogowany();
};

#endif
