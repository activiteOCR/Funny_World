#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdbool.h>

typedef struct ll_Maillon
{
    void *data;
    struct ll_Maillon *suivant;
} ll_Maillon;

typedef struct ListeLiee
{
    int longueur;
    int data_taille;
    ll_Maillon *debut;
    ll_Maillon *fin;
} ListeLiee;

/* Retourne une nouvelle liste qui peut stocker des element d'une taille donnee */
ListeLiee *ll_nouvelle_liste(int data_taille);

/* Ajouter un nouveau maillon avec des donnee a la fin de la liste */
void ll_ajouter(ListeLiee *liste, void *data);

/* Trouver l'element de tete */
void *ll_trouver_tete(ListeLiee *liste);

/* Enlever l'element a la tete de la liste */
void ll_couper_tete(ListeLiee *liste);

/* Vérifiez si la liste est vide ou non  */
bool ll_est_vide(ListeLiee *liste);

#endif
