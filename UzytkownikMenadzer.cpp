#include "UzytkownikMenadzer.h"

void UzytkownikMenadzer::rejestracjaUzytkownika()
{
    cout << "             >>> REJESTRACJA <<<" << endl;
    cout << "-----------------------------------------------" << endl;
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
        login = MetodyPomocnicze::wczytajLinie();
        uzytkownik.ustawLogin(login);
        if (login.empty())
            cout << "Login nie moze byc pusty." << endl;
    }
    while (czyIstniejeLogin(uzytkownik.pobierzLogin()) || login.empty());

    string haslo;
    do
    {
        cout << "Podaj haslo: ";
        haslo = MetodyPomocnicze::wczytajLinie();
        uzytkownik.ustawHaslo(haslo);
        if (haslo.empty())
            cout << "Haslo nie moze byc puste." << endl;
    }
    while(haslo.empty());

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
    for (size_t i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].pobierzLogin()==login)
        {
            cout << "Istnieje uzytkownik o takim loginie." << endl;
            return true;
        }
    }
    return false;
}

void UzytkownikMenadzer::wypiszWszystkichUzytkownikow()
{
    for (size_t i=0; i<uzytkownicy.size(); i++)
    {
        cout<<"Id:    "<<uzytkownicy[i].pobierzId()<<endl;
        cout<<"Login: "<<uzytkownicy[i].pobierzLogin()<<endl;
        cout<<"Haslo: "<<uzytkownicy[i].pobierzHaslo()<<endl;
        cout<<endl;
    }
    system ("pause");
}

void UzytkownikMenadzer::logowanieUzytkownika()
{
    cout << "             >>> LOGOWANIE <<<" << endl;
    cout << "-----------------------------------------------" << endl;
    string login = "", haslo = "";
    cout << "Podaj login: ";
    login = MetodyPomocnicze::wczytajLinie();
    for (size_t i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].pobierzLogin()==login)
        {
            for (int iloscProb = 3; iloscProb > 0; iloscProb--)
            {
                cout << "Podaj haslo. Pozostalo prob: " << iloscProb << ": ";
                haslo = MetodyPomocnicze::wczytajLinie();

                if(uzytkownicy[i].pobierzHaslo()==haslo)
                {
                    idZalogowanegoUzytkownika = uzytkownicy[i].pobierzId();
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    return;
                }
            }
            cout << "Wprowadzono 3 razy bledne haslo." << endl;
            system("pause");
            return;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl << endl;
    system("pause");
}

void UzytkownikMenadzer::zmianaHaslaZalogowanegoUzytkownika()
{
    cout << "             >>> ZMIANA HASLA <<<" << endl;
    cout << "-----------------------------------------------" << endl;
    string noweHaslo = "";
    do
    {
        cout << "Podaj nowe haslo: ";
        noweHaslo = MetodyPomocnicze::wczytajLinie();
        if (noweHaslo.empty())
            cout << "Haslo nie moze byc puste." << endl;
    }
    while (noweHaslo.empty());

    for (size_t i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].pobierzId()== idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].ustawHaslo(noweHaslo);
            break;
        }
    }
    plikZUzytkownikami.zapiszWszystkichUzytkownikowDoPliku(uzytkownicy);
    cout << "Haslo zostalo zmienione." << endl << endl;
    system("pause");
}

int UzytkownikMenadzer::pobierzIdZalogowanegoUzytkownika()
{
    return idZalogowanegoUzytkownika;
}

void UzytkownikMenadzer::wylogowanieUzytkownika()
{
    idZalogowanegoUzytkownika = 0;
    cout<<"Zostales wylogowany."<<endl;
    system("pause");
}

bool UzytkownikMenadzer::czyUzytkownikZalogowany()
{
    if (idZalogowanegoUzytkownika > 0)
        return true;
    else
        return false;
}
