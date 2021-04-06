#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "ListeLiee.h"
#include <stdbool.h>

/* Creer une nouvelle queue */
ListeLiee *q_nouvelle_queue(int data_taille);

/* Enlever un element un tete */
void q_couper_tete_queue(ListeLiee *queue);

/* Ajouter un element a la fin de la queue */
void q_mettre_un_element_en_queue(ListeLiee *queue, void *data);

/* Trouver l'element en tete */
void *q_trouver_tete(ListeLiee *queue);

/* Vérifiez si la queue est vide ou non  */
bool q_est_vide(ListeLiee *queue);

#endif
