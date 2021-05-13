/**
 * \file QueuePrioritaire.c
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * fonctions gerant les queues prioritaires.
 *
 */
#include "QueuePrioritaire.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/**
 * \fn qp_Maillon *qp_nouveau_maillon(void *data, int data_taille, int priorite)
 * \brief Creation d'un nouveau maillon prioritaire.
 *
 * \param data pointeur de type void.
 * \param data_taille de type int.
 * \param priorite de type int.
 * \return l'adresse du nouveau maillon prioritaire.
 */
qp_Maillon *qp_nouveau_maillon(void *data, int data_taille, int priorite)
{
    qp_Maillon *maillon = malloc(sizeof(qp_Maillon));
    maillon->data = malloc(data_taille);
    maillon->priorite = priorite;
    maillon->suivant = NULL;
    memcpy(maillon->data, data, data_taille);

    return maillon;
}

/**
 * \fn QueuePrioritaire *qp_nouvelle_queue(int data_taille)
 * \brief Creation d'une nouvelle queue prioritaire.
 *
 * \param data_taille de type int.
 * \return l'adresse de la nouvelle queue prioritaire.
 */
QueuePrioritaire *qp_nouvelle_queue(int data_taille)
{
    QueuePrioritaire *queue = malloc(sizeof(QueuePrioritaire));
    queue->data_taille = data_taille;
    queue->longueur = 0;
    queue->avant = NULL;
    queue->apres = NULL;

    return queue;
}

/**
 * \fn void *qp_trouver_tete(QueuePrioritaire *queue)
 * \brief Trouver la tete de la queue prioritaire.
 *
 * \param queue pointeur de type QueuePrioritaire.
 * \return les données du maillon entete de la queue prioritaire.
 */
void *qp_trouver_tete(QueuePrioritaire *queue)
{
    if (queue->avant == NULL)
    {
        perror("La liste est vide");
        exit(EXIT_FAILURE);
    }

    return queue->avant->data;
}

/**
 * \fn void qp_mettre_un_element_en_queue(QueuePrioritaire *queue, void *data, int priorite)
 * \brief Inserer un element dans la queue prioritaire.
 *
 * \param queue pointeur de type QueuePrioritaire.
 * \param data pointeur de type void.
 * \param priorite de type int.
 * \return vide.
 */
void qp_mettre_un_element_en_queue(QueuePrioritaire *queue, void *data, int priorite)
{
    qp_Maillon *temp = qp_nouveau_maillon(data, queue->data_taille, priorite);

    if (queue->longueur == 0)
    {
        queue->avant = temp;
    }
    else if (queue->avant->priorite < priorite)
    {
        temp->suivant = queue->avant;
        queue->avant = temp;
    }
    else
    {
        qp_Maillon *cour = queue->avant;

        while (cour->suivant != NULL && cour->suivant->priorite >= priorite)
        {
            cour = cour->suivant;
        }

        temp->suivant = cour->suivant;
        cour->suivant = temp;
    }

    queue->longueur++;
}

/**
 * \fn void qp_couper_tete_queue(QueuePrioritaire *queue)
 * \brief Retirer le maillon entete de la queue prioritaire.
 *
 * \param queue pointeur de type QueuePrioritaire.
 * \return vide.
 */
void qp_couper_tete_queue(QueuePrioritaire *queue)
{
    if (queue->avant == NULL)
    {
        perror("La liste est vide");
        exit(EXIT_FAILURE);
    }

    qp_Maillon *temp = queue->avant;
    queue->avant = queue->avant->suivant;
    free(temp);
    queue->longueur--;
}

/**
 * \fn void qp_couper_tete_queue(QueuePrioritaire *queue)
 * \brief check si la queue prioritaire est vide.
 *
 * \param queue pointeur de type QueuePrioritaire.
 * \return booleen check si vrai ou faux.
 */
bool qp_est_vide(QueuePrioritaire *queue)
{
    return queue->longueur == 0;
}
