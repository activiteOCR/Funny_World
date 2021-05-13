/**
 * \file Visiteur.h
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * structure et prototype visiteur.
 *
 */
#ifndef _VISITEUR_H_
#define _VISITEUR_H_

/**
 * \struct Visiteur
 * \brief Objet Visiteur.
 *
 * Visiteur est un objet de gestion des visiteurs. 
 * information heure_arrive, le temps_de_visite et heure_de depart. 
 */
typedef struct Visiteur
{
    float heure_arrive; /*!< Heure d'arrivee. */
    float temps_de_visite; /*!< Temps de visite. */
    float heure_depart; /*!< Heure de depart. */
} Visiteur;

/* Creer un nouveau visiteur avec un temps d'arrive */
Visiteur *nouveau_visiteur(float heure_arrive);

#endif
