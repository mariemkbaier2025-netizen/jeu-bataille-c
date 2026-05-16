#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "jeu.h"
#include "file.h"
#include "pile.h"


//VARIABLES GLOBALES

// Files des deux joueurs (leurs mains)
File j1 = {NULL, NULL, 0};
File j2 = {NULL, NULL, 0};

// Paquet initial de cartes
Carte *paquetInitial = NULL;

// Indique si une partie a déjà été jouée
int partieDejaJouee = 0;


//PROTOTYPES
void afficherRegles();
void voirGagnant();
void lancerPartie();
void quitter();


//MAIN
int main() {

// initialisation du générateur aléatoire (shuffle) - version 2    srand(time(NULL));

    int choix;

    do {
        system("cls"); // nettoyer écran

        // Titre du jeu
        setColor(10);
      printf("    \t==============================================\n");
       printf("           \t=== JEU DE LA BATAILLE ===\n");
       printf("   \t==============================================\n");
      setColor(11);

       printf("\n \t************** LET'S GOOOOO to enjoy the game !!! \n");
       printf("   \t************** BY MERIEM KBAIER **************\n");
       printf("\n \t************** LET'S GOOOOO!!!! **************\n");
       printf("   \t************** BY MERIEM ET FATMA **************\n");
        setColor(9);
       printf(" \n\t=================== MENU =====================\n");
       printf("   \t==============================================\n");
        printf("  \t1. Lancer une nouvelle partie pour jouer\n");
        printf("  \t2. Afficher les regles du jeu\n");
         printf(" \t3. Voir le gagnant du dernier jeu\n");
          printf(" \t0. Quitter le programme by by \n");
      printf(" \t==============================================\n");
      printf(" \t==============================================\n");
        printf("   \tChoix : ");

        //lecture sécurisée utilisateur
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n'); //vider buffer
            continue;
        }
        //nettoyage du buffer après scanf
        while (getchar() != '\n');
        //gestion du menu
        switch (choix) {
            case 1: lancerPartie(); break;
            case 2: afficherRegles(); break;
            case 3: voirGagnant(); break;
            case 0: quitter(); break;
            default:
                printf("\nChoix invalide !\n");
                Sleep(800);
        }
    } while (choix != 0);
    return 0;
}

//LANCER UNE PARTIE
void lancerPartie() {
    // vider anciennes mains
    liberer_file(&j1);
    liberer_file(&j2);
    paquetInitial = NULL;
    // création du paquet
    initialiserPaquet(&paquetInitial);
    //mélange
    melangerPaquet(&paquetInitial);
    //distribution aux joueurs
    distribuerCartes(&paquetInitial, &j1, &j2);
    int tour = 1;
    //boucle de jeu
    while (j1.taille > 0 && j2.taille > 0 && tour <= 50) {
        system("cls");
        setColor(11);
        printf("--- TOUR %d ---\n", tour++);
        setColor(14);
        printf("Scores: J1 [%d] | J2 [%d]\n\n", j1.taille, j2.taille);
        //jouer un tour
        jouerTour(&j1, &j2);
        setColor(10);
        printf("\n=======================================\n");
        printf("     \tAppuyez sur Entrer...");
        printf("\n=======================================\n");

        setColor(7);
        //pause utilisateur
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    //partie terminée
    partieDejaJouee = 1;
    //afficher résultat
    voirGagnant();
}


//AFFICHER GAGNANT
void voirGagnant() {
    system("cls");
    //si aucune partie jouée
    if (!partieDejaJouee) {
        setColor(12);
    printf("\nAucune partie n'a encore ete jouee.\n");
    }
    else {
        setColor(14);
        printf("\n==============================================\n");
        printf("               RESULTAT FINAL                 \n");
        printf("==============================================\n");
        //comparaison des tailles des files
        if (j1.taille > j2.taille)
            printf("GAGNANT : JOUEUR 1 (%d cartes)\n", j1.taille);
        else if (j2.taille > j1.taille)
        printf("GAGNANT : JOUEUR 2 (%d cartes)\n", j2.taille);
        else
        printf("MATCH NUL ! (%d - %d)\n", j1.taille, j2.taille);
        printf("==============================================\n");
    }
    setColor(7);
    printf("\nAppuyez sur Entree pour continuer...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}
void afficherRegles() {
    system("cls");
    setColor(14);

    printf("\n==========================================================\n");
    printf("                  REGLES DU JEU : LA BATAILLE             \n");
    printf("==========================================================\n");
    printf("1. Le paquet de 52 cartes est distribue equitablement.\n");
    printf("2. Chaque joueur tire la carte du dessus de sa FILE.\n");
    printf("3. La carte la plus forte remporte le pli.\n");
    printf("4. En cas d'egalite (BATAILLE) :\n");
    printf("   - Utilisation d'une PILE au centre.\n");
    printf("   - Cartes face cachee + face visible.\n");
    printf("   - Le gagnant prend tout le tas.\n");
    printf("5. Fin du jeu : un joueur n'a plus de cartes.\n");
    printf("==========================================================\n");
    printf("\nAppuyez sur Entree...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}


void quitter() {
    system("cls");
    setColor(12);
    //libération mémoire avant sortie
    liberer_file(&j1);
    liberer_file(&j2);
    printf("\n==============================================\n");
    printf("          Au revoir Meriem et Fatma !           \n");
    printf("==============================================\n");
    printf("  Merci d'avoir joue a notre jeu ! A bientot.  \n");
    Sleep(1500);
    exit(0);
}
