#ifndef PILE_H
#define PILE_H

#include <stdbool.h>
#include "listes.h"
typedef sequence_t pile_t;

void initialiser(pile_t *pile);
void empiler(pile_t *pile, int x,cellule_t *groupe);
int depiler(pile_t *pile,cellule_t **groupe);
void soustraction(pile_t *pile);
void addition(pile_t *pile);
void multiplication(pile_t *pile);
void afficher_pile(pile_t *pile);
void afficher_groupe_pile(cellule_t *groupe);
cellule_t *obtenir_bvf(pile_t *pile);
void inverser(pile_t *pile) ;
void echanger(pile_t *pile) ;
cellule_t *SommetVersLaRoutine(pile_t *pile);
cellule_t *Boucle(pile_t *pile);
void detruire_sommet(pile_t *pile);
void detruire_groupes_cases(cellule_t *cel);
void detruire_groupe_tete(cellule_t *cel);
void Aff_Cell_int(cellule_t *cel,cellule_t *suivant,cellule_t *group,int command);
void rotation_aux(pile_t *pile,cellule_t *cell1,cellule_t *cell2);
void rotation(pile_t *pile);
void clone(pile_t *pile);

#endif
