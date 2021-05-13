/**
 * \file Visiteur.c
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * fonctions gerant les nouveaux visteurs.
 *
 */
#include "Visiteur.h"
#include <stdlib.h>

/**
 * \fn Visiteur *nouveau_visiteur(float heure_arrive)
 * \brief Creation d'un nouveau visiteur.
 *
 * \param heure_arrive de type float.
 * \return l'adresse du nouveau visiteur.
 */
Visiteur *nouveau_visiteur(float heure_arrive)
{
    Visiteur *visiteur = malloc(sizeof(Visiteur));
    visiteur->heure_arrive = heure_arrive;

    return visiteur;
}
