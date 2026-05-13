#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "carte.h"

//Ajouter une carte à la file (enqueue)
void enfiler(File *f, Carte *c);
//Retirer la première carte de la file (de queue)
Carte* defiler(File *f);
//vérifier si la file est vide
//retourne 1 si vide,0 sinon
int file_vide(File *f);
//calculer la taille (nombre d'éléments) de la file
int taille_file(File *f);
//Libérer toute la mémoire utilisée par la file
void liberer_file(File *f);
#endif
