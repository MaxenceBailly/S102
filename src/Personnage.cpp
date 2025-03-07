#include <iostream>
#include <vector>

#include "Personnage.h"
#include "Image.h"
#include "Niveau.h"

using namespace std;

Personnage::Personnage(){
    cout << "Creation d'un personnage vide" << endl;
    _coorx=0;
    _coory=0;
    _width=16;
    _height=16;
    _speed=2;
    _skin=1;
    _sprite=Image();
}

Personnage::Personnage(int coorx, int coory, int width, int height, int speed, int skin, Image sprite, Niveau carte){
    cout << "Creation d'un personnage non vide" << endl;
    _coorx=coorx;
    _coory=coory;
    _width=width;
    _height=height;
    _speed=speed;
    _skin=skin;
    _sprite=sprite;
    _carte=carte;
    selectSprite();
}

void Personnage::dessinePerso() const{
    _sprite.dessiner(_coorx, _coory);
}

bool Personnage::allerBas(){
    _direction=BAS;
    bool canMove=_coory+_speed+_height<NB_CASE_HAUTEUR*TAILLE_CASE && !toucheListe(_carte.getObjets(), 0, _speed);
    if(canMove)
        _coory += _speed;
    else
        _coory += (((_coory+_height)/TAILLE_CASE+1)*TAILLE_CASE-(_coory+_height))==TAILLE_CASE?0:((_coory+_height)/TAILLE_CASE+1)*TAILLE_CASE-(_coory+_height);
    selectSprite();

    return canMove;
}

bool Personnage::allerHaut(){
    _direction=HAUT;
    bool canMove=_coory-_speed>0 && !toucheListe(_carte.getObjets(), 0, -_speed);
    if(canMove)
        _coory -= _speed;
    else
        _coory -= (_coory-(_coory/TAILLE_CASE)*TAILLE_CASE)==0?0:_coory-(_coory/TAILLE_CASE)*TAILLE_CASE;
    selectSprite();

    return canMove;
}

bool Personnage::allerGauche(){
    _direction=GAUCHE;
    bool canMove=_coorx-_speed>0 && !toucheListe(_carte.getObjets(), -_speed, 0);
    if(canMove)
        _coorx -= _speed;
    else
        _coorx -= (_coorx-(_coorx/TAILLE_CASE)*TAILLE_CASE)==0?0:_coorx-(_coorx/TAILLE_CASE)*TAILLE_CASE;
    selectSprite();

    return canMove;
}

bool Personnage::allerDroite(){
    _direction=DROITE;
    bool canMove=_coorx+_speed+_width<NB_CASE_LARGEUR*TAILLE_CASE && !toucheListe(_carte.getObjets(), _speed, 0);
    if(canMove)
        _coorx += _speed;
    else
        _coorx += (((_coorx+_width)/TAILLE_CASE+1)*TAILLE_CASE-(_coorx+_width))==TAILLE_CASE?0:((_coorx+_width)/TAILLE_CASE+1)*TAILLE_CASE-(_coorx+_width);
    selectSprite();

    return canMove;
}

bool Personnage::avancer(){
    bool peutAvancer;
    switch(_direction){
        case HAUT: peutAvancer=allerHaut();break;
        case BAS: peutAvancer=allerBas();break;
        case GAUCHE: peutAvancer=allerGauche();break;
        case DROITE: peutAvancer=allerDroite();break;
    }
    return peutAvancer;
}

void Personnage::ia_horizontale(){
    if(_direction!=GAUCHE&&_direction!=DROITE)
        _direction=DROITE;
    else if(!avancer())
        _direction=_direction==DROITE?GAUCHE:DROITE;
}

void Personnage::ia_verticale(){
    if(_direction!=HAUT&&_direction!=BAS)
        _direction=HAUT;
    else if(!avancer())
        _direction=_direction==HAUT?BAS:HAUT;
}

void Personnage::ia_aleatoire(){
    _direction = rand()%4;
    avancer();
}

void Personnage::ia_parapazi(const Personnage& cible){
    if(abs(_coorx-cible.getx())>abs(_coory-cible.gety())){
        if(_coorx>cible.getx())
            allerGauche();
        else
            allerDroite();
    }
    else{
        if(_coory>cible.gety())
            allerHaut();
        else
            allerBas();
    }
}

int Personnage::getx() const{
    return _coorx;
}

int Personnage::gety() const{
    return _coory;
}

int Personnage::getwidth() const{
    return _width;
}

int Personnage::getheight() const{
    return _height;
}

bool Personnage::touche(const Personnage& perso) const{
    bool collisionx = (_coorx + _width > perso.getx()) && (perso.getx() + perso.getwidth() > _coorx);
    bool collisiony = (_coory + _height > perso.gety()) && (perso.gety() + perso.getheight() > _coory);

    return collisionx && collisiony;
}

bool Personnage::touche(const Objet& element, int deplacementx, int deplacementy) const{
    bool collisionx=false, collisiony=false;
    if(element.collision()){
        collisionx = (_coorx+deplacementx+_width-1)/TAILLE_CASE>=element.getx()&&(_coorx+deplacementx)/TAILLE_CASE<=element.getx();
        collisiony = (_coory+deplacementy+_height-1)/TAILLE_CASE>=element.gety()&&(_coory+deplacementy)/TAILLE_CASE<=element.gety();
    }

    return collisionx && collisiony;
}

bool Personnage::toucheListe(const vector<Personnage>& liste) const{
    int nbElements=liste.size()-1;
    bool estTouche=false;
    while(!estTouche&&nbElements>=0){
        estTouche=touche(liste[nbElements]);
        nbElements--;
    }
    return estTouche;
}

bool Personnage::toucheListe(const vector<Objet>& liste, int deplacementx, int deplacementy) const{
    int nbElements=liste.size()-1;
    bool estTouche=false;
    while(!estTouche&&nbElements>=0){
        estTouche=touche(liste[nbElements], deplacementx, deplacementy);
        nbElements--;
    }
    return estTouche;
}

void Personnage::animationsAmettreAjour(bool mettreAJour){
    if(mettreAJour){
        if(_animDirection)
            _animFrame++;
        else
            _animFrame--;
    if(_animFrame==0||_animFrame==2)
        _animDirection=!_animDirection;
    }
    else
        _animFrame=1;
}

void Personnage::selectSprite(){
    _sprite.selectionnerRectangle((_skin%NB_SPRITE_LIGNE)*(3*SPRITE_SIZE)+SPRITE_SIZE+(_animFrame-1)*SPRITE_SIZE,_skin/NB_SPRITE_LIGNE*(4*SPRITE_SIZE)+_direction*SPRITE_SIZE,SPRITE_SIZE,SPRITE_SIZE);
}
