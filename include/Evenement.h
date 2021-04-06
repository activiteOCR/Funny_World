#ifndef _EVENEMENT_H_
#define _EVENEMENT_H_

#include "Visiteur.h"
#include "Manege.h"
#include "QueuePrioritaire.h"

typedef enum
{
    VISITEUR_ARRIVE, // entree visiteur
    VISITEUR_DEPART, // visiteur evenement et represente la fin de sa visite
    MANEGE_EVENEMENT     // evenement qui represente un manege qui a fini son tour ou qui est pret a en faire un
} event_type;

typedef int (* Action)(Manege *manege, Visiteur *visiteur);

typedef struct Evenement
{
    float heure; // heure a laquelle l'evenement arrive
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
