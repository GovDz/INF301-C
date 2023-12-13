#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"
void initalisation(int *a, int b) {
    *a = b;
}
void analyse_arbre_rec(arbre racine, int *nb_esp, int *nb_carac) {
    if (racine != NULL) {
        if (racine->gauche == NULL && racine->droit == NULL) {
            *nb_esp = *nb_esp + 1;
        } else {
            *nb_carac = *nb_carac + 1;
            if (racine->gauche != NULL) {
                analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);
            }
            if (racine->droit != NULL) {
                analyse_arbre_rec(racine->droit, nb_esp, nb_carac);
            }
        }
    }
}
void analyse_arbre(arbre racine, int *nb_esp, int *nb_carac) {
    initalisation(nb_esp, 0);
    initalisation(nb_carac, 0);
    analyse_arbre_rec(racine, nb_esp, nb_carac);
}





/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece(arbre racine, char *espece, liste_t *seq) {
    // Cas de base : Arbre vide
    if (racine == NULL) {
        return 1; // Non trouvé
    }
    // Vérifier si l'espèce est trouvée
    if (strcmp(espece, racine->valeur) == 0) {
        return 0; // Trouvé
    }
    // Recherche récursive dans le sous-arbre gauche
    if (rechercher_espece(racine->gauche, espece, seq) == 0) {
        return 0; // Trouvé
    }
    // Recherche récursive dans le sous-arbre droit
    if (rechercher_espece(racine->droit, espece, seq) == 0) {
        if (racine->valeur != NULL) {
            ajouter_tete(seq, racine->valeur);
        }
        return 0; // Trouvé
    }
    // Non trouvé
    return 1;
}




/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece_recursive(arbre *a, char *espece, cellule_t *seq)
{
    if (seq == NULL)
    {
        if (*a == NULL)
        {
            *a = nouveau_noeud();
            (*a)->valeur = espece;
            return 0;
        }
        while ((*a)->gauche != NULL)
        {
            a = &(*a)->gauche;
        }
        if (est_feuille(*a))
        {
            printf("Cannot add %s: has the same characters as %s.\n", espece, (*a)->valeur);
            return 1;
        }
        else
        {
            (*a)->gauche = nouveau_noeud();
            (*a)->gauche->valeur = espece;
            return 0;
        }
    }
    else
    {if (*a == NULL || est_feuille(*a))
        {noeud *n = nouveau_noeud();
            n->valeur = seq->val;
            if (*a != NULL)
            {
                noeud *fg = nouveau_noeud();
                fg->valeur = (*a)->valeur;
                n->gauche = fg;
            }

            noeud *n_p = n;
            while (seq->suivant != NULL)
            {
                noeud *fd = nouveau_noeud();
                fd->valeur = seq->suivant->val;
                n_p->droit = fd;
                n_p = fd;
                seq = seq->suivant;
            }
            noeud *fe = nouveau_noeud();
            fe->valeur = espece;
            n_p->droit = fe;
            *a = n;
            return 0;
        }
        else
        {
            if (strcmp(seq->val, (*a)->valeur) == 0)
            {
                return ajouter_espece_recursive(&(*a)->droit, espece, seq->suivant);
            }
            else
            {
                return ajouter_espece_recursive(&(*a)->gauche, espece, seq);
            }
        }
    }
}

// Wrapper function to call the recursive version
int ajouter_espece(arbre *a, char *espece, cellule_t *seq)
{
    return ajouter_espece_recursive(a, espece, seq);
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {
   printf ("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
}

// Acte 4


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
