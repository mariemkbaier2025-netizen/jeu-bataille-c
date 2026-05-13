#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "carte.h"

//Changer la couleur du texte dans la console
void setColor(int color);
//initialiser un paquet de cartes
void initialiserPaquet(Carte **paquet);
//Mélanger le paquet de cartes
void melangerPaquet(Carte **paquet);
//Distribuer les cartes entre deux joueurs (files)
void distribuerCartes(Carte **paquet, File *j1, File *j2);//j1 et j2 représentent les files des joueurs
//Jouer un tour du jeu
void jouerTour(File *j1, File *j2);
#endif // JEU_H_INCLUDED
