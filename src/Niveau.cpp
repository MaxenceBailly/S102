#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Niveau.h"
#include "Moteur.h"
#include "Objet.h"
#include "Dictionnaire.h"
#include "Tuile.h"

using namespace std;

Niveau::Niveau(){
    cout << "Creation d'un niveau vide" << endl;
}

Niveau::Niveau(const string& nomFichier, const Image& textures, const Dictionnaire& dictionnaire){
    cout << "Creation d'un niveau" << endl;
    _objetsTextures=textures;

    int nbLignes;
    ifstream entreeFichier;

    entreeFichier.open(nomFichier);

    int coorx, coory;
    string idTuile;

    entreeFichier >> nbLignes;
    entreeFichier.ignore();

    while(!entreeFichier.eof()){
        entreeFichier >> idTuile >> coorx >> coory;

        Tuile tuile = dictionnaire.recherche(idTuile);

        Objet objet(idTuile,
                    coorx,
                    coory,
                    _objetsTextures,
                    tuile.getTexturex(),
                    tuile.getTexturey(),
                    tuile.getPropriete(),
                    (tuile.getPropriete()=="solide"?true:false));

        objet.afficher();

        if(tuile.getPropriete()=="bonus")
            _nbBonus++;
        _objets.push_back(objet);

    }
    entreeFichier.close();
}

void Niveau::dessiner() const{
    for(int i=0;i<_objets.size();i++){
        _objets[i].dessiner();
    }
}

vector<Objet> Niveau::getObjets() const{
    return _objets;
}

void Niveau::testerBonusEtPrendre(int coorx, int coory){
    for(int i=0; i<_objets.size(); i++){
        if(_objets[i].getPropriete()=="bonus"){
            if((coorx/TAILLE_CASE==_objets[i].getx() || coorx/TAILLE_CASE+1==_objets[i].getx()) &&
               (coory/TAILLE_CASE==_objets[i].gety() || coory/TAILLE_CASE+1==_objets[i].gety())){
                _objets[i].cacher();
                _nbBonus--;}
        }
    }
}

bool Niveau::gagne() const{
    return _nbBonus<=0;
}
