/**
 * \file ListeLiee.h
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * structure et prototype Liste liée (chainee).
 *
 */
#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdbool.h>

/**
 * \struct ll_Maillon
 * \brief Objet ll_Maillon.
 *
 * ll_Maillon est un objet de gestion des maillons des listes liées.  
 */
typedef struct ll_Maillon
{
    void *data;
    struct ll_Maillon *suivant;
} ll_Maillon;

/**
 * \struct listeLiee
 * \brief Objet listeLiee.
 *
 * listeLiee est un objet de gestion des listes liées.  
 */
typedef struct ListeLiee
{
    int longueur;
    int data_taille;
    ll_Maillon *debut;
    ll_Maillon *fin;
} ListeLiee;

/* Retourne une nouvelle liste qui peut stocker des elements d'une taille donnee */
ListeLiee *ll_nouvelle_liste(int data_taille);

/* Ajouter un nouveau maillon avec des donnees a la fin de la liste */
void ll_ajouter(ListeLiee *liste, void *data);

/* Trouver l'element de tete */
void *ll_trouver_tete(ListeLiee *liste);

/* Enlever l'element a la tete de la liste */
void ll_couper_tete(ListeLiee *liste);

/* Vérifiez si la liste est vide ou non  */
bool ll_est_vide(ListeLiee *liste);

#endif
