#ifndef _VISITEUR_H_
#define _VISITEUR_H_

typedef struct Visiteur
{
    float heure_arrive;
    float temps_de_visite;
    float heure_depart;
} Visiteur;
/* Creates a new customer with arrival_time */
/* Creer un nouveau visiteur avec un temps d'arrivee */
Visiteur *nouveau_visiteur(float heure_arrive);

#endif
