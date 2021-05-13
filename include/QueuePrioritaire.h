/**
 * \file QueuePrioritaire.h
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * Structure et prototype QueuePrioritaire.
 *
 */
#ifndef _QUEUEPRIORITAIRE_H_
#define _QUEUEPRIORITAIRE_H_

#include <stdbool.h>

/**
 * \struct qp_Maillon
 * \brief Objet qp_Maillon.
 *
 * qp_Maillon est un objet de gestion de maillon de queue prioritaire. 
 * attribut maillon queue prioritaire. 
 */
typedef struct qp_Maillon
{
    void *data;
    int priorite;
    struct qp_Maillon *suivant;
} qp_Maillon;

/**
 * \struct QueuePrioritaire
 * \brief Objet QueuePrioritaire.
 *
 * QueuePrioritaire est un objet de gestion de queue prioritaire. 
 * attribut queue prioritaire. 
 */
typedef struct QueuePrioritaire
{
    int longueur;
    int data_taille;
    qp_Maillon *avant;
    qp_Maillon *apres;
} QueuePrioritaire;

/* Retourne une nouvelle queue qui peut stocker des elements d'une taille donnee */
QueuePrioritaire *qp_nouvelle_queue(int data_taille);

/* Ajouter un element dans la queue en fonction de sa priorite */
void qp_mettre_un_element_en_queue(QueuePrioritaire *queue, void *data, int priorite);

/* Retirer le premier element */
void qp_couper_tete_queue(QueuePrioritaire *queue);

/* Obtenir le premier element*/
void *qp_trouver_tete(QueuePrioritaire *queue);

/* Vérifiez si la queue est vide ou non  */
bool qp_est_vide(QueuePrioritaire *queue);

#endif
