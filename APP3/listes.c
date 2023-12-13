#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
    L->tete = NULL;
}

void liberer_liste(liste_t *L) {
    cellule_t *courant = L->tete; // Pointeur vers la cellule en cours de traitement
    cellule_t *suivant; // Pointeur vers la cellule suivante à traiter
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant); // Libération de la mémoire occupée par la cellule actuelle
        courant = suivant; // Passage à la cellule suivante
    }
    // Mise à jour du pointeur de tête de liste
    L->tete = NULL;
}


int ajouter_tete(liste_t *L, string c)
{ /* retourne 0 si OK, 1 sinon  */
    cellule_t *cel;
    if (L == NULL){return 1;}
    cel = (cellule_t *)malloc(sizeof(cellule_t));
    cel->suivant = L->tete;
    cel->val = c;
    L->tete = cel;
    return 0;
}

