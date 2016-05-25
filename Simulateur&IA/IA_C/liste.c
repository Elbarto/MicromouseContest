#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

Liste creer_liste(void) {	return NULL;	}

int est_vide(Liste L) {	return !L;	}

Liste ajout_tete(ELEMENT e, Liste L)
{ Liste p=(Liste) calloc(1,sizeof(*p));
  if (p==NULL) return NULL;
  p->val=e;
  p->suiv=L;
  return p;
}

Liste rech(ELEMENT e, Liste L)
{ Liste p=L;
  while(!est_vide(p)&&(p->val!=e)) p=p->suiv;
  return p;
}

