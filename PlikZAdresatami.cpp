#include "PlikZAdresatami.h"
#include "Adresat.h"
#include "AdresatMenadzer.h"

bool PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::out | ios::app);//zapis, dopisywanie na koncu

    if (plikTekstowy.good() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty() == true)
        {
            plikTekstowy << liniaZDanymiAdresata;
        }
        else
        {
            plikTekstowy << endl << liniaZDanymiAdresata;
        }
        idOstatniegoAdresata++;
        plikTekstowy.close();
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

    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);//otwarcie pliku w trybie do odczytu

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

bool PlikZAdresatami::czyPlikJestPusty()
{
    ifstream plikTekstowy;

    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);

    if (!plikTekstowy.is_open())
        return true;

    plikTekstowy.seekg(0, ios::end);
    bool pusty = (plikTekstowy.tellg() == 0);

    plikTekstowy.close();
    return pusty;
}

int PlikZAdresatami::pobierzIdOstatniegoAdresata()
{
    ifstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);

    string linia;
    int ostatnieIdAdresata = 0;

    while (getline(plikTekstowy, linia))
    {
        Adresat adresat = pobierzDaneAdresata(linia);
        if (adresat.pobierzId() > ostatnieIdAdresata)
            ostatnieIdAdresata = adresat.pobierzId();
    }

    plikTekstowy.close();
    return ostatnieIdAdresata;
}

void PlikZAdresatami::usunAdresataZPliku(int idUsuwanegoAdresata)
{
    fstream odczytywanyPlikTekstowy, tymczasowyPlikTekstowy;
    string wczytanaLinia = "";
    bool czyToPierwszaZapisanaLinia = true;
    bool czyAdresatZostalUsuniety = false;

    odczytywanyPlikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);
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
            usunPlik(NAZWA_PLIKU_Z_ADRESATAMI);
            zmienNazwePliku(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI, NAZWA_PLIKU_Z_ADRESATAMI);
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

    odczytywanyPlikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);
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
            usunPlik(NAZWA_PLIKU_Z_ADRESATAMI);
            zmienNazwePliku(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI, NAZWA_PLIKU_Z_ADRESATAMI);
        }
        else
        {
            usunPlik(NAZWA_TYMCZASOWEGO_PLIKU_Z_ADRESATAMI);
        }
    }
}

void PlikZAdresatami::usunPlik(string nazwaPlikuZRozszerzeniem)
{
    if (remove(nazwaPlikuZRozszerzeniem.c_str()) == 0) {}
    else
        cout << "Nie udalo sie usunac pliku " << nazwaPlikuZRozszerzeniem << endl;
}

void PlikZAdresatami::zmienNazwePliku(string staraNazwa, string nowaNazwa)
{
    if (rename(staraNazwa.c_str(), nowaNazwa.c_str()) == 0) {}
    else
        cout << "Nazwa pliku "<< staraNazwa << " nie zostala zmieniona." << endl;
}

int PlikZAdresatami::pobierzZPlikuIdOstatniegoAdresata()
{
    int idOstatniegoAdresata = 0;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            daneOstaniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
        }
        plikTekstowy.close();
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    if (daneOstaniegoAdresataWPliku != "")
    {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstaniegoAdresataWPliku);
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

