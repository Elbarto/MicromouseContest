#include "ia.h"



//Fonction permettant de mettre la map sous forme de tableau avec des liens entre les cases pour pouvoir effectuer Bellman
Liste* recuperation(CASE** map, int cases, Liste *tab){
    int i=0, j=0, indice=0;
    for(i=0; i<cases; i++){
        for(j=0; j<cases; j++){
            indice = map[i][j].numero;
            if(map[i][j].bas<1){
                tab[indice] = ajout_tete((indice+cases), tab[indice]);
            }
            if(map[i][j].gauche<1){
                tab[indice] = ajout_tete((indice-1), tab[indice]);
            }
            if(map[i][j].haut<1){
                tab[indice] = ajout_tete((indice-cases), tab[indice]);
            }
            if(map[i][j].droite<1){
                tab[indice] = ajout_tete((indice+1), tab[indice]);
           }
        }
    }
    return tab;
}

//Fonction qui affiche le résutlat de la fonction recuperation
void affiche_tab(Liste *tab, int cases){
    int i=0;
    Liste p;
    for(i=0; i<(cases*cases); i++){
        for(p=tab[i]; !est_vide(p); p=p->suiv){
            printf("Case %d -> %lf\n", i, p->val);
        }
    }
}


/* Bellman
    Cout de 1 pour 1 déplacement => optimisation cout plus important pour un virage que ligne droite
*/
SOMMET* bellman(SOMMET* trajet, Liste *tab, int nb_sommet, int depart){
	int i,j,k;
	double cout_temp;
	for(i=0; i<nb_sommet; i++){
		trajet[i].cout=100000;
	}
	trajet[depart].cout=0;
	for(k=0; k<nb_sommet; k++){
		for(j=0; j<nb_sommet; j++){
			for(i=0; i<nb_sommet; i++){
				cout_temp = rech_cout(tab, j, i);
				if(trajet[j].cout+cout_temp<trajet[i].cout){
					trajet[i].cout = trajet[j].cout+cout_temp;
					trajet[i].pere = j;
				}
			}
		}
	}
	return trajet;
}
//Fonction recherche le cout entre 2 stations, utilisée dans Bellman
int rech_cout(Liste *tab,  int depart, int arrivee){
	Liste chemin=creer_liste();
	chemin = rech(arrivee, tab[depart]);
	if(chemin){
		return 14;
	}else{
		return 1000000.00;
	}
}

//Fonction affiche le resultat de Bellman
void affiche_bellman(SOMMET *tab, int nb){
	int i;
	for(i=0; i<nb; i++){
		printf("***Depart: 0, Arrivee: %d, cout: %lf, pere: %d\n", i, tab[i].cout, tab[i].pere);
	}
}


//Fonction calcul du parcours a partir du resultat de Bellman
Liste chemin_bellman(SOMMET* tab, int depart, int arrivee){
    int i=arrivee;
    Liste chemin = creer_liste();
	while(i!=depart){
		chemin = ajout_tete(i, chemin);
		i = tab[i].pere;
	}
	chemin = ajout_tete(i, chemin);
	return chemin;
}

//Fonction affiche le chemin Bellman
void affiche_chemin_bellman(Liste chemin){
    Liste chemin2;
	if(!chemin) printf("La voie est vide");
	for(chemin2=chemin; !est_vide(chemin2); chemin2=chemin2->suiv){
		printf("Case : %lf\n",chemin2->val);
	}

}
/*
Amelioration Bellman
SOMMET* bellman(SOMMET* trajet, Liste *tab, int nb_sommet, int depart){
	int i,j,k;
	//optimisation : File comprenant les cases a (re)tester car leur valeur a ete modifiee
	File file_sommets=creer_file();;

	double cout_temp;
	for(i=0; i<nb_sommet; i++){
		trajet[i].cout=100000;
	}

	//optimisation, on ajoute le sommet de depart, l'unique sommet a traite au debut
	file_sommets = enfiler(depart, file_sommets);

	trajet[depart].cout=0;

	//On effectue Bellman pour les sommets qui ont ete modifie a l'iteration precedente jusqu'a ce que plus aucune case ne soit modifiee donc c'est la fin
	while(!file_vide(file_sommets)){
        j = defiler(&file_sommets);
        for(i=0; i<nb_sommet; i++){
            cout_temp = rech_cout(tab, j, i);
            if(trajet[j].cout+cout_temp<trajet[i].cout){
                trajet[i].cout = trajet[j].cout+cout_temp;
                trajet[i].pere = j;
                if(!in_file(file_sommets, i)){
					file_sommets = enfiler(i, file_sommets);
				}
            }
        }
	}
	return trajet;
}


int in_file(File f, int num){
	File f2;
	if(f==NULL){
		return 0;
	}
	if(f=f->suiv){
		if(f->val==num){
			return 1;
		}else{
			return 0;
		}
	}else{
		for(f2=f->suiv; f2!=f; f2->suiv){
			if(f2->val==num){
				return 1;
			}
		}
		return 0;
	}
}
*/

//Faire fonction pour exécuter les move du trajet obtenu avec "chemin Bellman"
