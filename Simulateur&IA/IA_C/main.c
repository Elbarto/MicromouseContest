#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "functions.h"
#include "ia.h"

//169.254.0.1


int main()
{

/* ############################### Initialisation variables #############################################*/
    int cases=9; //Nombres de cases du laby
    int compteur=0, i, j;



    //Listes contenant toutes les valeurs des capteurs,
    //à chaque boucle du main : à incrémenter d'une nouvelle valeur donnée par les capteurs
    Liste capteur_s=creer_liste(); //capteur straight
    Liste capteur_l=creer_liste(); //capteur left
    Liste capteur_r=creer_liste(); //capteur right
    Liste* capteurs=calloc(3, sizeof(*capteurs));
    capteurs[0] = capteur_r;
    capteurs[1] = capteur_s;
    capteurs[2] = capteur_l;


    //Alloc et init Matrice contenant la map
    CASE **map; //Matrice contenant la map à compléter
    map = alloue_map(map, cases);
    if(map == NULL) return NULL;


    //Initialisation current_case
    int *current_case; //Case sur laquelle est le robot à l'instant t
    current_case = calloc(2, sizeof(*current_case));
    current_case[0] = 0;
    current_case[1] = 0;
    affiche_current_case(current_case);

    /*Init de l'orientation du micromouse
    orientation :
    - 0 : dir en haut
    - 1 : <-
    - 2 : en bas
    - 3 : ->
    */
    int* orientation=calloc(1, sizeof(*orientation));

    *orientation = 0;

    //Init des distances parcourues
    int*  dist_l=calloc(1, sizeof(*dist_l)); //distance totale parcourue par la roue gauche
    int*  dist_r=calloc(1, sizeof(*dist_r)); //distance totale parcourue par la roue droite
    *dist_l=0;
    *dist_r=0;

    //Init dernier mouvement effectue servant a maj la current_case
    int last_move=NULL;

    //Initialisation Tableau de cases*cases listes avec les liens entre les cases pour Bellman
    Liste* tab=calloc((cases*cases), sizeof(*tab));

/* ################################### Fonctions du main ############################################*/






    // TEST DES CAPTEURS + REMPLISSAGE MAP + CREATION TAB DE LISTE POUR BELLMAN
    /*
    while(compteur<50){
        if(compteur%20>18){ //On test les capteurs tous les 20 boucles
            capteurs = mapping(capteurs, map, current_case,orientation, 50, &last_move);
            //TEST de maj current case et orientation
            //printf("orientation bef : %d\n", *orientation);
            maj_current_case(current_case, orientation, last_move);
            //affiche_current_case(current_case);
            //printf("orientation aft : %d\n", *orientation);
            //affiche_map(map);



        }

        compteur++;
        wait(0.1); //Fonction attendre XX sec
    }
    */

    //TEST BELLMAN
    /*
    tab = recuperation(map, cases, tab);
    SOMMET* tableau_bellman = calloc(cases*cases, sizeof(*tableau_bellman));;
    tableau_bellman = bellman(tableau_bellman,tab, cases*cases, 0);
    Liste chemin = creer_liste();
    chemin = chemin_bellman(tableau_bellman, 0, 10);
    affiche_chemin_bellman(chemin);
    */


    //Création d'un trou pour tester test_gagne
    /*
    for(i=2; i<4; i++){
        for(j=2; j<4; j++){
            map[i][j].bas = 0;
            map[i][j].gauche = 0;
            map[i][j].haut = 0;
            map[i][j].droite = 0;
        }
    }
    affiche_map(map);
    if(test_gagne(map, current_case)) printf("Gagne!\n");
    */




    //Création liste de valeurs de capteur et moyennage sur
    /*
    capteur_l = creer_liste();
    int nb_for_moy = 50;
    int k=0;
    for(k=0; k<100; k++){
        capteur_l = ajout_tete(k,capteur_l);
    }
    printf("Moyenne : %lf\n", moy_detect(capteur_l, nb_for_moy));*
    */






    //Utilisation d'une boucle avec tempo
    /*
    printf("\nDecompte :");
    while(1){
        printf("\n%d",(map[0][compteur]).numero);
        compteur++;
        wait(1); //Fonction attendre X sec
    }
    */



    return 0;
}
