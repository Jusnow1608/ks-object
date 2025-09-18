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
    } while (czyIstniejeLogin(uzytkownik.pobierzLogin()) == true);

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
for (int i=0;i<uzytkownicy.size();i++)
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
//int rozmiar = uzytkownicy.size();
for (int i=0;i<uzytkownicy.size();i++)
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

