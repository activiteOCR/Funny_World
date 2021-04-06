#include "Evenement.h"
#include <stdlib.h>

Evenement *nouveau_visiteur_arrive_evenement(Visiteur *visiteur)
{
    Evenement *evenement = malloc(sizeof(Evenement));
    evenement->type = VISITEUR_ARRIVE;
    evenement->visiteur = visiteur;
    evenement->heure = visiteur->heure_arrive;

    return evenement;
}

Evenement *nouveau_visiteur_depart_evenement(Visiteur *visiteur, float heure_depart)
{
    Evenement *evenement = malloc(sizeof(Evenement));
    evenement->type = VISITEUR_DEPART;
    evenement->visiteur = visiteur;
    evenement->heure = heure_depart;

    return evenement;
}

Evenement *nouveau_manege_evenement(Manege *manege, float heure)
{
    Evenement *evenement = malloc(sizeof(Evenement));
    evenement->type = MANEGE_EVENEMENT;
    evenement->heure = heure;
    evenement->manege = manege;

    return evenement;
}

QueuePrioritaire *nouveau_evenement_queue()
{
    return qp_nouvelle_queue(sizeof(Evenement));
}

void mettre_evenement_dans_la_queue(QueuePrioritaire *evenement_queue, Evenement *evenement)
{
    qp_mettre_un_element_en_queue(evenement_queue, (void *)evenement, -(evenement->heure));
}
