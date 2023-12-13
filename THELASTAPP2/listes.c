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
void conversion (char *texte, sequence_t *seq)
{
    cellule_t *cel = nouvelleCellule(),*tmpcel,*tmpgroup;
    int depth = 0;
    // FNC
    seq->tete = NULL;
    Aff_Cell(cel,NULL,NULL,*texte);
    tmpcel = cel;
    seq->tete = cel;
    // FNC
    while (*texte != '\0') {
        cellule_t *cel = nouvelleCellule();
        texte = texte + 1;
        if(*texte == '{'){
            cel->command = GroupeDeCmd;
            tmpcel->suivant = cel;
            tmpcel = cel;
            texte = texte + 1;
            depth++;
            if(*texte != '}'){
                cellule_t *groupe = nouvelleCellule();
                Aff_Cell(groupe,NULL,NULL,*texte);
                tmpcel->groupe = groupe;
                texte = texte + 1;
                tmpgroup = groupe;
                if(*texte != '}') {
                    while (depth != 0){
                        if(*texte == '{'){
                            depth++;
                            if(*(texte+1) == '}'){ // change + 1
                                depth--;}
                        } else if(*(texte+1) == '}'){ // change + 1
                            depth--;
                        }
                        cellule_t *groupe = nouvelleCellule();
                        Aff_Cell(groupe,NULL,NULL,*texte);
                        tmpgroup->suivant = groupe;
                        tmpgroup = groupe;
                        texte = texte + 1;
                    }
                }else{
                    depth--;
                }

            }else{
                depth--;
                cellule_t *groupe = nouvelleCellule();
                Aff_Cell(groupe,NULL,NULL,Vide);
                tmpcel->groupe = groupe;
                tmpgroup = groupe;
            }
        }
        else {
            Aff_Cell(cel,NULL,NULL,*texte);
            tmpcel->suivant = cel;
            tmpcel = cel;
        }
    }

    // LIS// CREE CELLULE// INSERTION F LA FIN// ++
    tmpcel = NULL;
    tmpgroup = NULL;
    detruireCellule(tmpcel);
    detruireCellule(tmpgroup);
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

cellule_t *validation(cellule_t *g) {
    char *texte = NULL;
    int i = 0;
    int text_length = 0;
    cellule_t *current = g;
    if (current == NULL) {
        // Handle the case when the input list is empty
        return NULL;
    }
    while (current != NULL) {
        text_length++;
        current = current->suivant;
    }
    texte = (char *)malloc(text_length + 1); // +1 for the null terminator
    if (texte == NULL) {
        return NULL;
    }
    i = 0;
    current = g;
    while (current != NULL) {
        texte[i] = current->command;
        current = current->suivant;
        i++;
    }
    texte[i] = '\0';
    sequence_t nouvelle_seq;
    conversion(texte, &nouvelle_seq);
    free(texte);
    return nouvelle_seq.tete;
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