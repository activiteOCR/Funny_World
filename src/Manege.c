#include "Manege.h"
#include <stdlib.h>

Manege *nouveau_manege(float temps_attente_initial)
{
    Manege *manege = malloc(sizeof(Manege));
    manege->temps_attente_initial = temps_attente_initial;
    manege->temps_attente_total = temps_attente_initial; // Ajouter le temps initial au temps total d'attente
    manege->temps_de_tour_total = 0.0;

    return manege;
}

ListeLiee *nouvelle_queue_de_manege()
{
    return q_nouvelle_queue(sizeof(Visiteur));
}

void mettre_visiteur_dans_queue(ListeLiee *manege_queue, Visiteur *visiteur)
{
    q_mettre_un_element_en_queue(manege_queue, (void *)visiteur);
}

Visiteur *trouver_visiteur_de_tete(ListeLiee *manege_queue)
{
    return (Visiteur *)q_trouver_tete(manege_queue);
}
