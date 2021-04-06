#include "QueuePrioritaire.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

qp_Maillon *qp_nouveau_maillon(void *data, int data_taille, int priorite)
{
    qp_Maillon *maillon = malloc(sizeof(qp_Maillon));
    maillon->data = malloc(data_taille);
    maillon->priorite = priorite;
    maillon->suivant = NULL;
    memcpy(maillon->data, data, data_taille);

    return maillon;
}

QueuePrioritaire *qp_nouvelle_queue(int data_taille)
{
    QueuePrioritaire *queue = malloc(sizeof(QueuePrioritaire));
    queue->data_taille = data_taille;
    queue->longueur = 0;
    queue->avant = NULL;
    queue->apres = NULL;

    return queue;
}

void *qp_trouver_tete(QueuePrioritaire *queue)
{
    if (queue->avant == NULL)
    {
        perror("La liste est vide");
        exit(EXIT_FAILURE);
    }

    return queue->avant->data;
}

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

bool qp_est_vide(QueuePrioritaire *queue)
{
    return queue->longueur == 0;
}
