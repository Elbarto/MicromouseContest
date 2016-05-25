#include "functions.h"


//Fonction attendre step secondes
void wait(float step){
    clock_t end=clock()+(step*CLOCKS_PER_SEC); // On calcule le moment où l'attente devra s'arrêter
    while(clock()<end);
}

//Fonction alloue dynamiquement contiguement une matrice 2D n*m et Initialise les cases
int alloue_map(CASE **p, int cases){
    int i,j,k;
    p = calloc(cases, sizeof(*p));
    if (p==NULL) return NULL;
    else{
        *p = calloc(cases*cases, sizeof(**p));
        if (*p==NULL) {free(p); return NULL;}
        for(i=1; i<cases; i++){
            p[i] = p[i-1] + cases;
        }

        //Initialisation de la map
        for(j=0; j<cases; j++){
            for(k=0; k<cases; k++){
                p[j][k].bas = 1;
                p[j][k].gauche = 1;
                p[j][k].haut = 1;
                p[j][k].droite = 1;
                p[j][k].numero = j*cases+k;
            }
        }

    }
    return p;
}


//Fonction affiche la map : bas / gauche / haut / droite
void affiche_map(CASE **map){
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            printf("(%d,%d,%d,%d)  ",(map[i][j]).bas,(map[i][j]).gauche,(map[i][j]).haut,(map[i][j]).droite);
        }
        printf("\n");
    }
}

void affiche_current_case(int *current_case){
    printf("Current position i:%d j:%d\n",current_case[0], current_case[1]);
}

/*Fonction mise à jour de la current case grace à la current_case, et à la différence de distance parcourue par les moteurs droit et gauche
orientation :
    - 0 : dir en haut
    - 1 : <-
    - 2 : en bas
    - 3 : ->
*/

void maj_current_case(int* current_case, int* orientation, int last_move){


    if(last_move==0){ //Le dernier déplacement : DROITE
        current_case[0] +=  *orientation%2 * (*orientation-2);
        current_case[1] += abs((*orientation-1))%2* (1-*orientation);
        *orientation = (*orientation+3)%4;
    }
    else if (last_move==1){ //Le dernier déplacement : TOUT DROIT
        current_case[0] += abs((*orientation-1))%2* (*orientation-1); //si déplacement horizontal => null ;
        current_case[1] += *orientation%2* (*orientation-2); //si déplacement vertical => null ;
    }
    else if (last_move==2){ //Le dernier déplacement : GAUCHE
        current_case[0] += *orientation%2* (2-*orientation);
        current_case[1] += abs((*orientation-1))%2* (*orientation-1);
        *orientation = (*orientation+1)%4;
    }
    else { //Le dernier déplacement : BACK
        current_case[0] += abs((*orientation-1))%2* (1-*orientation);
        current_case[1] += *orientation%2* (2-*orientation);
        *orientation = (*orientation+2)%4;
    }
}

//Test et renvoie 1 s'il n'y a pas de mur entre entre map[i][j] et la case (v_i, v_j) d'à coté
int test_no_mur(CASE **map, int i, int j, int orientation){
    switch(orientation){

    case 0:
        if(map[i][j].bas==0) return 1;
        break;

    case 1:
        if(map[i][j].gauche==0) return 1;
        break;

    case 2:
        if(map[i][j].haut==0) return 1;
        break;

    case 3:
        if(map[i][j].droite==0) return 1;
        break;
    }
    return 0;
}


//Test si on est sur l'arrivée
//Test gagne à appeler si on n'est pas sur le bord
int test_gagne(CASE **map, int *current_case){
    int k, l;
    for(k=1; k<4; k+=2){
        //(k=1)Test mur à gauche(j-1) de la current //(k=3)Test mur à droite(j+1) de la current
        if(test_no_mur(map, current_case[0], current_case[1], k)){
            for(l=0; l<3; l+=2){
                //(l=0)Test du bas(i+1) //(l=2)Test du haut(i-1)
                if(test_no_mur(map, current_case[0], current_case[1], l)){
                    // Test  mur à gauche(j-1) de la (current[0]+1, current[1]+1) //Test mur à gauche(j-1) de la (current[0]-1, current[1]+1)
                    if(test_no_mur(map, current_case[0]-l+1, current_case[1]+k-2, 4-k)){
                        //Test mur en haut(i-1) de la (current[0]+1, current[1]+1) //Test mur en bas(i+1) de la (current[0]-1, current[1]+1)
                        if(test_no_mur(map, current_case[0]-l+1, current_case[1]+k-2, 2-l)){
                            return 1;
                        }
                    }
                }
            }
        }
    }
}

void move_robot(int dist_consigne_g, int dist_consigne_d){
    int dist_g_offset = 0;//////////////////////////////////////////////////////////////////////////////////////////////////////
    int dist_d_offset = 0;//////////////////////////////////////////////////////////////////////////////////////////////////////
    int dist_g, dist_d;
    while(dist_g<dist_consigne_g+dist_g_offset && dist_d<dist_consigne_d+dist_d_offset){
        //fonction_avancer_roue_gauche();
        //fonction_avancer_roue_droite();
        dist_g += 1;//fonction_permettant_de_recuperer_la_distance_roue_gauche();////////////////////////////////////////////////
        dist_d += 1;//fonction_permettant_de_recuperer_la_distance_roue_droite();////////////////////////////////////////////////
    }

}

//Fonction move_straight : avancer tout droit
void move_straight(){
    int dist_consigne_g=9000, dist_consigne_d=9000;
    move_robot(dist_consigne_g, dist_consigne_d);
}

//Fonction move_straight : tourner et avancer à gauche
void move_left(){
    int dist_consigne_g=3000, dist_consigne_d=9000;
    move_robot(dist_consigne_g, dist_consigne_d);
}


//Fonction move_straight : tourner et avancer à droite
void move_right(){
    int dist_consigne_g=9000, dist_consigne_d=3000;
    move_robot(dist_consigne_g, dist_consigne_d);
}

//Fonction move_straight : se retourner et avancer tout droit
void move_back(){
    int dist_consigne_g=5000, dist_consigne_d=0;
    move_robot(dist_consigne_g, dist_consigne_d);
}


//Fonction detect renvoie la moyenne des XXX dernières valeurs données par chaque capteur
double moy_detect(Liste capteur, int nb_val){
    Liste p=capteur;
    int i;
    double sum=0;

    for(i=0; i<nb_val; i++){
        if(!est_vide(p)){
            sum += p->val;
            p=p->suiv;
        }else{
            printf("Liste pas assez grande\n");
            return -2;
        }
    }
    return sum/i;
}



//Fonction Mapping: REMPLISSAGE MATRICE puis MOV
Liste* mapping(Liste* capteurs, CASE **map, int* current_case, int* orientation, int ref_capteur, int *last_move){
    int nb_for_moy = 1;//on prend la moyenne des XX dernières valeurs des capteurs
    int move=0, mur_r=0, mur_s=0, mur_l=0;
    //maj_capteurs
    capteurs[0] = ajout_tete(0,capteurs[0]); //FONCTION_CAPTEUR RIGHT en premier argument**************************************************************
    capteurs[1] = ajout_tete(60,capteurs[1]); //FONCTION_CAPTEUR STRAIGHT en premier argument**************************************************************
    capteurs[2] = ajout_tete(60,capteurs[2]); //FONCTION_CAPTEUR LEFT en premier argument**************************************************************

    //calculs des moyennes des nb valeurs des capteurs
    if (moy_detect(capteurs[0], nb_for_moy)>ref_capteur) mur_r=1;
    if (moy_detect(capteurs[1], nb_for_moy)>ref_capteur) mur_s=1;
    if (moy_detect(capteurs[2], nb_for_moy)>ref_capteur) mur_l=1;


    rempli_map(map, current_case, orientation, mur_r, mur_s, mur_l);


    //on effectue des attributions de vitesses en fonction des capteurs
    if(!mur_r){
        printf("\nright**********\n\n");
        move_right();
        *last_move = 0;
    }
    else if(!mur_s){
        printf("\nstraight**********\n\n");
        move_straight(); //A ajouter compensation du rapport moy_left/moy_right = 1 pour recentrer le robot*************************************
        *last_move = 1;
    }
    else if(!mur_l){
        printf("\nleft**********\n\n");
        move_left();
        *last_move = 2;
    }
    else{
        printf("\nback**********\n\n");
        move_back();
        *last_move = 3;
    }



    return capteurs;
}

//Fonction remplissage de la map en fonction de la current_case et de l'orientation
/*
    Remplissage des current_case et du complémentaire
*/
void rempli_map(CASE **map, int* current_case, int* orientation, int right, int straight, int left){
    switch(*orientation){
    case 0:
        if(!left){ //si pas de mur
            map[current_case[0]][current_case[1]].gauche = 0; //break du mur
            map[current_case[0]][current_case[1]-1].droite = 0; //complementaire
        }
        if(!straight){
            map[current_case[0]][current_case[1]].haut = 0;
            map[current_case[0]-1][current_case[1]].bas = 0;
        }
        if(!right){
            map[current_case[0]][current_case[1]].droite = 0;
            map[current_case[0]][current_case[1]+1].gauche = 0;
        }
        break;

    case 1:
        if(!left){
            map[current_case[0]][current_case[1]].bas = 0;
            map[current_case[0]+1][current_case[1]].haut = 0;
        }
        if(!straight){
            map[current_case[0]][current_case[1]].gauche = 0;
            map[current_case[0]][current_case[1]-1].droite = 0;
        }
        if(!right){
            map[current_case[0]][current_case[1]].haut = 0;
            map[current_case[0]-1][current_case[1]].bas = 0;
        }
        break;

    case 2:
        if(!left){
            map[current_case[0]][current_case[1]].droite = 0;
            map[current_case[0]][current_case[1]+1].gauche = 0;
        }
        if(!straight){
            map[current_case[0]][current_case[1]].bas = 0;
            map[current_case[0]+1][current_case[1]].haut = 0;
        }
        if(!right){
            map[current_case[0]][current_case[1]].gauche = 0;
            map[current_case[0]][current_case[1]-1].droite = 0;
        }
        break;

    case 3:
        if(!left){
            map[current_case[0]][current_case[1]].haut = 0;
            map[current_case[0]-1][current_case[1]].bas = 0;
        }
        if(!straight){
            map[current_case[0]][current_case[1]].droite = 0;
            map[current_case[0]][current_case[1]+1].gauche = 0;
        }
        if(!right){
            map[current_case[0]][current_case[1]].bas = 0;
            map[current_case[0]+1][current_case[1]].haut = 0;
        }
        break;
    }
}
