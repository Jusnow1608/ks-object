#include "UzytkownikMenadzer.h"

void UzytkownikMenadzer::rejestracjaUzytkownika()
{
    Uzytkownik uzytkownik = podajDaneNowegoUzytkownika();

    uzytkownicy.push_back(uzytkownik);
    plikZUzytkownikami.dopiszUzytkownikaDoPliku(uzytkownik);

    cout << endl << "Konto zalozono pomyslnie" << endl << endl;
    system("pause");
}

Uzytkownik UzytkownikMenadzer::podajDaneNowegoUzytkownika()
{
    Uzytkownik uzytkownik;

    uzytkownik.ustawId(pobierzIdNowegoUzytkownika());
    string login;

    do
    {
        cout << "Podaj login: ";
        cin>>login;
        uzytkownik.ustawLogin(login);
    }
    while (czyIstniejeLogin(uzytkownik.pobierzLogin()) == true);

    string haslo;
    cout << "Podaj haslo: ";
    cin>>haslo;
    uzytkownik.ustawHaslo(haslo);

    return uzytkownik;
}

int UzytkownikMenadzer::pobierzIdNowegoUzytkownika()
{
    if (uzytkownicy.empty() == true)
        return 1;
    else
        return uzytkownicy.back().pobierzId() + 1;
}

bool UzytkownikMenadzer::czyIstniejeLogin(string login)
{
    int liczbaUzytkownikow = uzytkownicy.size();
    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].pobierzLogin()==login)
        {
            cout << endl << "Istnieje uzytkownik o takim loginie." << endl;
            return true;
        }

    }
    return false;
}

void UzytkownikMenadzer::wypiszWszystkichUzytkownikow()
{
    int liczbaUzytkownikow = uzytkownicy.size();
    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        cout<<uzytkownicy[i].pobierzId()<<endl;
        cout<<uzytkownicy[i].pobierzLogin()<<endl;
        cout<<uzytkownicy[i].pobierzHaslo()<<endl;
    }
}

void UzytkownikMenadzer::wczytajUzytkownikowZPliku()
{
    uzytkownicy = plikZUzytkownikami.wczytajUzytkownikowZPliku();
}

void UzytkownikMenadzer::logowanieUzytkownika()
{
    string login = "", haslo = "";
    cout << "Podaj login: ";
    cin>>login;
    int liczbaUzytkownikow = uzytkownicy.size();
    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].pobierzLogin()==login)
        {
            for (int iloscProb = 3; iloscProb > 0; iloscProb--)
            {
                cout << "Podaj haslo. Pozostalo prob: " << iloscProb << ": ";
                cin>>haslo;

                if(uzytkownicy[i].pobierzHaslo()==haslo)
                {
                    idZalogowanegoUzytkownika = uzytkownicy[i].pobierzId();
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    return ;
                }
            }
            cout << "Wprowadzono 3 razy bledne haslo." << endl;
            system("pause");
            return ;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl << endl;
    system("pause");
}

/*bool UzytkownikMenadzer::czyUzytkownikZalogowany(string login, string haslo)
{
    int liczbaUzytkownikow = uzytkownicy.size();
    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].pobierzLogin()==login && uzytkownicy[i].pobierzHaslo()==haslo)
        {
            return true;
        }
    }
    return false;
}*/

/*int UzytkownikMenadzer::pobierzIdZalogowanegoUzytkownika(string login)
{
    int liczbaUzytkownikow = uzytkownicy.size();
    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].pobierzLogin()==login)
        {
            return uzytkownicy[i].pobierzId();
        }
    }
    return 0;
}*/

void UzytkownikMenadzer::zmianaHaslaZalogowanegoUzytkownika()
{
    if (idZalogowanegoUzytkownika == 0)
    {
        cout<<"Brak zalogowanego uzytkownika."<<endl;
        system("pause");
        return;
    }
    string noweHaslo = "";
    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;
    int liczbaUzytkownikow = uzytkownicy.size();
    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].pobierzId()==idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].ustawHaslo(noweHaslo);
            cout << "Haslo zostalo zmienione." << endl << endl;
            system("pause");
            break;
        }
    }
    plikZUzytkownikami.zapiszWszystkichUzytkownikowDoPliku(uzytkownicy);
}

int UzytkownikMenadzer::pobierzIdZalogowanegoUzytkownika()
{
    return idZalogowanegoUzytkownika;
}
