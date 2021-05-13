/**
 * \file Queue.c
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * fonctions gerant les queues.
 *
 */
#include "Queue.h"

/**
 * \fn ListeLiee *q_nouvelle_queue(int data_taille)
 * \brief Fonction de rappel(callback) appel de la fonction ll_nouvelle_liste.
 *
 * \param data_taille de type int.
 * \return l'adresse du nouvelle liste.
 */
ListeLiee *q_nouvelle_queue(int data_taille)
{
    return ll_nouvelle_liste(data_taille);
}

/**
 * \fn void q_couper_tete_queue(ListeLiee *queue)
 * \brief Appel de la fonction ll_couper_tete.
 *
 * \param queue pointeur de type ListeLiee.
 * \return vide.
 */
void q_couper_tete_queue(ListeLiee *queue)
{
    ll_couper_tete(queue);
}

/**
 * \fn void q_mettre_un_element_en_queue(ListeLiee *queue, void *data)
 * \brief Appel de la fonction ll_ajouter.
 *
 * \param queue pointeur de type ListeLiee.
 * \param data pointeur de type void.
 * \return vide.
 */
void q_mettre_un_element_en_queue(ListeLiee *queue, void *data)
{
    ll_ajouter(queue, data);
}

/**
 * \fn void *q_trouver_tete(ListeLiee *queue)
 * \brief Fonction de rappel(callback) appel de la fonction ll_trouver_tete.
 *
 * \param queue pointeur de type ListeLiee.
 * \return vide.
 */
void *q_trouver_tete(ListeLiee *queue)
{
    return ll_trouver_tete(queue);
}

/**
 * \fn bool q_est_vide(ListeLiee *queue)
 * \brief Appel de la fonction ll_est_vide.
 *
 * \param queue pointeur de type ListeLiee.
 * \return booleen liste vide vrai ou faux.
 */
bool q_est_vide(ListeLiee *queue)
{
    return ll_est_vide(queue);
}
