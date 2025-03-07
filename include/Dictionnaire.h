#ifndef DICTIONNAIRE_H_INCLUDED
#define DICTIONNAIRE_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

#include "Tuile.h"

using namespace std;

class Dictionnaire{
    vector<Tuile> _tuiles;

public:
    Dictionnaire(const string&);

    void afficher() const;

    Tuile recherche(const string&) const;
};

#endif // DICTIONNAIRE_H_INCLUDED
