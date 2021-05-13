/**
 * \file Evenement.c
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * fonctions gerant les evenements.
 *
 */
#include "Evenement.h"
#include <stdlib.h>

/**
 * \fn Evenement *nouveau_visiteur_arrive_evenement(Visiteur *visiteur)
 * \brief Création liste de type Evenement pour l'evenement VISITEUR_ARRIVE.
 *
 * \param visiteur pointeur de type Visiteur.
 * \return evenement VISITEUR_ARRIVE.
 */
Evenement *nouveau_visiteur_arrive_evenement(Visiteur *visiteur)
{
    Evenement *evenement = malloc(sizeof(Evenement));
    evenement->type = VISITEUR_ARRIVE;
    evenement->visiteur = visiteur;
    evenement->heure = visiteur->heure_arrive;

    return evenement;
}

/**
 * \fn Evenement *nouveau_visiteur_depart_evenement(Visiteur *visiteur, float heure_depart)
 * \brief Création liste de type Evenement pour l'evenement VISITEUR_DEPART.
 *
 * \param visiteur pointeur de type Visiteur.
 * \param heure_depart de type float.
 * \return evenement VISITEUR_DEPART.
 */
Evenement *nouveau_visiteur_depart_evenement(Visiteur *visiteur, float heure_depart)
{
    Evenement *evenement = malloc(sizeof(Evenement));
    evenement->type = VISITEUR_DEPART;
    evenement->visiteur = visiteur;
    evenement->heure = heure_depart;

    return evenement;
}

/**
 * \fn Evenement *nouveau_manege_evenement(Manege *manege, float heure)
 * \brief Création liste de type Evenement pour l'evenement MANEGE_EVENEMENT.
 *
 * \param manege pointeur de type Manege.
 * \param heure de type float.
 * \return evenement MANEGE_EVENEMENT.
 */
Evenement *nouveau_manege_evenement(Manege *manege, float heure)
{
    Evenement *evenement = malloc(sizeof(Evenement));
    evenement->type = MANEGE_EVENEMENT;
    evenement->heure = heure;
    evenement->manege = manege;

    return evenement;
}

/**
 * \fn QueuePrioritaire *nouveau_evenement_queue()
 * \brief Fonction de rappel(callback) appel de la fonction qp_nouvelle_queue.
 *
 * \param void.
 * \return objet queue_prioritaire.
 */
QueuePrioritaire *nouveau_evenement_queue()
{
    return qp_nouvelle_queue(sizeof(Evenement));
}

/**
 * \fn mettre_evenement_dans_la_queue(QueuePrioritaire *evenement_queue, Evenement *evenement)
 * \brief inserer un evenement dans la queue.
 *
 * \param evenement_queue pointeur de type QueuePrioritaire.
 * \param evenement de type Evenement.
 * \return void.
 */
void mettre_evenement_dans_la_queue(QueuePrioritaire *evenement_queue, Evenement *evenement)
{
    qp_mettre_un_element_en_queue(evenement_queue, (void *)evenement, -(evenement->heure));
}
