//
// Created by anais et feth on 12/10/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbres.h"
#include "arbresphylo.h"

int DEBUG = 0;

void generer_dot(arbre racine, FILE* fichier_dot) {
    if (racine == NULL) {
        return;
    }

    if (racine->gauche != NULL) {
        fprintf(fichier_dot, "\"%s\" -> \"%s\" [label = \"non\"]\n", racine->valeur, racine->gauche->valeur);
        generer_dot(racine->gauche, fichier_dot);
    }

    if (racine->droit != NULL) {
        fprintf(fichier_dot, "\"%s\" -> \"%s\" [label = \"oui\"]\n", racine->valeur, racine->droit->valeur);
        generer_dot(racine->droit, fichier_dot);
    }

}
int main(int argc, char* argv[])
{
    char *fichier = NULL;

    if (argc < 2) {
        fprintf (stderr, "Usage:  %s <fichier>\n", argv[0]);
        exit(1);
    }

    fichier = argv[1];

    debug ("Ouverture de %s\n", fichier);
    FILE* f = fopen (fichier, "r");
    if (!f) {
        fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", fichier);
        perror (fichier);
        exit(1);
    }

    arbre mon_arbre = lire_arbre(f);

    FILE* fichier_dot = fopen("affichage.dot", "w");
    if (fichier_dot == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    fprintf(fichier_dot, "digraph arbre {\n");
    generer_dot(mon_arbre, fichier_dot);
    fprintf(fichier_dot, "}\n");
    fclose(fichier_dot);
    return 0;
}
