#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

#include "carte.h"

//ajouter une carte au sommet de la pile (push)
void empiler(Pile *p, Carte *c);
//retirer la carte au sommet de la pile (pop)
Carte* depiler(Pile *p);
//Vérifier si la pile est vide
int pile_vide(Pile *p);
//vider toute la pile vers une file
//transfère toutes les cartes de la pile vers la file (FIFO)
void vider_dans_file(Pile *p, File *f);

#endif // PILE_H_INCLUDED
