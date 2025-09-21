#ifndef ADRESATMENADZER_H
#define ADRESATMENADZER_H

#include <iostream>
#include <vector>

#include "Adresat.h"
#include "PlikZAdresatami.h"
#include "MetodyPomocnicze.h"

using namespace std;

class AdresatMenadzer
{
    int idZalogowanegoUzytkownika;
    vector <Adresat> adresaci;
    PlikZAdresatami plikZAdresatami;
    int idOstatniegoAdresata;

    Adresat podajDaneNowegoAdresata(int idOstatniegoAdresata);

    public:
    AdresatMenadzer(string nazwaPlikuZAdresatami): plikZAdresatami(nazwaPlikuZAdresatami)
    {
    idOstatniegoAdresata = plikZAdresatami.pobierzIdOstatniegoAdresata();
    }
    void dodajAdresata();
    void pobierzAdresatowZalogowanegoUzytkownikaZPliku();
    void ustawIdZalogowanegoUzytkownika(int noweIdZalogowanegoUzytkownika);
    void wypiszWszystkichAdresatow();

};

#endif
