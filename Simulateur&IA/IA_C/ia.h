#ifndef _IA
#define _IA

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "liste.h"
#include "functions.h"

typedef struct SOMMET {
	double cout;
	int pere;
} SOMMET;

Liste* recuperation(CASE** map, int cases, Liste *tab);
void affiche_tab(Liste *tab, int cases);
SOMMET* bellman(SOMMET* trajet,Liste *tab, int nb_sommet, int depart);
int rech_cout(Liste *tab,  int depart, int arrivee);
Liste chemin_bellman(SOMMET* tab, int depart, int arrivee);
void affiche_chemin_bellman(Liste chemin);
void affiche_bellman(SOMMET *tab, int nb);


#endif



