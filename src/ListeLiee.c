/**
 * \file ListeLiee.c
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * fonctions gerant les liste liées (chainées).
 *
 */
#include "ListeLiee.h"
#include <stdlib.h>
#include <string.h> // for memcpy
#include <stdio.h>

/**
 * \fn ll_Maillon *ll_nouveau_maillon(void *data, int data_taille)
 * \brief Création d'un nouveau maillon.
 *
 * \param data pointeur de type vide.
 * \param data_taille de type int.
 * \return l'adresse du nouveau maillon.
 */
ll_Maillon *ll_nouveau_maillon(void *data, int data_taille)
{
    ll_Maillon *maillon = malloc(sizeof(ll_Maillon));
    maillon->data = malloc(data_taille);
    maillon->suivant = NULL;
    memcpy(maillon->data, data, data_taille);

    return maillon;
}

/**
 * \fn ListeLiee *ll_nouvelle_liste(int data_taille)
 * \brief Création d'une nouvelle liste.
 *
 * \param data_taille de type int.
 * \return l'adresse de la nouvelle liste.
 */
ListeLiee *ll_nouvelle_liste(int data_taille)
{
    ListeLiee *liste = malloc(sizeof(ListeLiee));
    liste->data_taille = data_taille;
    liste->longueur = 0;
    liste->debut = NULL;
    liste->fin = NULL;

    return liste;
}

/**
 * \fn void ll_ajouter(ListeLiee *liste, void *data)
 * \brief Ajout d'un maillon dans la liste.
 *
 * \param liste pointeur de type ListeLiee.
 * \param data pointeur de type vide.
 * \return vide.
 */
void ll_ajouter(ListeLiee *liste, void *data)
{
    ll_Maillon *maillon = ll_nouveau_maillon(data, liste->data_taille);

    if (liste->longueur == 0)
    {
        liste->debut = maillon;
        liste->fin = maillon;
    }
    else
    {
        liste->fin->suivant = maillon;
        liste->fin = maillon;
    }

    liste->longueur++;
}

/**
 * \fn void *ll_trouver_tete(ListeLiee *liste)
 * \brief trouver la tete de la liste.
 *
 * \param liste pointeur de type ListeLiee.
 * \return vide.
 */
void *ll_trouver_tete(ListeLiee *liste)
{
    if (liste->debut == NULL)
    {
        perror("La liste est vide");
        exit(EXIT_FAILURE);
    }

    return liste->debut->data;
}

/**
 * \fn void ll_couper_tete(ListeLiee *liste)
 * \brief supprimer le maillon de la tete de la liste.
 *
 * \param liste pointeur de type ListeLiee.
 * \return vide.
 */
void ll_couper_tete(ListeLiee *liste)
{
    if (liste->debut == NULL)
    {
        perror("La liste est vide");
        exit(EXIT_FAILURE);
    }

    ll_Maillon *temp = liste->debut;
    liste->debut = liste->debut->suivant;
    free(temp);
    liste->longueur--;
}

/**
 * \fn bool ll_est_vide(ListeLiee *liste)
 * \brief check si liste vide.
 *
 * \param liste pointeur de type ListeLiee.
 * \return booleen vrai ou faux.
 */
bool ll_est_vide(ListeLiee *liste)
{
    return liste->longueur == 0;
}
