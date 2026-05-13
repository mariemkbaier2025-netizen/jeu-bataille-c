// Librairies standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//Modules du projet
#include "jeu.h"
#include "file.h"
#include "pile.h"


//Changer la couleur du texte dans la console Windows
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


//Créer et initialiser un paquet de 52 cartes
void initialiserPaquet(Carte **paquet) {
    char *couleurs[] = {"Coeur", "Pique", "Carreau", "Trefle"};

    *paquet = NULL;

    for (int i = 0; i < 4; i++) {          //4 couleurs
        for (int v = 2; v <= 14; v++) {    //valeurs

            Carte *n = (Carte*)malloc(sizeof(Carte));

            strcpy(n->couleur, couleurs[i]);
            n->valeur = v;

            //insertion en tête (stack-like construction)
            n->suivant = *paquet;
            *paquet = n;
        }
    }
}


//Mélanger le paquet en échangeant des cartes aléatoires
void melangerPaquet(Carte **paquet) {
    for (int i = 0; i < 50; i++) {

        int p1 = rand() % 52;
        int p2 = rand() % 52;

        Carte *c1 = *paquet;
        Carte *c2 = *paquet;

        //avancer jusqu'aux positions p1 et p2
        for (int j = 0; j < p1; j++)
            if (c1->suivant) c1 = c1->suivant;

        for (int j = 0; j < p2; j++)
            if (c2->suivant) c2 = c2->suivant;

        //swap des valeurs + couleurs
        int tV = c1->valeur;
        char tC[10];
        strcpy(tC, c1->couleur);

        c1->valeur = c2->valeur;
        strcpy(c1->couleur, c2->couleur);

        c2->valeur = tV;
        strcpy(c2->couleur, tC);
    }
}


//Distribuer les cartes entre 2 joueurs (files)
void distribuerCartes(Carte **paquet, File *j1, File *j2) {
    int i = 0;
    Carte *curr = *paquet;

    while (curr) {
        Carte *suivant = curr->suivant;

        if (i % 2 == 0)
            enfiler(j1, curr);
        else
            enfiler(j2, curr);

        curr = suivant;
        i++;
    }

    *paquet = NULL;
}


//Jouer un tour de jeu (bataille)
void jouerTour(File *j1, File *j2) {

    //pile centrale (cartes jouées)
    Pile table = {NULL, 0};

    //tirer une carte de chaque joueur
    Carte *c1 = defiler(j1);
    Carte *c2 = defiler(j2);

    //sécurité fin de jeu
    if (!c1 || !c2) {
        printf("Un joueur n'a plus de cartes !\n");
        return;
    }

    //poser sur la table
    empiler(&table, c1);
    empiler(&table, c2);

    //affichage
    setColor(9);
    printf("J1 joue: %d-%s", c1->valeur, c1->couleur);

    setColor(7);
    printf(" vs ");

    setColor(12);
    printf("J2 joue: %d-%s\n", c2->valeur, c2->couleur);


    //CAS BATAILLE(égalité)
    while (c1->valeur == c2->valeur) {

        setColor(14);
        printf("\n=======================================\n");
        printf("        \t BATAILLE ");
        printf("\n=======================================\n");

        setColor(7);

        //vérification sécurité (pas assez de cartes)
        if (j1->taille < 2) {
            printf("Joueur 2 gagne (J1 bloque)\n");
            vider_dans_file(&table, j2);
            return;
        }

        if (j2->taille < 2) {
            printf("Joueur 1 gagne (J2 bloque)\n");
            vider_dans_file(&table, j1);
            return;
        }

        //cartes face cachée + nouvelle carte
        empiler(&table, defiler(j1));
        empiler(&table, defiler(j2));

        c1 = defiler(j1);
        c2 = defiler(j2);

        empiler(&table, c1);
        empiler(&table, c2);

        printf("Bataille: J1(%d) vs J2(%d)\n", c1->valeur, c2->valeur);
    }


    //déterminer le gagnant du pli
    if (c1->valeur > c2->valeur) {
        setColor(10);
        printf("-> Joueur 1 gagne le pli !\n");
        vider_dans_file(&table, j1);
    } else {
        setColor(11);
        printf("-> Joueur 2 gagne le pli !\n");
        vider_dans_file(&table, j2);
    }

    setColor(7);
}
