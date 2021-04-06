#ifndef _QUEUEPRIORITAIRE_H_
#define _QUEUEPRIORITAIRE_H_

#include <stdbool.h>

typedef struct qp_Maillon
{
    void *data;
    int priorite;
    struct qp_Maillon *suivant;
} qp_Maillon;

typedef struct QueuePrioritaire
{
    int longueur;
    int data_taille;
    qp_Maillon *avant;
    qp_Maillon *apres;
} QueuePrioritaire;

/* Retourne une nouvelle queue qui peut stocker des element d'une taille donnee */
QueuePrioritaire *qp_nouvelle_queue(int data_taille);

/* Ajouter un element dans la queue en fonction de sa priorite */
void qp_mettre_un_element_en_queue(QueuePrioritaire *queue, void *data, int priorite);

/* Enlever l'element a l'avant */
void qp_couper_tete_queue(QueuePrioritaire *queue);

/* Trouver l'element a l'avant */
void *qp_trouver_tete(QueuePrioritaire *queue);

/* Vérifiez si la queue est vide ou non  */
bool qp_est_vide(QueuePrioritaire *queue);

#endif
