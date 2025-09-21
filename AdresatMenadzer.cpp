#include "AdresatMenadzer.h"
#include "MetodyPomocnicze.h"


void AdresatMenadzer::ustawIdZalogowanegoUzytkownika(int noweIdZalogowanegoUzytkownika)
{
    if(noweIdZalogowanegoUzytkownika >= 0)
        idZalogowanegoUzytkownika = noweIdZalogowanegoUzytkownika;
}

void AdresatMenadzer::dodajAdresata()
{
    Adresat adresat;

    system("cls");
    cout << " >>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;
    adresat = podajDaneNowegoAdresata(idOstatniegoAdresata);

    adresaci.push_back(adresat);
    plikZAdresatami.dopiszAdresataDoPliku(adresat);

    idOstatniegoAdresata++;
}

Adresat AdresatMenadzer::podajDaneNowegoAdresata(int idOstatniegoAdresata)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;

    adresat.ustawId (++idOstatniegoAdresata);

    adresat.ustawIdUzytkownika(idZalogowanegoUzytkownika);

    cout << "Podaj imie: ";
    cin>>imie;
    imie= MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);
    adresat.ustawImie(imie);

    cout << "Podaj nazwisko: ";
    cin>>nazwisko;
    nazwisko = MetodyPomocnicze::zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwisko);
    adresat.ustawNazwisko (nazwisko);

    cout << "Podaj numer telefonu: ";
    cin>>numerTelefonu;
    adresat.ustawNumerTelefonu (numerTelefonu);

    cout << "Podaj email: ";
    cin>>email;
    adresat.ustawEmail (email);

    cout << "Podaj adres: ";
    cin>>adres;
    adresat.ustawAdres (adres);

    return adresat;
}

void AdresatMenadzer::pobierzAdresatowZalogowanegoUzytkownikaZPliku()
{
    adresaci = plikZAdresatami.pobierzAdresatowZalogowanegoUzytkownikaZPliku();
}


void AdresatMenadzer::wypiszWszystkichAdresatow()
{
    int liczbaAdresatow = adresaci.size();
    for (int i=0; i<liczbaAdresatow; i++)
    {
        cout<<adresaci[i].pobierzId()<<endl;
        cout<<adresaci[i].pobierzIdUzytkownika()<<endl;
        cout<<adresaci[i].pobierzImie()<<endl;
        cout<<adresaci[i].pobierzNazwisko()<<endl;
        cout<<adresaci[i].pobierzNumerTelefonu()<<endl;
        cout<<adresaci[i].pobierzEmail()<<endl;
        cout<<adresaci[i].pobierzAdres()<<endl;
    }
}
