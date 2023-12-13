#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "pile.h"
#include "curiosity.h"



/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}



int interprete (sequence_t* seq, bool debug)
{
    // Version temporaire a remplacer par une lecture des commandes dans la
    // liste chainee et leur interpretation.

    char commande;
    pile_t pile;
    initialiser(&pile);
    cellule_t *groupe = NULL;
    cellule_t *a_faire = NULL;
    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();
    int ret;         //utilisée pour les valeurs de retour
    while ( true ) { //à modifier: condition de boucle
        command(seq,&commande,&groupe);
        if(!isspace(commande) && commande != Vide){
            switch (commande) {
                case '\n':
                    break;
                case '{':
                    printf("HEHE");
                    break;
                /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */
                case 'A':
                    ret = avance();
                    if (ret == VICTOIRE) return VICTOIRE; /* on a atteint la cible */
                    if (ret == RATE)     return RATE;     /* tombé dans l'eau ou sur un rocher */
                    break; /* à ne jamais oublier !!! */
                case 'D':
                    droite();
                    break; /* à ne jamais oublier !!! */
                case 'G':
                    gauche();
                    break; /* à ne jamais oublier !!! */
                case '0' ... '9': // intervalle de 0 a 9
                    empiler(&pile,atoi(&commande),NULL); // ca m'a pris des heures pour trouver qu'il faut utiliser soit atoi soit commande - '0"
                    break;
                case '-': // soustraction
                    soustraction(&pile);
                    break;
                case GroupeDeCmd: // soustraction
                    empiler(&pile,GroupeDeCmd,groupe);
                    break;
                case '+': // addition
                    addition(&pile);
                    break;
                case '*': // multiplication
                    multiplication(&pile);
                    break;
                case '?': // obtenir b V F ?
                    a_faire = obtenir_bvf(&pile);
                    seq->tete = concatener(validation(a_faire),seq->tete);
                    break;
                case 'M': // MESEURE
                    empiler(&pile,mesure(depiler(&pile,NULL)),NULL);
                    /*ret = depiler(&pile);
                    ret = mesure(ret);
                    empiler(pile,ret); */

                    break;
                case 'P': // POSE
                    pose(depiler(&pile,NULL));
                    break;
                case 'Z': // POSE
                    inverser(&pile);
                    break;
                case 'X': // POSE
                    echanger(&pile);
                    break;
                case '!': //
                    a_faire = SommetVersLaRoutine(&pile);
                    seq->tete = concatener(validation(a_faire),seq->tete);
                    break;
                case 'I': // Ignore
                    detruire_sommet(&pile);
                    break;
                case 'R': // Rotation
                    rotation(&pile);
                    break;
                case 'C': // Clone
                    clone(&pile);
                    break;
                case 'B': // Boucle
                    a_faire = Boucle(&pile);
                    if (a_faire != NULL) // VIDE
                        ajouter_tete_routine(seq, 'B'); // ON AJOUTE B
                    seq->tete = concatener(validation(a_faire),seq->tete);
                    break;
                default:
                    eprintf("Caractère inconnu: '%c'\n", commande);
            }
        }


        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        printf("La pile : ");
        afficher_pile(&pile);
        printf ("\n");
        if (debug) stop();
    }
    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
