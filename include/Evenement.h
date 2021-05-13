/**
 * \file Evenement.h
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * Enum, structure et prototype evenement.
 *
 */
#ifndef _EVENEMENT_H_
#define _EVENEMENT_H_

#include "Visiteur.h"
#include "Manege.h"
#include "QueuePrioritaire.h"

/**
 * \enum event_type
 * \brief Constantes d'erreurs.
 *
 * Defini les types d'evenements
 * 
 */
typedef enum
{
    VISITEUR_ARRIVE,  /*!< entree visiteur. */
    VISITEUR_DEPART, /*!< visiteur evenement et represente la fin de sa visite. */
    MANEGE_EVENEMENT /*!< evenement qui represente un manege qui a fini son tour ou qui est pret a en faire un. */    
} event_type;

typedef int (* Action)(Manege *manege, Visiteur *visiteur);

/**
 * \struct Evenement
 * \brief Objet Evenement.
 *
 * Evenement est un objet de gestion d'evenements. 
 * attribut sur les differentes types d'evenements. 
 */
typedef struct Evenement
{
    float heure; /*!< heure a laquelle l'evenement arrive. */
    event_type type;
    Visiteur *visiteur;
    Manege *manege;
    Action action;
} Evenement;

/* Creer un evenement nouveau visiteur */
Evenement *nouveau_visiteur_arrive_evenement(Visiteur *visiteur);

/* Creer un evenement nouveau manege */
Evenement *nouveau_manege_evenement(Manege *manege, float heure);

/* Creer un nouveau evenement depart de visiteur */
Evenement *nouveau_visiteur_depart_evenement(Visiteur *visiteur, float heure_depart);

/* Action pour evenement */
void action(Evenement *evenement);

/* Creer un nouveau evenement queue */
QueuePrioritaire *nouveau_evenement_queue();

/* Mettre un evenement dans la queue */
void mettre_evenement_dans_la_queue(QueuePrioritaire *evenement_queue, Evenement *evenement);

#endif
