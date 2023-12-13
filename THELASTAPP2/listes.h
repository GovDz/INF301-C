#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>



/*
 * Pour réaliser des tests de performance, désactiver tous les 
 * affichages.
 * Pour cela, le plus simple est de redefinir les fonctions principales 
 * en decommentant les 3 lignes suivantes et en commentant l'ancienne 
 * definition de 'eprintf' juste dessous.
 */

#ifdef SILENT

#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif
#define GroupeDeCmd -128
#define Vide -127
extern bool silent_mode;




struct cellule {
    char   command;
    int valeur;
    struct cellule *suivant;
    struct cellule *groupe;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
    int x; // NOMBRE DE GROUPES
};
typedef struct sequence sequence_t;
struct depth {
    sequence_t *seq;
    struct depth *suivant;
};
typedef struct depth depth_t;

struct depth_liste {
    depth_t *tete;
};
typedef struct depth_liste depth_liste_t;


cellule_t* nouvelleCellule (void);

char * validation_texte(const char *texte);

cellule_t *validation(cellule_t *g);

void detruireCellule (cellule_t*);

void conversion (char *texte, sequence_t *seq);

void afficher (sequence_t* seq);

void command(sequence_t* seq,char *command,cellule_t **groupe);

void afficher_groupe(cellule_t *groupe);

cellule_t * obtenir_groupe(cellule_t *cellule);
void remplir(cellule_t *cellule,cellule_t *tmpcel,cellule_t *tmpgroup,char *texte);
cellule_t *concatener(cellule_t *g1,cellule_t *g2);
cellule_t *queue(cellule_t *g1);
void ajouter_tete_routine(sequence_t *seq, char command);
void Aff_Cell(cellule_t *cel,cellule_t *suivant,cellule_t *group,char command);
cellule_t * selecteur(sequence_t *seq,int x);
#endif
