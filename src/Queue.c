#include "Queue.h"

ListeLiee *q_nouvelle_queue(int data_taille)
{
    return ll_nouvelle_liste(data_taille);
}

void q_couper_tete_queue(ListeLiee *queue)
{
    ll_couper_tete(queue);
}

void q_mettre_un_element_en_queue(ListeLiee *queue, void *data)
{
    ll_ajouter(queue, data);
}

void *q_trouver_tete(ListeLiee *queue)
{
    return ll_trouver_tete(queue);
}

bool q_est_vide(ListeLiee *queue)
{
    return ll_est_vide(queue);
}
