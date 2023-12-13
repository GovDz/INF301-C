#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "pile.h"
// PILE = LIFO = LAST IN FIRST OUT
void initialiser(pile_t *pile){
    pile->tete = NULL;
}
void empiler(pile_t *pile, int x,cellule_t *groupe){
    if(x != GroupeDeCmd && groupe == NULL){
        cellule_t *nouvelle_case = malloc(sizeof(cellule_t));
        nouvelle_case->valeur=x;
        nouvelle_case->suivant = pile->tete;
        pile->tete = nouvelle_case;
    } else {
        cellule_t *nouvelle_case = malloc(sizeof(cellule_t));
        nouvelle_case->valeur=x;
        nouvelle_case->suivant = pile->tete;
        nouvelle_case->groupe = groupe;
        pile->tete = nouvelle_case;
    }

}
int depiler(pile_t *pile,cellule_t **groupe){
    int valeur;
    if (pile->tete == NULL){
        printf("ERREUR");
    }
    cellule_t *tmp = pile->tete;
    valeur = tmp->valeur;
    pile->tete = tmp->suivant;
    if (valeur == GroupeDeCmd){
        *groupe = tmp->groupe;
    }
    return valeur;
    detruireCellule(tmp);
}
void soustraction(pile_t *pile){
    int a,b;
    a = depiler(pile,NULL);
    b = depiler(pile,NULL);
    empiler(pile,b-a,NULL);
}
void addition(pile_t *pile){
    int a,b;
    a = depiler(pile,NULL);
    b = depiler(pile,NULL);
    empiler(pile,a+b,NULL);
}
void multiplication(pile_t *pile){
    int a,b;
    a = depiler(pile,NULL);
    b = depiler(pile,NULL);
    empiler(pile,a*b,NULL);
}

void afficher_pile(pile_t *pile){
    cellule_t *tmp = pile->tete;
    cellule_t *groupe;
    while (tmp != NULL){
        if(tmp->valeur == GroupeDeCmd){
            groupe = tmp->groupe;
            afficher_groupe_pile(groupe);
            printf("--");
        } else{
            printf("%d--",tmp->valeur);
        }
        tmp = tmp->suivant;
    }
    printf("E");

}


void afficher_groupe_pile(cellule_t *groupe){
    printf("{");
    while (groupe->suivant != NULL){
        printf("%c", groupe->command);
        groupe = groupe->suivant;
    }
    printf("%c", groupe->command);
    printf("}");
}
cellule_t *obtenir_bvf(pile_t *pile){
    int checker;
    cellule_t *final1 = NULL;
    cellule_t *final2 = NULL;
    depiler(pile,&final1);
    depiler(pile,&final2);
    checker = depiler(pile,NULL);
    if (checker){
        detruireCellule(final1);
        return final2;
    } else return final1;
}
void inverser(pile_t *pile) {
    assert(pile != NULL);
    cellule_t *precedant = NULL, *cel = pile->tete, *suivant;
    while (cel != NULL) {
        suivant = cel->suivant;
        cel->suivant = precedant;
        precedant = cel;
        cel = suivant;
    }
    pile->tete = precedant;
}

void echanger(pile_t *pile) {
    cellule_t *cel_1 = pile->tete;
    cellule_t *cel_2 = pile->tete->suivant;
    cellule_t *reste = pile->tete->suivant->suivant;
    pile->tete = cel_2;
    cel_2->suivant = cel_1;
    cel_1->suivant = reste;
}


cellule_t *SommetVersLaRoutine(pile_t *pile) {
    cellule_t *groupe;
    depiler(pile, &groupe);
    return groupe;
}
cellule_t *Boucle(pile_t *pile){
    if (pile->tete->valeur <= 0) {
        detruire_sommet(pile);
        detruire_sommet(pile);
        return NULL;
    } else {
        int a = pile->tete->valeur;
        pile->tete->valeur = a - 1;
        return pile->tete->suivant->groupe;
    }
}

void detruire_sommet(pile_t *pile) {
    cellule_t *tete_a_supp = pile->tete;
    if (pile->tete->command == GroupeDeCmd) {
        detruire_groupe_tete(pile->tete->groupe);
    }
    pile->tete = pile->tete->suivant;
    detruireCellule(tete_a_supp);
}
void Aff_Cell_int(cellule_t *cel,cellule_t *suivant,cellule_t *group,int command){
    cel->command = command;
    cel->suivant = suivant; // FUNCTION APRES
    cel->groupe = group;
}

void detruire_groupe_tete(cellule_t *cel) {
    cellule_t *old_cel;
    while (cel != NULL) {
        if (cel->command == GroupeDeCmd)
            detruire_groupes_cases(cel->groupe);
        old_cel = cel;
        cel = cel->suivant;
        detruireCellule(old_cel);
    }
    cel = NULL;
}
void detruire_groupes_cases(cellule_t *cel) {
    cellule_t *old_cel;
    while (cel != NULL) {
        if (cel->command == GroupeDeCmd)
            detruire_groupes_cases(cel->groupe);
        old_cel = cel;
        cel = cel->suivant;
        detruireCellule(old_cel);
    }
}


void rotation(pile_t *pile){
    int nbpas = depiler(pile,NULL);
    int nbelement = depiler(pile,NULL);
    if(nbelement >= nbpas){
        if(nbpas != 0 && nbelement != nbpas){
            nbelement--;
            /*sequence_t *seq;
            int n,cmpt = 0;
            cellule_t *groupe = nouvelleCellule();
            cellule_t *nv_cell = nouvelleCellule();
            //cellule_t *tmp = nouvelleCellule();

            while (cmpt < nbelement - 1){
                n = depiler(pile,&groupe);
                if (n == GroupeDeCmd){
                    ajouter_tete_liste(seq,nv_cell,groupe,n);
                }
                else{
                    ajouter_tete_liste(seq,nv_cell,NULL,n);
                }
                cmpt++;                                          // idee 1 : CODE qui marchais seulement pour nbpas superiure a 1;
            }
            cellule_t *Groupe = nouvelleCellule();
            cellule_t *Debut = nouvelleCellule();

            n = depiler(pile,&groupe);
            if (n == GroupeDeCmd){
                ajouter_tete_liste(seq,Debut,Groupe,n);
            }
            else{
                ajouter_tete_liste(seq,Debut,NULL,n);
            }
             */
            cellule_t *cell1 = selecteur(pile,nbelement); // Selection de la cellule avant derniere
            // CELL1--Valeur = CMDGROUPE = 'D'
            cellule_t *cell2 = selecteur(pile,nbelement-nbpas); // ;CA ON CHANGE SA PLACE APRES;
            // CELL1--Valeur = CMDGROUPE = 'A'
            rotation_aux(pile,cell1,cell2);
        }
    }

}

void rotation_aux(pile_t *pile,cellule_t *cell1,cellule_t *cell2){
    cellule_t *tmp = pile->tete; // ON LE STOCK
    pile->tete = cell2->suivant; // pile-tete = 4
    cell2->suivant =  cell1->suivant; // cell1 - SUIV = 9
    cell1->suivant = tmp; // A
}

void clone(pile_t *pile){
    empiler(pile,pile->tete->valeur, obtenir_groupe(pile->tete->groupe));
}

cellule_t *obtenir_groupe(cellule_t *cellule){
    if(cellule==NULL){ // Some Help From ChatGPT & StackOverflow
        return NULL;
    }
    cellule_t *nv = nouvelleCellule();
    nv->command = cellule->command;
    nv->groupe = obtenir_groupe(cellule->groupe);
    nv->suivant = obtenir_groupe(cellule->suivant);
    return nv;

}
    /*
    cellule_t *tmp = cellule;
    cellule_t *tmpcell = NULL;
    cellule_t *group;
    cellule_t *cell = nouvelleCellule();
    cell->command = tmp->command;
    cell->suivant = tmp;
    tmp = tmp->suivant;
    tmpcell = cell;
    group = cell;
    while (tmp != NULL){
        cellule_t *cell = nouvelleCellule();
        cell->command = tmp->command;
        cell->suivant = tmp;
        tmp = tmp->suivant;
        tmpcell = cell;
    }
    return group;
     }
      // works but not always doesnt work with {] cases */

cellule_t *validation(cellule_t *g) {
    cellule_t *tmp;
    bool GroupeDetected = false;
    tmp = g;
    while (tmp != NULL && GroupeDetected == false)
    {
        if(tmp->command == '{') {
            GroupeDetected = true;
        }
        tmp = tmp->suivant;
    }
    cellule_t *aretourner = nouvelleCellule();
    return aretourner;
    
    
}