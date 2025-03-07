#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Dictionnaire.h"
#include "Tuile.h"

using namespace std;

Dictionnaire::Dictionnaire(const string& nomFichier){
    ifstream fichier(nomFichier);
    int nbLignes;

    fichier >> nbLignes;
    fichier.ignore();

    string nom, propriete;
    int x, y;

    while(fichier >> nom >> x >> y >> propriete){
        cout << "ok" << endl;
        cout << nom << x << y << propriete << endl;
        Tuile tuile(nom, x, y, propriete);
        _tuiles.push_back(tuile);
    }
    cout << "C'est bon gars" << endl;

    fichier.close();
}

void Dictionnaire::afficher() const{
    cout << "Dictionnaire: " << endl;
    for(int i=0;i<_tuiles.size();i++){
        _tuiles[i].afficher();
    }
}

///Recherche dichotomique
Tuile Dictionnaire::recherche(const string&mot) const{
    int debut = 0, fin = _tuiles.size() - 1, trouve = -1;

    while (debut <= fin) {
        int milieu = debut + (fin - debut) / 2;

        if (_tuiles[milieu].getNom() == mot) {
            trouve = milieu;
            break;
        } else if (_tuiles[milieu].getNom() < mot) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }
    if (trouve == -1) {
        cerr << "Erreur, element non trouve : " << mot << endl;
        throw "Erreur, element non trouve";
    }
    return _tuiles[trouve];
}
