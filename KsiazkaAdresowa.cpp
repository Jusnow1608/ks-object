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

    adresatMenadzer.pobierzAdresatowZalogowanegoUzytkownikaZPliku(id);
}

void KsiazkaAdresowa::zmianaHaslaZalogowanegoUzytkownika()
{
    uzytkownikMenadzer.zmianaHaslaZalogowanegoUzytkownika();
}

void KsiazkaAdresowa::dodajAdresata()
{
    if(uzytkownikMenadzer.czyUzytkownikZalogowany()==true)
    {
        adresatMenadzer.dodajAdresata();
    }
    else
    {
        cout << "Aby dodac adresata, musisz byc zalogowany." << endl;
        system("pause");
    }
}

void KsiazkaAdresowa::wyswietlWszystkichAdresatow()
{
    if(uzytkownikMenadzer.czyUzytkownikZalogowany()==true)
    {
        adresatMenadzer.wyswietlWszystkichAdresatow();
    }
    else
    {
        cout << "Aby wyswietlic adresatow, musisz byc zalogowany." << endl;
        system("pause");
    }
}

void KsiazkaAdresowa::wylogowanieUzytkownika()
{
    uzytkownikMenadzer.wylogowanieUzytkownika();

    adresatMenadzer.wyczyscAdresatow();
}





