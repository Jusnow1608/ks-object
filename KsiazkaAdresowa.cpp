#include "KsiazkaAdresowa.h"

KsiazkaAdresowa::KsiazkaAdresowa()//konstruktor?
{
    uzytkownikMenadzer.wczytajUzytkownikowZPliku();
}

void KsiazkaAdresowa::rejestracjaUzytkownika()
{
    uzytkownikMenadzer.rejestracjaUzytkownika();
}

void KsiazkaAdresowa::wypiszWszystkichUzytkownikow()
{
    uzytkownikMenadzer.wypiszWszystkichUzytkownikow();
}



