#include "Adresat.h"


void Adresat::ustawId (int noweId)
{
   if(noweId >= 0)
    id = noweId;
}

void Adresat::ustawIdUzytkownika (int noweIdUzytkownika)
{
   if(noweIdUzytkownika >= 0)
    idUzytkownika = noweIdUzytkownika;
}

void Adresat::ustawImie (string noweImie)
{
    if(noweImie!="")
    imie = noweImie;
}

void Adresat::ustawNazwisko (string noweNazwisko)
{
    if(noweNazwisko!="")
    nazwisko=noweNazwisko;
}

void Adresat::ustawNumerTelefonu(string nowyNumerTelefonu)
{
    if(nowyNumerTelefonu!="")
    numerTelefonu = nowyNumerTelefonu;
}

void Adresat::ustawEmail (string nowyEmail)
{
    if(nowyEmail!="")
    email=nowyEmail;
}

void Adresat::ustawAdres (string nowyAdres)
{
    if(nowyAdres!="")
    adres=nowyAdres;
}

int Adresat::pobierzId()
{
return id;
}

int Adresat::pobierzIdUzytkownika()
{
return idUzytkownika;
}

string Adresat::pobierzImie()
{
    return imie;
}

string Adresat::pobierzNazwisko()
{
    return nazwisko;
}

string Adresat::pobierzNumerTelefonu()
{
    return numerTelefonu;
}

string Adresat::pobierzEmail()
{
    return email;
}

string Adresat::pobierzAdres()
{
    return adres;
}
