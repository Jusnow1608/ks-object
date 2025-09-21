#include "KsiazkaAdresowa.h"

void KsiazkaAdresowa::rejestracjaUzytkownika()
{
    uzytkownikMenadzer.rejestracjaUzytkownika();
}

void KsiazkaAdresowa::wypiszWszystkichUzytkownikow()
{
    uzytkownikMenadzer.wypiszWszystkichUzytkownikow();
}

void KsiazkaAdresowa::logowanieUzytkownika()
{
    uzytkownikMenadzer.logowanieUzytkownika();

    int id =  uzytkownikMenadzer.pobierzIdZalogowanegoUzytkownika();

    adresatMenadzer.ustawIdZalogowanegoUzytkownika(id);

    adresatMenadzer.pobierzAdresatowZalogowanegoUzytkownikaZPliku();
}

void KsiazkaAdresowa::zmianaHaslaZalogowanegoUzytkownika()
{
    uzytkownikMenadzer.zmianaHaslaZalogowanegoUzytkownika();
}

void KsiazkaAdresowa::dodajAdresata()
{
    adresatMenadzer.dodajAdresata();
}

void KsiazkaAdresowa::wypiszWszystkichAdresatow()
{
    adresatMenadzer.wypiszWszystkichAdresatow();
}





