#include <stdlib.h>
#include "file.h"

//ajoute une carte à la fin de la file (enqueue)
void enfiler(File *f, Carte *c) {
    if (!c) return; //si la carte est NULL, on ne fait rien

    c->suivant = NULL;//la nouvelle carte devient la dernière

    if (f->queue == NULL) {
        //file vide
        f->tete = f->queue = c;
    } else {
        //file non vide
        f->queue->suivant = c; //ancien dernier pointe vers nouveau
        f->queue = c;//mise à jour de la queue
    }

    f->taille++;//augmentation de la taille
}


//Retire la première carte de la file (dequeue)
Carte* defiler(File *f) {
    if (f->tete == NULL) return NULL;// file vide

    Carte *temp = f->tete;//sauvegarde de l’élément à retirer
    f->tete = f->tete->suivant;//avance la tête

    if (f->tete == NULL)
        f->queue = NULL;//si la file devient vide

    f->taille--;

    temp->suivant = NULL;//coupe le lien proprement
    return temp;//retourne la carte retirée
}


//Vérifie si la file est vide
int file_vide(File *f) {
    return (f->taille == 0);
}


//Retourne la taille de la file
int taille_file(File *f) {
    return f->taille;
}


//Libère toute la mémoire de la file
void liberer_file(File *f) {
    while (f->tete) {
        free(defiler(f));
    }
}
