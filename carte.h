#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED



//structure représentant une carte unique
typedef struct Carte {
    int valeur;//De 2 à 14 (As = 14)
    char couleur[10];//Coeur, Carreau, Trefle, Pique
    struct Carte *suivant; //pointeur pour le chaînage dynamique
} Carte;

//structure File pour la main des joueurs (FIFO)
typedef struct {
    Carte *tete;  //sortie des cartes (on joue la carte du dessus)
    Carte *queue;  //sntrée des cartes (on ajoute les gains en bas)
    int taille;//nombre de cartes dans la main
} File;

// Structure Pile pour la zone de bataille (LIFO)
typedef struct {
    Carte *sommet; //sommet de la pile
    int taille;//nombre de cartes sur la table
} Pile;


#endif // CARTE_H_INCLUDED
