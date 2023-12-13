#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"


/*
 *  Auteur(s) : Anais Belal / Feth-Ellah Boudellal
 *  Date : 01/11/2023
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void)
{
    cellule_t *cel=malloc(sizeof(cellule_t));
    if (cel == NULL) {
        printf("Erreur");
    }
    return cel;
}

void detruireCellule (cellule_t* cel)
{
    free(cel);
}
// char *texte ---- TAB[0] "\0"
void conversion(char *texte, sequence_t *seq) {
    assert(seq != NULL && seq->tete == NULL);
    int len_txt = strlen(texte);
    depth_liste_t depth_liste;
    depth_liste.tete = NULL; // Initialize the depth_liste

    for (int i = 0; i < len_txt; i++) {
        if (texte[i] == '{') {
            depth_t *new_depth = malloc(sizeof(depth_t));
            new_depth->seq = malloc(sizeof(sequence_t));
            new_depth->seq->tete = NULL;
            new_depth->suivant = depth_liste.tete;
            depth_liste.tete = new_depth;

            // add a cell to the head of the main sequence
            cellule_t *new_tete = nouvelleCellule();
            new_tete->command = GroupeDeCmd;
            new_tete->groupe = seq->tete;
            new_tete->suivant = depth_liste.tete->seq->tete;
            depth_liste.tete->seq->tete = new_tete;
        } else if (texte[i] == '}') {

            depth_t *old_depth = depth_liste.tete;
            depth_liste.tete = depth_liste.tete->suivant;
            free(old_depth->seq);
            free(old_depth);
        } else if (!isspace(texte[i])) {
            // add a cell to the head of the main sequence
            cellule_t *new_tete = nouvelleCellule();
            new_tete->command = texte[i];
            new_tete->valeur = Vide;
            new_tete->groupe = NULL;

            // change the head
            new_tete->suivant = seq->tete;
            seq->tete = new_tete;
        }
    }

    // Free any remaining depth entries in the list
    while (depth_liste.tete != NULL) {
        depth_t *old_depth = depth_liste.tete;
        depth_liste.tete = depth_liste.tete->suivant;
        free(old_depth->seq);
        free(old_depth);
    }
}

        // LIS// CREE CELLULE// INSERTION F LA FIN// ++

void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    cellule_t *c,*tmp;
    c = seq->tete;
    /*while(c->suivant != NULL ){
            c = c->suivant;
            if(c->command != GroupeDeCmd){
                printf("%c", c->command);
        } else{
                tmp = c->groupe;
                afficher_groupe(tmp);
            }
    }*/
    while(c->suivant != NULL){
        if(c->command != GroupeDeCmd){
            printf("%c", c->command);
        } else{
            tmp = c->groupe;
            afficher_groupe(tmp);

        }
        c = c->suivant;
    }
}
void command(sequence_t* seq,char *cmd,cellule_t **groupe){
    cellule_t *tmp; // temporary
    tmp = seq->tete; // VERS PREMIERE CELLULE
        seq->tete = tmp->suivant;// JE CHANGE L'@ DE TETE VERS LA DEUXIEME CELLULE = TMP-SUIVANT----DEUXIEME
        *cmd = tmp->command;
        *groupe = tmp->groupe;
    detruireCellule(tmp);
}

void afficher_groupe(cellule_t *groupe){
    printf("{");
    while (groupe->suivant != NULL){
        printf("%c", groupe->command);
        groupe = groupe->suivant;
    }
    if(groupe->command != Vide){
        printf("%c", groupe->command);
    }
    printf("}");
}


cellule_t *concatener(cellule_t *g1,cellule_t *g2){
    if(g1 == NULL) return g2;
    else{
        queue(g1)->suivant = g2;
        return g1;
    }
}
cellule_t *queue(cellule_t *g1){
    while(g1->suivant != NULL) {
        g1= g1->suivant;
    }
    return g1;
}


char *validation_texte(const char *text) {
    int i, j;
    int len = strlen(text);
    char *nv_texte = (char *)malloc(len + 2);
    nv_texte[0] = ' ';
    for (i = 0, j = 1; text[i] != '\0'; i++) { // La je supprime tout \n ( Break Line ) 
        if (text[i] != '\n') {
            nv_texte[j] = text[i];
            j++;
        }
    }
    nv_texte[j] = '\0';
    return nv_texte;
}



void Aff_Cell(cellule_t *cel,cellule_t *suivant,cellule_t *group,char command){
    cel->command = command;
    cel->suivant = suivant; // FUNCTION APRES
    cel->groupe = group;
}

void ajouter_tete_routine(sequence_t *seq, char command) {
    cellule_t *nv_tete = nouvelleCellule();
    Aff_Cell(nv_tete,seq->tete,NULL,command);
    seq->tete = nv_tete;
}

cellule_t * selecteur(sequence_t *seq,int x){
    cellule_t *tmp = seq->tete;
    while (x > 0 && tmp->suivant != NULL){ // WLH DARETHA ANAIS // NIMBRE EMPILIGH
        tmp = tmp->suivant;
        x--;
    }
    return tmp;
}