#include <stdlib.h>
#include <stdio.h>
#include "sequences.h"

/* Inversion d'une sequence  : à implementer */


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

/* Inversion d'une sequence */
void inversion(liste_t *l) {
    if(l->tete != NULL) {
        liste_t inverse;
        inverse.tete = NULL;
        cellule_t *cellp = l->tete;
        cellule_t *cellpre = l->tete;
        cellule_t *revers_cell;
        while(cellp != NULL) {
            if(inverse.tete == NULL) {
                revers_cell = (cellule_t *) malloc(sizeof(cellule_t));
                revers_cell->suivant = NULL;
                revers_cell->valeur = cellp->valeur;
                inverse.tete = revers_cell;
            }
            else {
                cellpre = inverse.tete;
                revers_cell = (cellule_t *) malloc(sizeof(cellule_t));
                revers_cell->valeur = cellp->valeur;
                revers_cell->suivant = cellpre;
                inverse.tete = revers_cell;
            }
            cellp = cellp->suivant;
        }

        l->tete = inverse.tete;
    }
}
