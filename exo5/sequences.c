#include <stdlib.h>
#include <stdio.h>
#include "sequences.h"

/* Tri d'une sequence  : à implementer */


/* lecture d'une sequence d'entiers.
  En entrée : des entiers (-1 pour finir)*/
void saisir(liste_t *l, int valeurMin) {
  int n=-1;
  cellule_t *c;
  printf("Donner un entier (un entier négatif pour finir) :\n");
  scanf("%d",&n);
  if (n>=valeurMin) {
    c = (cellule_t *) malloc(sizeof(cellule_t));  
    c->valeur = n;
    c->suivant = NULL;  
    l->tete = c;
    printf("Donner un entier (un entier négatif pour finir) :\n");
    scanf("%d",&n);
    while (n>=valeurMin) {
      c->suivant = (cellule_t *) malloc(sizeof(cellule_t));
      c = c->suivant;
      c->valeur = n;
      c->suivant = NULL;  
      printf("Donner un entier (un entier négatif pour finir) :\n");
      scanf("%d",&n);}}
  else {
    l->tete = NULL;}
return;}

/* Affichage d'une sequence d'entiers.
  En  sortie : un espace entre deux entiers */
void afficher(liste_t l) {
  cellule_t *c;
  if (l.tete==NULL) {
    printf("\n");}
  else {
    c = l.tete;
    while (c!=NULL) {
      printf(" %d",c->valeur);
      c = c->suivant;}
    printf("\n");}
return;}

/* Tri d'une sequence */
void tri(liste_t *l) {
    // en utilisant le tri a bulles
    int i = 0, tmp;
    cellule_t *cellp, *cellps;
    cellp = l->tete;

    while (cellp != NULL) { // calcul de la taille de LC
        cellp = cellp->suivant;
        i++;
    }

    for (int j = 0; j < i - 1; j++) {
        cellp = l->tete;
        cellps = cellp->suivant;

        for (int k = 0; k < i - 1 - j; k++) {
            if (cellp->valeur > cellps->valeur) {
                tmp = cellp->valeur;
                cellp->valeur = cellps->valeur;
                cellps->valeur = tmp;
            }
            cellp = cellps;
            cellps = cellps->suivant;
        }
    }
}