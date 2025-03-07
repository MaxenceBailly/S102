#ifndef TUILE_H_INCLUDED
#define TUILE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Tuile{
    string _nom;
    int _texturex, _texturey;
    string _propriete;

public:
    Tuile(const string& nom, int texturex, int texturey, const string& propriete);

    void afficher() const;

    string getNom() const;
    int getTexturex() const;
    int getTexturey() const;
    string getPropriete() const;
};

#endif // TUILE_H_INCLUDED
