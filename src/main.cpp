#include <vector>
#include <iostream>

#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"
#include "Dictionnaire.h"
#include "Niveau.h"

using namespace std;

int main(int, char**) // Version special du main, ne pas modifier
{
  // Initialisation du jeu
  Moteur moteur("Eht Dnegel fo Adlez");

  // TODO: charger images, creer personnages, etc.
  Image fond, personnageImage, gameOver, bravo, textures;
  try {
      personnageImage = Image(moteur, "assets/personnages.png");
      gameOver = Image(moteur, "assets/gameover.png");
      bravo = Image(moteur, "assets/bravo.png");
      textures = Image(moteur, "assets/objets.png");
  }
  catch (invalid_argument& e){
    cout << "Impossible de charger l'image, " << e.what() << endl;
  }


  Dictionnaire dico("assets/dictionnaire.txt");
  dico.afficher();

  Niveau niveau1("assets/niveau1.txt", textures, dico);

  Personnage kinl(1*TAILLE_CASE, 2*TAILLE_CASE, 16, 16, 2, 2, personnageImage, niveau1);
  Personnage ennemi1(5*TAILLE_CASE, 2*TAILLE_CASE, 16, 16, 1, 5, personnageImage, niveau1);
  Personnage ennemi2(TAILLE_CASE, 5*TAILLE_CASE, 16, 16, 3, 6, personnageImage, niveau1);

  bool quitter = false, gagne = false, perdu = false , updateMove=false;

  // Boucle de jeu, appelee a chaque fois que l'ecran doit etre mis a jour
  // (en general, 60 fois par seconde)
  while (!quitter)
  {
    // I. Gestion des evenements
    Evenement evenement = moteur.evenementRecu();
    while (evenement != AUCUN)
    {
      switch (evenement)
      {
        case QUITTER_APPUYE:
          quitter = true;
          break;
        case ESPACE_APPUYE:
          break;
        case ESPACE_RELACHE:
          break;
        case GAUCHE_APPUYE:
          kinl.allerGauche();
          updateMove=true;
          break;
        case DROITE_APPUYE:
          kinl.allerDroite();
          updateMove=true;
          break;
        case HAUT_APPUYE:
          kinl.allerHaut();
          updateMove=true;
          break;
        case BAS_APPUYE:
          kinl.allerBas();
          updateMove=true;
          break;
        // TODO: gerer les autres evenements
        default:
        break;
      }
      evenement = moteur.evenementRecu();
    }

    ///Mettre à jour les annimations de kinl que lorsque que l'on appuie sur une touche de déplacement
    if(!updateMove)
        kinl.selectSprite();

    ///Mise à jour des personnages ainsi que la gestion des ia
    if(moteur.animationsAmettreAjour()){
        kinl.animationsAmettreAjour(updateMove);
        ennemi1.animationsAmettreAjour(true);
        ennemi2.animationsAmettreAjour(true);
        ennemi1.ia_parapazi(kinl);
        ennemi2.ia_verticale();
        updateMove=false;
    }

    ///Verification collisions ennemis
    vector<Personnage> ennemis = {ennemi1, ennemi2};
    perdu = kinl.toucheListe(ennemis);

    quitter=quitter||perdu||gagne;

    moteur.initialiserRendu(); ///Efface tout à l'écran (-> tout noir)

    ///Teste des bonus
    niveau1.testerBonusEtPrendre(kinl.getx(), kinl.gety());
    gagne = niveau1.gagne();

    ///Dessine tout les elements
    niveau1.dessiner();
    kinl.dessinePerso();
    ennemi1.dessinePerso();
    ennemi2.dessinePerso();

    ///Affiche l'image finale
    moteur.finaliserRendu();
  }

  ///Affichage fin
  moteur.initialiserRendu();

  if(perdu)
    gameOver.dessiner((LARGEUR_FENETRE-gameOver.getLargeur())/2,(HAUTEUR_FENETRE-gameOver.getHauteur())/2);
  else if(gagne)
    bravo.dessiner((LARGEUR_FENETRE-bravo.getLargeur())/2,(HAUTEUR_FENETRE-bravo.getHauteur())/2);

  moteur.finaliserRendu();
  moteur.attendre(3);

  return 0;
}
