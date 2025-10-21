#include "PlikTekstowy.h"

bool PlikTekstowy::czyPlikJestPusty()
{
    ifstream plikTekstowy;
    plikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);

    if (!plikTekstowy.is_open())
        return true;

    plikTekstowy.seekg(0, ios::end);
    bool pusty = (plikTekstowy.tellg() == 0);

    plikTekstowy.close();
    return pusty;// true jesli plik ma 0 bajtów
}

string PlikTekstowy::pobierzNazwePliku()
{
    return NAZWA_PLIKU;
}

bool PlikTekstowy::dopiszDaneDoPliku(const string& tekst)
{
    fstream plikTekstowy;
    plikTekstowy.open(pobierzNazwePliku().c_str(), ios::out |ios::app);

    if (plikTekstowy.is_open())
    {
        plikTekstowy.seekp(0, ios::end);
        if (plikTekstowy.tellp() > 0)
            plikTekstowy << endl;

        plikTekstowy << tekst;
        plikTekstowy.close();
        return true;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku " << pobierzNazwePliku() << " i zapisac w nim danych." << endl;
    }
    plikTekstowy.close();
    return false;
}


