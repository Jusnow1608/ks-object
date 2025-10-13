#include <iostream>
#include "KsiazkaAdresowa.h"

using namespace std;

int main()
{
    KsiazkaAdresowa ksiazkaAdresowa("Uzytkownicy.txt", "Adresaci.txt");
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
            /* case '2':
                wyszukajAdresatowPoImieniu(adresaci);
                 break;
             case '3':
                 wyszukajAdresatowPoNazwisku(adresaci);
                 break;*/
            case '4':
                ksiazkaAdresowa.wyswietlWszystkichAdresatow();
                break;
            /*case '5':
                idUsunietegoAdresata = usunAdresata(adresaci);
                idOstatniegoAdresata = podajIdOstatniegoAdresataPoUsunieciuWybranegoAdresata(idUsunietegoAdresata, idOstatniegoAdresata);
                break;
            case '6':
               // edytujAdresata(adresaci);
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
