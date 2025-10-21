#ifndef PLIKZADRESATAMI_H
#define PLIKZADRESATAMI_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Adresat.h"
#include "MetodyPomocnicze.h"
#include "PlikTekstowy.h"

using namespace std;

class PlikZAdresatami: public PlikTekstowy
{
    const string NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI;
    int idOstatniegoAdresata;

    string zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat);
    Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami);
    void usunPlik(string nazwaPlikuZRozszerzeniem);
    void zmienNazwePliku(string nazwaTymczasowegoPlikuZRozszerzeniem, string nazwaPlikuZRozszerzeniem);
    int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami);
    int podajIdOstatniegoAdresataPoUsunieciuWybranegoAdresata(int idUsuwanegoAdresata, int idOstatniegoAdresata);
    void zapiszLinieDoPliku(fstream& plik, const string& linia, bool& czyToPierwszaZapisanaLinia);

public:
    PlikZAdresatami(string nazwaPliku, string nazwaTymczasowegoPlikuZAdresatami):
    PlikTekstowy (nazwaPliku), NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI (nazwaTymczasowegoPlikuZAdresatami), idOstatniegoAdresata(pobierzZPlikuIdOstatniegoAdresata())
    {
    }
    bool dopiszAdresataDoPliku(Adresat adresat);
    vector <Adresat> pobierzAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika);
    int pobierzIdOstatniegoAdresata();
    void usunAdresataZPliku(int idUsuwanegoAdresata);
    int pobierzZPlikuIdOstatniegoAdresata();
    void edytujAdresataWPliku(Adresat adresat);
};

#endif
