#include "ListeLiee.h"
#include <stdlib.h>
#include <string.h> // for memcpy
#include <stdio.h>

ll_Maillon *ll_nouveau_maillon(void *data, int data_taille)
{
    ll_Maillon *maillon = malloc(sizeof(ll_Maillon));
    maillon->data = malloc(data_taille);
    maillon->suivant = NULL;
    memcpy(maillon->data, data, data_taille);

    return maillon;
}

ListeLiee *ll_nouvelle_liste(int data_taille)
{
    ListeLiee *liste = malloc(sizeof(ListeLiee));
    liste->data_taille = data_taille;
    liste->longueur = 0;
    liste->debut = NULL;
    liste->fin = NULL;

    return liste;
}

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

void *ll_trouver_tete(ListeLiee *liste)
{
    if (liste->debut == NULL)
    {
        perror("La liste est vide");
        exit(EXIT_FAILURE);
    }

    return liste->debut->data;
}

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

bool ll_est_vide(ListeLiee *liste)
{
    return liste->longueur == 0;
}
