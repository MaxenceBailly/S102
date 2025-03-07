#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <iostream>
#include <string>

#include "Image.h"

using namespace std;

class Element{
    string _id;
    int _coorx;
    int _coory;
    Image _image;
    int _texturex;
    int _texturey;
    bool _collision;

public:

    Element(string&, int, int, const Image&, int, int, bool);

    void dessiner() const;
    void afficher() const;

    int getx() const;
    int gety() const;

    bool collision() const;

};

#endif // ELEMENT_H_INCLUDED
