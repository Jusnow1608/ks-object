#include <iostream>
#include "KsiazkaAdresowa.h"

using namespace std;

int main()
{
    KsiazkaAdresowa ksiazkaAdresowa("Uzytkownicy.txt", "Adresaci.txt", "Adresaci-tymczasowy.txt");
    char wybor;

    while (true)
    {
        if (ksiazkaAdresowa.czyUzytkownikZalogowany() == false)
        {
            wybor = ksiazkaAdresowa.wybierzOpcjeZMenuGlownego();

            switch (wybor)
            {
            case '1':
                ksiazkaAdresowa.wypiszWszystkichUzytkownikow();
                ksiazkaAdresowa.rejestracjaUzytkownika();
                break;
            case '2':
                ksiazkaAdresowa.wypiszWszystkichUzytkownikow();
                ksiazkaAdresowa.logowanieUzytkownika();
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        }
        else
        {
            wybor = ksiazkaAdresowa.wybierzOpcjeZMenuUzytkownika();

            switch (wybor)
            {
            case '1':
                ksiazkaAdresowa.wyswietlWszystkichAdresatow();
                ksiazkaAdresowa.dodajAdresata();
                break;
            case '2':
                ksiazkaAdresowa.wyszukajAdresatowPoImieniu();
                break;
            case '3':
                ksiazkaAdresowa.wyszukajAdresatowPoNazwisku();
                break;
            case '4':
                ksiazkaAdresowa.wyswietlWszystkichAdresatow();
                break;
            case '5':
                ksiazkaAdresowa.usunAdresata();
                break;
           /* case '6':
                edytujAdresata(adresaci);
                break;*/
            case '7':
                ksiazkaAdresowa.zmianaHaslaZalogowanegoUzytkownika();
                ksiazkaAdresowa.wypiszWszystkichUzytkownikow();
                break;
            case '8':
                ksiazkaAdresowa.wylogowanieUzytkownika();
                break;
            }
        }
    }
    return 0;
}


//Testy klasy AdresatMenadzer

#include "AdresatMenadzer.h"

using namespace std;

int  AdresatMenadzer_main()
{
    AdresatMenadzer adresatMenadzer("Adresaci-test.txt", "Adresaci-tymczasowy-test.txt",1);
    adresatMenadzer.wyswietlWszystkichAdresatow();
    adresatMenadzer.dodajAdresata();
    adresatMenadzer.wyswietlWszystkichAdresatow();
    //adresatMenadzer.wyszukajAdresatowPoImieniu();
    //adresatMenadzer.wyszukajAdresatowPoNazwisku();
    adresatMenadzer.usunAdresata();

    return 0;
}

//Testy klasy PlikZAdresatami

#include "Adresat.h"
#include "PlikZAdresatami.h"

int PlikZAdresatami_main()
{
    PlikZAdresatami plikZAdresatami("Adresaci-test.txt", "Adresaci-tymczasowy-test.txt");
    Adresat adresat(11,1, "Wojtek", "Kowalski","6543 543 654", "jtrdds@wp.pl", "ul. Gleboka 19, m. 56, Lodz 95-345");
    plikZAdresatami.dopiszAdresataDoPliku(adresat);
    plikZAdresatami.pobierzAdresatowZalogowanegoUzytkownikaZPliku(1);
    cout<<plikZAdresatami.pobierzIdOstatniegoAdresata()<<endl;
    plikZAdresatami.usunAdresataZPliku(10);


    return 0;
}
