#include "PlikZAdresatami.h"
#include "Adresat.h"
#include "AdresatMenadzer.h"

void PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
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
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
    }
    plikTekstowy.close();
    system("pause");
}

string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
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

