#ifndef OBJET_H_INCLUDED
#define OBJET_H_INCLUDED

#include <iostream>
#include <string>

#include "Image.h"

using namespace std;

class Objet{
    string _id;
    int _coorx;
    int _coory;
    Image _image;
    int _texturex;
    int _texturey;
    string _propriete;
    bool _collision;

public:

    Objet(string&, int, int, const Image&, int, int, string, bool);

    void dessiner() const;
    void afficher() const;

    int getx() const;
    int gety() const;
    string getPropriete() const;

    bool collision() const;

    void cacher();

};

#endif // OBJET_H_INCLUDED
