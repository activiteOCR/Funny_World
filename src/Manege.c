/**
 * \file Manege.c
 * \brief Projet algo 2 (P18M Simulateur à evenement discret en C).
 * \author Julien.T, Mathieu.B, Anakin.H
 * \version 2.3
 * \date 23 mai 2021
 *
 * fonctions gerant les maneges.
 *
 */
#include "Manege.h"
#include <stdlib.h>

/**
 * \fn Manege *nouveau_manege(float temps_attente_initial)
 * \brief Création d'un nouveau manege.
 *
 * \param temps_attente_initial de type float.
 * \return l'adresse du nouveau manege.
 */
Manege *nouveau_manege(float temps_attente_initial)
{
    Manege *manege = malloc(sizeof(Manege));
    manege->temps_attente_initial = temps_attente_initial;
    manege->temps_attente_total = temps_attente_initial; // Ajouter le temps initial au temps total d'attente
    manege->temps_de_tour_total = 0.0;

    return manege;
}

/**
 * \fn ListeLiee *nouvelle_queue_de_manege()
 * \brief Fonction de rappel(callback) appel de la fonction q_nouvelle_queue.
 *
 * \param void.
 * \return l'adresse de la nouvelle liste.
 */
ListeLiee *nouvelle_queue_de_manege()
{
    return q_nouvelle_queue(sizeof(Visiteur));
}

/**
 * \fn void mettre_visiteur_dans_queue(ListeLiee *manege_queue, Visiteur *visiteur)
 * \brief inserer visiteur dans la queue manege.
 *
 * \param manege_queue pointeur de type ListeLiee.
 * \param visiteur pointeur de type Visiteur.
 * \return vide.
 */
void mettre_visiteur_dans_queue(ListeLiee *manege_queue, Visiteur *visiteur)
{
    q_mettre_un_element_en_queue(manege_queue, (void *)visiteur);
}

/**
 * \fn Visiteur *trouver_visiteur_de_tete(ListeLiee *manege_queue)
 * \brief Fonction de rappel(callback) appel de la fonction q_trouver_tete.
 *
 * \param manege_queue pointeur de type ListeLiee.
 * \return l'adresse du visteur en debut de liste.
 */
Visiteur *trouver_visiteur_de_tete(ListeLiee *manege_queue)
{
    return (Visiteur *)q_trouver_tete(manege_queue);
}
