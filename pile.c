#include <stdlib.h>
#include "pile.h"
#include "file.h"
#include "carte.h"
//la carte devient le nouveau sommet
void empiler(Pile *p, Carte *c) {
    if (!c) return; //sécurité

    c->suivant = p->sommet; //le nouveau pointe vers l’ancien sommet
    p->sommet = c;//mise à jour du sommet
    p->taille++;//augmentation taille
}

//Retirer la carte au sommet de la pile (pop)
Carte* depiler(Pile *p) {
    if (p->sommet == NULL) return NULL; //pile vide

    Carte *temp = p->sommet;//sauvegarde sommet
    p->sommet = p->sommet->suivant;//déplacement sommet
    p->taille--;// décrément taille

    temp->suivant = NULL;//couper lien proprement
    return temp;//retourner carte
}


//Vérifier si la pile est vide
int pile_vide(Pile *p) {
    return (p->taille == 0);
}


//Vider la pile vers une file (donner cartes au gagnant)
void vider_dans_file(Pile *p, File *f) {
    if (!p || !f) return;
    Carte *c;
    //tant qu'il y a des cartes dans la pile
    while (p->sommet != NULL) {
        c = depiler(p);//retire du sommet
        enfiler(f, c);//ajoute dans la file du joueur gagnant
    }
}
