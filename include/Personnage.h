#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include <vector>

#include "Image.h"
#include "Objet.h"
#include "Niveau.h"

using namespace std;

const int NB_SPRITE_LIGNE = 4;
const int NB_SPRITE_ANIM = 3;
const int SPRITE_SIZE = 16;
enum Direction {BAS, GAUCHE, DROITE, HAUT};

class Personnage{
    int _coorx; ///Coordonnée x
    int _coory; ///Coordonnée y
    int _width; ///Largeur du sprite
    int _height; ///Hauteur du sprite
    int _speed; ///Vitesse du personnage
    int _skin; ///La peau a utiliser (0=chauve, 1=garçon, 2=fille, ...)
    Image _sprite; ///Image des sprites (qui va être cropée sur une peau)
    int _direction=BAS; ///Direction
    int _animFrame=1; ///Position de l'animation
    bool _animDirection=true;
    Niveau _carte; ///Carte

public:
    ///Constructeurs
    Personnage();
    Personnage(int coorx, int coory, int width, int height, int speed, int skin, Image sprite, Niveau carte);

    void dessinePerso() const; ///Dessine le personnage (hero, ennemis, etc...)

    bool allerDroite(); ///Déplacement vers la droite
    bool allerGauche(); ///Déplacement vers la gauche
    bool allerHaut(); ///Déplacement vers le haut
    bool allerBas(); ///Déplacement vers le bas

    bool avancer(); ///Avance dans la direction courante

    void ia_verticale(); ///Une ia qui se déplace de gauche à droite
    void ia_horizontale(); ///Une ia qui se déplace de haut en bas
    void ia_aleatoire(); ///Une ia qui se déplace à chaque fois dans une direction aléatoire
    void ia_parapazi(const Personnage& cible); ///Une ia qui suis un personnage donné

    int getx() const;
    int gety() const;
    int getwidth() const;
    int getheight() const;

    bool touche(const Personnage&) const;
    bool touche(const Objet&, int, int) const;

    bool toucheListe(const vector<Personnage>&) const;
    bool toucheListe(const vector<Objet>&, int, int) const;

    void animationsAmettreAjour(bool mettreAJour);

    void selectSprite();
};

#endif // PERSONNAGE_H_INCLUDED
