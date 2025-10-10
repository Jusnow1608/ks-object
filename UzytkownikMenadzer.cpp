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
    for (size_t i=0; i<uzytkownicy.size(); i++)
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
    for (size_t i=0; i<uzytkownicy.size(); i++)
    {
        cout<<uzytkownicy[i].pobierzId()<<endl;
        cout<<uzytkownicy[i].pobierzLogin()<<endl;
        cout<<uzytkownicy[i].pobierzHaslo()<<endl;
    }
    system ("pause");
}

void UzytkownikMenadzer::logowanieUzytkownika()
{
    cout << "             >>> LOGOWANIE <<<" << endl;
    cout << "-----------------------------------------------" << endl;
    string login = "", haslo = "";
    cout << "Podaj login: ";
    cin>>login;
    for (size_t i=0; i<uzytkownicy.size(); i++)
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
    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;
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
