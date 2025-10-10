#include <iostream>
#include "KsiazkaAdresowa.h"

using namespace std;

int main()
{
    KsiazkaAdresowa ksiazkaAdresowa("Uzytkownicy.txt", "Adresaci.txt");
    ksiazkaAdresowa.wypiszWszystkichUzytkownikow();
    ksiazkaAdresowa.rejestracjaUzytkownika();
    ksiazkaAdresowa.wypiszWszystkichUzytkownikow();
    ksiazkaAdresowa.logowanieUzytkownika();
    ksiazkaAdresowa.zmianaHaslaZalogowanegoUzytkownika();
    ksiazkaAdresowa.wypiszWszystkichUzytkownikow();
    ksiazkaAdresowa.wyswietlWszystkichAdresatow();
    ksiazkaAdresowa.dodajAdresata();
    ksiazkaAdresowa.wyswietlWszystkichAdresatow();
    ksiazkaAdresowa.wylogowanieUzytkownika();

    return 0;
}


//Testy klasy AdresatMenadzer

#include "AdresatMenadzer.h"

using namespace std;

int TestyAdresatMenadzer_main()
{
    AdresatMenadzer adresatMenadzer("Adresaci.txt",3);
    adresatMenadzer.wyswietlWszystkichAdresatow();
    adresatMenadzer.dodajAdresata();
    adresatMenadzer.wyswietlWszystkichAdresatow();

    return 0;
}

//Testy klasy PlikZAdresatami

#include "Adresat.h"
#include "PlikZAdresatami.h"

int TestyPlikZAdresatami_main()
{
    PlikZAdresatami plikZAdresatami("Adresaci-test.txt");
    Adresat adresat(8,1, "Michal", "Nowak","6543 543 654", "jtrdds@wp.pl", "ul. Gleboka 19, m. 56, Lodz 95-345");
    plikZAdresatami.dopiszAdresataDoPliku(adresat);
    plikZAdresatami.pobierzAdresatowZalogowanegoUzytkownikaZPliku(1);
    cout<<plikZAdresatami.pobierzIdOstatniegoAdresata();

    return 0;
}
