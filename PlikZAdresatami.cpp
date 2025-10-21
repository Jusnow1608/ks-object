#include "PlikZAdresatami.h"
#include "Adresat.h"
#include "AdresatMenadzer.h"
#include "PlikTekstowy.h"

bool PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);
    if (dopiszDaneDoPliku(liniaZDanymiAdresata))
    {
        idOstatniegoAdresata = adresat.pobierzId();
        return true;
    }
    return false;
}

string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwersjaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwersjaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}

vector <Adresat> PlikZAdresatami::pobierzAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    fstream plikTekstowy;
    vector <Adresat> adresaci;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    plikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);//otwarcie pliku w trybie do odczytu

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            Adresat adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
            if(adresat.pobierzIdUzytkownika() == idZalogowanegoUzytkownika)
                adresaci.push_back(adresat);
        }
        plikTekstowy.close();
    }
    return adresaci;
}

Adresat PlikZAdresatami::pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int IloscZnakowWLinii = daneAdresataOddzielonePionowymiKreskami.length();
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < IloscZnakowWLinii; pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.ustawId (atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 2:
                adresat.ustawIdUzytkownika (atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 3:
                adresat.ustawImie (pojedynczaDanaAdresata);
                break;
            case 4:
                adresat.ustawNazwisko (pojedynczaDanaAdresata);
                break;
            case 5:
                adresat.ustawNumerTelefonu (pojedynczaDanaAdresata);
                break;
            case 6:
                adresat.ustawEmail (pojedynczaDanaAdresata);
                break;
            case 7:
                adresat.ustawAdres (pojedynczaDanaAdresata);
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

int PlikZAdresatami::pobierzIdOstatniegoAdresata()
{
    return idOstatniegoAdresata;
}

void PlikZAdresatami::usunAdresataZPliku(int idUsuwanegoAdresata)
{
    fstream odczytywanyPlikTekstowy, tymczasowyPlikTekstowy;
    string wczytanaLinia = "";
    bool czyToPierwszaZapisanaLinia = true;
    bool czyAdresatZostalUsuniety = false;

    odczytywanyPlikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);
    tymczasowyPlikTekstowy.open(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI.c_str(), ios::out);

    if (odczytywanyPlikTekstowy.good() == true && idUsuwanegoAdresata != 0)
    {
        while (getline(odczytywanyPlikTekstowy, wczytanaLinia))
        {
            int idOdczytanegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(wczytanaLinia);
            if(idOdczytanegoAdresata != idUsuwanegoAdresata)
            {
                zapiszLinieDoPliku(tymczasowyPlikTekstowy, wczytanaLinia, czyToPierwszaZapisanaLinia);
            }
            else
                czyAdresatZostalUsuniety = true;
        }

        odczytywanyPlikTekstowy.close();
        tymczasowyPlikTekstowy.close();

        if (czyAdresatZostalUsuniety == true)
        {
            usunPlik(pobierzNazwePliku());
            zmienNazwePliku(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI, pobierzNazwePliku());
            idOstatniegoAdresata = podajIdOstatniegoAdresataPoUsunieciuWybranegoAdresata(idUsuwanegoAdresata, idOstatniegoAdresata);
        }
        else
        {
            usunPlik(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI);
        }
    }
}

void PlikZAdresatami::edytujAdresataWPliku(Adresat adresat)
{
    fstream odczytywanyPlikTekstowy, tymczasowyPlikTekstowy;
    string wczytanaLinia = "";
    bool czyToPierwszaZapisanaLinia = true;
    bool czyAdresatZostalZedytowany = false;

    odczytywanyPlikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);
    tymczasowyPlikTekstowy.open(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI.c_str(), ios::out);

    if (odczytywanyPlikTekstowy.good() == true && adresat.pobierzId() != 0)
    {
        while (getline(odczytywanyPlikTekstowy, wczytanaLinia))
        {
            int idOdczytanegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(wczytanaLinia);
            if(idOdczytanegoAdresata != adresat.pobierzId())
            {
                zapiszLinieDoPliku(tymczasowyPlikTekstowy, wczytanaLinia, czyToPierwszaZapisanaLinia);
            }
            else
            {
                string nowaLinia = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);
                zapiszLinieDoPliku(tymczasowyPlikTekstowy, nowaLinia, czyToPierwszaZapisanaLinia);
                czyAdresatZostalZedytowany = true;
            }
        }
        odczytywanyPlikTekstowy.close();
        tymczasowyPlikTekstowy.close();

        if (czyAdresatZostalZedytowany == true)
        {
            usunPlik(pobierzNazwePliku());
            zmienNazwePliku(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI, pobierzNazwePliku());
        }
        else
        {
            usunPlik(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI);
        }
    }
}

void PlikZAdresatami::usunPlik(string nazwaPlikuZRozszerzeniem)
{
    if (remove(nazwaPlikuZRozszerzeniem.c_str()) == 0) {}//plik usuniety pomyslnie
    else
        cout << "Nie udalo sie usunac pliku " << nazwaPlikuZRozszerzeniem << endl;
}

void PlikZAdresatami::zmienNazwePliku(string staraNazwa, string nowaNazwa)
{
    if (rename(staraNazwa.c_str(), nowaNazwa.c_str()) == 0) {}////nazwa zmieniona pomyslnie
    else
        cout << "Nazwa pliku "<< staraNazwa << " nie zostala zmieniona." << endl;
}

int PlikZAdresatami::pobierzZPlikuIdOstatniegoAdresata()
{
    string daneAdresataOddzielonePionowymiKreskami = "";
    string ostatniaLinia = "";

    fstream plikTekstowy;
    plikTekstowy.open(pobierzNazwePliku().c_str(), ios::in);

    if (plikTekstowy.is_open())
    {
        while (getline(plikTekstowy, daneAdresataOddzielonePionowymiKreskami))
        {
            ostatniaLinia = daneAdresataOddzielonePionowymiKreskami;
        }
        plikTekstowy.close();
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    if (ostatniaLinia != "")
    {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(ostatniaLinia);
    }
    else
    {
        cout << "Plik jest pusty — brak adresatów." << endl;
        return 0;
    }
    return idOstatniegoAdresata;
}

int PlikZAdresatami::pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}

int PlikZAdresatami::podajIdOstatniegoAdresataPoUsunieciuWybranegoAdresata(int idUsuwanegoAdresata, int idOstatniegoAdresata)
{
    if (idUsuwanegoAdresata == idOstatniegoAdresata)
        return pobierzZPlikuIdOstatniegoAdresata();
    else
        return idOstatniegoAdresata;
}

void PlikZAdresatami::zapiszLinieDoPliku(fstream& plik, const string& linia, bool& czyToPierwszaZapisanaLinia)
{
    if (czyToPierwszaZapisanaLinia)
    {
        plik << linia;
        czyToPierwszaZapisanaLinia = false;
    }
    else
    {
        plik << endl << linia;
    }
}
