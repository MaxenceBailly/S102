#include <iostream>
#include <string>

#include "Objet.h"

using namespace std;

Objet::Objet(string& id, int x, int y, const Image& image, int texturex, int texturey, string propriete, bool collision){
    cout << "Creation d'un objet de type: " << id << " texturex: " << texturex << " texturey: " << texturey << " collision: " << (collision?"oui":"non") << endl;
    _id = id;
    _coorx = x;
    _coory = y;
    _image = image;
    _texturex = texturex;
    _texturey = texturey;
    _propriete=propriete;
    _collision = collision;
    _image.selectionnerRectangle(_texturex*16, _texturey*16, 16, 16);
}

void Objet::dessiner() const{
    if(_propriete!="cache")
        _image.dessiner(_coorx*TAILLE_CASE, _coory*TAILLE_CASE);
}

void Objet::afficher() const{
    cout << "Id: " << _id << ", texture x: " << _texturex << ", texture y: " << _texturey << ", propriete: " << _propriete << ", collsion: " << (_collision?"oui":"non") << endl;
}

int Objet::getx() const{
    return _coorx;
}

int Objet::gety() const{
    return _coory;
}

string Objet::getPropriete() const{
    return _propriete;
}

bool Objet::collision() const{
    return _collision;
}

void Objet::cacher(){
    _propriete="cache";
}
