#ifndef _FUNCTIONS
#define _FUNCTIONS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "liste.h"

typedef struct {
    int bas;
    int gauche;
    int haut;
    int droite;
    int numero;
} CASE;


void wait(float step);
int alloue_map(CASE **p, int cases);
void affiche_map(CASE **map);
void affiche_current_case(int *current_case);
void maj_current_case(int* current_case, int *orientation, int last_move);
int test_no_mur(CASE **map, int i, int j, int orientation);
int test_gagne(CASE **map, int *current_case);
void move_robot(int dist_consigne_g, int dist_consigne_d);
void move_straight();
void move_left();
void move_right();
void move_back();
double moy_detect(Liste capteur, int nb_val);
Liste* mapping(Liste* capteurs, CASE **map, int* current_case, int* orientation, int ref_capteur, int *last_move);
void rempli_map(CASE **map, int* current_case, int* orientation, int right, int straight, int left);

#endif


