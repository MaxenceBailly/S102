#include <iostream>
#include <string>

#include "Tuile.h"

using namespace std;

Tuile::Tuile(const string& nom, int texturex, int texturey, const string& propriete){
    _nom=nom;
    _texturex=texturex;
    _texturey=texturey;
    _propriete=propriete;
}

void Tuile::afficher() const{
    cout << "nom: " << _nom << " texture x: " << _texturex << " texture y: " << _texturey << " propriete: " << _propriete << endl;
}

string Tuile::getNom() const{
    return _nom;
}

int Tuile::getTexturex() const{
    return _texturex;
}

int Tuile::getTexturey() const{
    return _texturey;
}

string Tuile::getPropriete() const{
    return _propriete;
}
