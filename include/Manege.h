/**
 * \file Manege.h
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * structure et prototype Manege.
 *
 */
#ifndef _MANEGE_H_
#define _MANEGE_H_

#include "Queue.h"
#include "Visiteur.h"

#define TEMPS_ATTENTE_INITIALE 10.0   // temps max d'attente avant de demarrer pour la premiere fois : 600s
#define TEMPS_ATTENTE_ENTRE_SERVICE 3.0 // temps max entre deux tour : 150s

/**
 * \struct Manege
 * \brief Objet Manege.
 *
 * Evenement est un objet de gestion de manege. 
 * attribut sur les maneges. 
 */
typedef struct Manege
{
    float temps_attente_initial;    /*!< Temps initial d'inactivite. */
    float temps_de_tour_total;
    float temps_attente_total;
    ListeLiee *manege_queue;
} Manege;

/* Creer un nouveau manege avec un temps d'attente initial */
Manege *nouveau_manege(float temps_attente_initial);

/* Creer une nouvelle queue de manege */
ListeLiee *nouvelle_queue_de_manege();

/* Mettre un visiteur dans manege_queue */
void mettre_visiteur_dans_queue(ListeLiee *manege_queue, Visiteur *visiteur);

/* Trouver le visiteur en tete d'une queue */
Visiteur *trouver_visiteur_de_tete(ListeLiee *manege_queue);

#endif
