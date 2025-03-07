#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED

#include <vector>
#include <fstream>
#include <string>

#include "Moteur.h"
#include "Objet.h"
#include "Image.h"
#include "Dictionnaire.h"

using namespace std;

class Niveau{
    vector<Objet> _objets;
    Image _objetsTextures;
    int _nbBonus=0;

public:

    Niveau();

    Niveau(const string&, const Image&, const Dictionnaire& dictionnaire);

    void metAJour() const;

    void miseEnPlaceGrille() const;

    void dessiner() const;

    vector<Objet> getObjets() const;

    void testerBonusEtPrendre(int, int);

    bool gagne() const;
};

#endif // NIVEAU_H_INCLUDED
