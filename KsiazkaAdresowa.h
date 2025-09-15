#ifndef KSIAZKAADRESOWA_H
#define KSIAZKAADRESOWA_H

#include <iostream>

#include "UzytkownikMenadzer.h"

using namespace std;

class KsiazkaAdresowa
{
UzytkownikMenadzer uzytkownikMenadzer;

public:
KsiazkaAdresowa();
void rejestracjaUzytkownika();
void wypiszWszystkichUzytkownikow();
};

#endif
