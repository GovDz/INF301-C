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
void afficher_par_niveau(arbre a, FILE* fout) {
    if (a == NULL) {
        return;
    }

    // Utilisation d'un tableau pour le parcours en largeur
    arbre tab[25000];
    int deb = 0, niveau = 0, fini = 0, nb_elems = 1;

    tab[0] = a;

    // Parcours en largeur
    while (nb_elems > 0) {
        // Affichage de la valeur si le noeud a des sous-arbres non vides
        if (!(tab[deb]->gauche == NULL && tab[deb]->droit == NULL)) {
            fprintf(fout, "%s ", tab[deb]->valeur);
        }

        // Ajout du sous-arbre gauche dans le tableau si non vide
        if (tab[deb]->gauche != NULL) {
            fini = (fini + 1) % 25000;
            tab[fini] = tab[deb]->gauche;
            nb_elems++;
        }

        // Ajout du sous-arbre droit dans le tableau si non vide
        if (tab[deb]->droit != NULL) {
            fini = (fini + 1) % 25000;
            tab[fini] = tab[deb]->droit;
            nb_elems++;
        }

        // Décrémentation du nombre d'éléments restants à traiter
        nb_elems--;

        // Changement de niveau et affichage d'une nouvelle ligne si nécessaire
        if (deb == niveau) {
            niveau = fini;
            fprintf(fout, "\n");
        }

        // Passage au prochain élément dans le tableau circulaire
        deb = (deb + 1) % 25000;
    }
}

// Acte 4
// A l'aide de ChatGPT ( Explication du principe ) + Quelq funcs

enum ErrorCode {NOEUD_VIDE = -126,ERREUR =-127 ,NOEUD_AJOUTE = -128};
int recherche(cellule_t *seq, const char *nom) {
    cellule_t *cel = seq;
    while (cel != NULL) {
        if (strcmp(cel->val, nom) == 0) {
            return 1;
        }
        cel = cel->suivant;
    }
    return 0;
}
int nb_element(cellule_t *cel){
    int count=0;
    while (cel != NULL)
    {
        count++;
        cel=cel->suivant;
    }
    return count;
}

int parcours_prefixe(arbre racine, const char *carac, cellule_t *seq, int nb_elem) {
    if (racine == NULL) {
        return NOEUD_VIDE;
    }

    if (est_feuille(racine)) {
        return recherche(seq, racine->valeur) ? 1 : 0;
    }

    int gauche = parcours_prefixe(racine->gauche, carac, seq, nb_elem);

    if (gauche == nb_elem) {
        arbre tmp = nouveau_noeud();
        tmp->valeur = strdup(carac);
        tmp->droit = racine->gauche;
        racine->gauche = tmp;
        return NOEUD_AJOUTE;
    }

    if (gauche == NOEUD_AJOUTE || gauche == ERREUR) {
        return gauche;
    }

    if (NOEUD_VIDE == gauche) {
        return parcours_prefixe(racine->droit, carac, seq, nb_elem);
    }

    int droit = parcours_prefixe(racine->droit, carac, seq, nb_elem);

    if (NOEUD_VIDE == droit) {
        return gauche;
    }

    if (NOEUD_AJOUTE == droit || ERREUR == droit) {
        return droit;
    }

    if ((gauche == 0 || droit == 0) && (gauche != 0 || droit != 0)) {
        if (droit == nb_elem) {
            arbre tmp = nouveau_noeud();
            tmp->valeur = strdup(carac);
            tmp->droit = racine->droit;
            racine->droit = tmp;
            return NOEUD_AJOUTE;
        } else {
            return ERREUR;
        }
    }
    return gauche + droit;
}
int ajouter_carac(arbre *a, char *carac, cellule_t *seq) {
    int nb_elem = nb_element(seq);
    int ret = parcours_prefixe((*a), carac, seq, nb_elem);

    switch (ret) {
        case ERREUR:
        case NOEUD_VIDE:
            printf("Impossible d'ajouter %s\n", carac);
            return 0;
        case NOEUD_AJOUTE:
            return 1;
        default:
            if (nb_elem == ret) {
                arbre tmp = nouveau_noeud();
                tmp->valeur = strdup(carac);
                tmp->droit = (*a);
                (*a) = tmp;
                return 1;
            }
            printf("Impossible d'ajouter %s\n", carac);
            return 0;
    }
}