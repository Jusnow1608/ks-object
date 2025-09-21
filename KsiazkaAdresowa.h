#ifndef KSIAZKAADRESOWA_H
#define KSIAZKAADRESOWA_H

#include <iostream>

#include "UzytkownikMenadzer.h"
#include "AdresatMenadzer.h"

using namespace std;

class KsiazkaAdresowa
{
UzytkownikMenadzer uzytkownikMenadzer;
AdresatMenadzer adresatMenadzer;
int idOstatniegoAdresata;

public:
KsiazkaAdresowa(string nazwaPlikuZUzytkownikami, string nazwaPlikuZAdresatami):uzytkownikMenadzer (nazwaPlikuZUzytkownikami), adresatMenadzer(nazwaPlikuZAdresatami), idOstatniegoAdresata(0)
    {
    uzytkownikMenadzer.wczytajUzytkownikowZPliku();
    }
void rejestracjaUzytkownika();
void wypiszWszystkichUzytkownikow();
void logowanieUzytkownika();
void zmianaHaslaZalogowanegoUzytkownika();
void dodajAdresata();
void wypiszWszystkichAdresatow();

};

#endif
