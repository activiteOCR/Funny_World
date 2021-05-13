#include "QueuePrioritaire.h"
#include "Queue.h"
#include "Visiteur.h"
#include "Manege.h"
#include "Evenement.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* Trouver la plus petite queue */
ListeLiee *trouver_la_plus_petite_queue(Manege *manege[], int nombre_de_manege, int nombre_de_visiteur)
{
    int longueur_min = nombre_de_visiteur + 1;
    int compteur = 0;

    for (int i = 0; i < nombre_de_manege; i++)
    {
        if (manege[i]->manege_queue->longueur == longueur_min)
        {
            compteur++;
        }

        if (manege[i]->manege_queue->longueur < longueur_min)
        {
            longueur_min = manege[i]->manege_queue->longueur;
            compteur = 1;
        }
    }

    int n = (rand() % compteur) + 1; // nombre au hasard entre 1 et le compteur
    int j = 1;

    ListeLiee *manege_queue;

    for (int i = 0; i < nombre_de_manege; i++)
    {
        if (manege[i]->manege_queue->longueur == longueur_min)
        {
            if (j == n)
            {
                manege_queue = manege[i]->manege_queue;
            }
            j++;
        }
    }
    return manege_queue;
};

/* le manege fait son tour avec le visiteur  */
void tour_visiteur(Manege *manege, Visiteur *visiteur, QueuePrioritaire *evenement_queue, float temps_de_service_moyen, float horloge_simulation, FILE *file)
{
    float temps_de_service = 2 * temps_de_service_moyen * rand() / (float)(RAND_MAX);
    float heure_de_depart = temps_de_service + horloge_simulation;
    visiteur->temps_de_visite = temps_de_service;
    visiteur->heure_depart = heure_de_depart;

    manege->temps_de_tour_total = manege->temps_de_tour_total + temps_de_service;

    Evenement *visiteur_depart_evenement = nouveau_visiteur_depart_evenement(visiteur, heure_de_depart);
    Evenement *manege_service_fini_evenement = nouveau_manege_evenement(manege, heure_de_depart);

    mettre_evenement_dans_la_queue(evenement_queue, manege_service_fini_evenement);
    mettre_evenement_dans_la_queue(evenement_queue, visiteur_depart_evenement);

    fprintf(file, "Queue pas vide\n");
    fprintf(file, "Temps de tour : %f\t", temps_de_service);
    fprintf(file, "nouveau temps : %f\n", horloge_simulation + temps_de_service);
}

/* Evenement temps d'inactivite manege */
void mettre_en_attente(Manege *manege, QueuePrioritaire *evenement_queue, float horloge_simulation, FILE *file)
{
    float temps_attente = TEMPS_ATTENTE_ENTRE_SERVICE * rand() / (float)(RAND_MAX);
    manege->temps_attente_total = manege->temps_attente_total + temps_attente;

    Evenement *manege_attente_evenement = nouveau_manege_evenement(manege, horloge_simulation + temps_attente);
    mettre_evenement_dans_la_queue(evenement_queue, manege_attente_evenement);

    fprintf(file, "Queue vide\n");
    fprintf(file, "Temps d'inactivité: %f\t", temps_attente);
    fprintf(file, "Nouveau temps: %f\n", horloge_simulation + temps_attente);
}

/* Run simulation
    mode = 1 for simulation single manege queue (plotting graph)
    mode = 2 for simulating both single and then multiple manege queue
 */
float lancer_simulation(int nombre_de_visiteurs, int nombre_de_maneges, float temps_de_simulation, float temps_de_tour_moyene, int mode)
{
	FILE *file = fopen("output/event_logs.txt", "w");
    if (file == NULL)
    {
        printf("Could not open log file. Continuing...\n");
    }

    Manege *maneges[nombre_de_maneges];       // Tableau maneges
    Visiteur *visiteurs[nombre_de_visiteurs]; // Tableau visiteurs

    /* Creer les visiteurs */
    for (int i = 0; i < nombre_de_visiteurs; i++)
    {
        float heure_arrive = temps_de_simulation * rand() / (float)(RAND_MAX);
        Visiteur *visiteur = nouveau_visiteur(heure_arrive);
        visiteurs[i] = visiteur;
        fprintf(file, "heure d'arrive visiteur : %f\n", heure_arrive);
    }

    /* Creer les maneges */
    for (int i = 0; i < nombre_de_maneges; i++)
    {
        float temps_attente = TEMPS_ATTENTE_INITIALE * rand() / (float)(RAND_MAX);
        Manege *manege = nouveau_manege(temps_attente);
        maneges[i] = manege;
        fprintf(file, "manege temps d'attente: %f\n", maneges[i]->temps_attente_initial);
    }

    float temps_moyen_passe_dans_le_parc_1; // temps moyen d'un visiteur en mode simple queue dans le parc

    /* Simulation */
    for (int sim_compt = 0; sim_compt < mode; sim_compt++)
    {
        QueuePrioritaire *evenement_queue = nouveau_evenement_queue(); // Evenement queue

        /* Creer un evenement arrive de visiteur */
        for (int i = 0; i < nombre_de_visiteurs; i++)
        {
            Evenement *arrive_evenement = nouveau_visiteur_arrive_evenement(visiteurs[i]);
            mettre_evenement_dans_la_queue(evenement_queue, arrive_evenement);
        }

        /* Creation evenement manege */
        for (int i = 0; i < nombre_de_maneges; i++)
        {
            maneges[i]->temps_de_tour_total = 0.0;
            Evenement *manege_en_attente_evenement = nouveau_manege_evenement(maneges[i], maneges[i]->temps_attente_initial);
            mettre_evenement_dans_la_queue(evenement_queue, manege_en_attente_evenement);
        }

        int evenement_compteur = 0;

        /* Variables de statistique */
        float horloge_simulation = 0.0;          // Heure actuelle de simulation
        int total_visiteur_ayant_fait_un_manege = 0;         // Visiteurs total servi peut etre different du nombre total de visiteurs arrivant
        float temps_de_tour_total = 0.0;         // temps total tour
        float temps_total_dans_le_parc = 0.0;          // heure depart - heure arrive
        float temps_dans_le_parc[nombre_de_visiteurs]; // pour l'ecart type
        float temps_attente_max = 0.0;

        if (sim_compt == 0) // Simple queue
        {
            ListeLiee *manege_queue = nouvelle_queue_de_manege(); // Manege queue

            /* Evenement en cours */
            while (!qp_est_vide(evenement_queue))
            {
                evenement_compteur++;

                fprintf(file, "---------------evenement %d ----------------\n", evenement_compteur);
                fprintf(file, "evenement queue longueur: %d\n", evenement_queue->longueur);
                Evenement *evenement = (Evenement *)qp_trouver_tete(evenement_queue);
                qp_couper_tete_queue(evenement_queue);

                horloge_simulation = evenement->heure;
                fprintf(file, "heure : %f\n", horloge_simulation);

                if (evenement->type == VISITEUR_ARRIVE)
                {
                    fprintf(file, "Visiteur arrive evenement\n");

                    if (evenement->visiteur == NULL)
                    {
                        perror("Visiteur arrive evenement n'a pas de visiteur");
                        exit(EXIT_FAILURE);
                    }

					mettre_visiteur_dans_queue(manege_queue, evenement->visiteur);

                    fprintf(file, "Manege courant longueur queue: %d\n", manege_queue->longueur);
                }
                else if (evenement->type == VISITEUR_DEPART)
                {
                    if (evenement->visiteur == NULL)
                    {
                        perror("Visiteur depart evenement n'a pas de visiteur");
                        exit(EXIT_FAILURE);
                    }

                    temps_dans_le_parc[total_visiteur_ayant_fait_un_manege] = evenement->visiteur->heure_depart - evenement->visiteur->heure_arrive;
                    temps_total_dans_le_parc = temps_total_dans_le_parc + temps_dans_le_parc[total_visiteur_ayant_fait_un_manege];
                    temps_de_tour_total = temps_de_tour_total + evenement->visiteur->temps_de_visite;

                    float temps_attente = temps_dans_le_parc[total_visiteur_ayant_fait_un_manege] - evenement->visiteur->temps_de_visite;
                    if (temps_attente > temps_attente_max)
                    {
                        temps_attente_max = temps_attente;
                    }
                    total_visiteur_ayant_fait_un_manege++;

                    fprintf(file, "visiteur quitte le parc\n");
                    free(evenement);
                }
                else if (evenement->type == MANEGE_EVENEMENT)
                {
                    fprintf(file, "Manege evenement\n");

                    if (evenement->manege == NULL)
                    {
                        perror("Manege evenement pas de manege");
                        exit(EXIT_FAILURE);
                    }

                    if (q_est_vide(manege_queue))
                    {
                        if (horloge_simulation < temps_de_simulation)
                        {
                            mettre_en_attente(evenement->manege, evenement_queue, horloge_simulation, file);
                        }
                    }
                    else
                    {
                        Visiteur *visiteur = trouver_visiteur_de_tete(manege_queue);
                        q_couper_tete_queue(manege_queue);

                        tour_visiteur(evenement->manege, visiteur, evenement_queue, temps_de_tour_moyene, horloge_simulation, file);
                    }
                }
                else
                {
                    perror("Pas de correspondance evenement type");
                    exit(EXIT_FAILURE);
                }

                fprintf(file, "-------------------------------\n");
            }

            /* Free manege queue */
            while (!q_est_vide(manege_queue))
            {
                q_couper_tete_queue(manege_queue);
            }
            free(manege_queue);
        }
        else // Multiple manege queues
        {
            /* Creation multiple manege queues */
            for (int i = 0; i < nombre_de_maneges; i++)
            {
                maneges[i]->manege_queue = nouvelle_queue_de_manege();
            }

            /* Evenement en cours */
            while (!qp_est_vide(evenement_queue))
            {
                evenement_compteur++;

                fprintf(file, "---------------evenement %d ----------------\n", evenement_compteur);
                fprintf(file, "evenement queue longueur: %d\n", evenement_queue->longueur);
                Evenement *evenement = (Evenement *)qp_trouver_tete(evenement_queue);
                qp_couper_tete_queue(evenement_queue);

                horloge_simulation = evenement->heure;
                fprintf(file, "temps: %f\n", horloge_simulation);

                if (evenement->type == VISITEUR_ARRIVE)
                {
                    fprintf(file, "Visiteur Arrive evenement\n");

                    if (evenement->visiteur == NULL)
                    {
                        perror("Visiteur arrive evenement pas de visiteur");
                        exit(EXIT_FAILURE);
                    }

                    // selection plus petite manege queue
                    ListeLiee *manege_queue = trouver_la_plus_petite_queue(maneges, nombre_de_maneges, nombre_de_visiteurs);

                    mettre_visiteur_dans_queue(manege_queue, evenement->visiteur);

                    fprintf(file, "Actuel manege queue longueur: %d\n", manege_queue->longueur);
                }
                else if (evenement->type == VISITEUR_DEPART)
                {
                    if (evenement->visiteur == NULL)
                    {
                        perror("Visiteur depart evenement pas de visiteur");
                        exit(EXIT_FAILURE);
                    }

                    temps_dans_le_parc[total_visiteur_ayant_fait_un_manege] = evenement->visiteur->heure_depart - evenement->visiteur->heure_arrive;
                    temps_total_dans_le_parc = temps_total_dans_le_parc + temps_dans_le_parc[total_visiteur_ayant_fait_un_manege];
                    temps_de_tour_total = temps_de_tour_total + evenement->visiteur->temps_de_visite;

                    float temps_attente = temps_dans_le_parc[total_visiteur_ayant_fait_un_manege] - evenement->visiteur->temps_de_visite;
                    if (temps_attente > temps_attente_max)
                    {
                        temps_attente_max = temps_attente;
                    }
                    total_visiteur_ayant_fait_un_manege++;

                    fprintf(file, "visiteur quitte le parc\n");
                    free(evenement);
                }
                else if (evenement->type == MANEGE_EVENEMENT)
                {
                    fprintf(file, "Manege evenement\n");

                    if (evenement->manege == NULL)
                    {
                        perror("Manege evenement n'a pas de manege manege");
                        exit(EXIT_FAILURE);
                    }

                    if (q_est_vide(evenement->manege->manege_queue))
                    {
                        int compt_queue_non_vide = 0;

                        for (int i = 0; i < nombre_de_maneges; i++)
                        {
                            if (maneges[i]->manege_queue->longueur != 0)
                            {
                                compt_queue_non_vide++;
                            }
                        }

                        if (compt_queue_non_vide == 0)
                        {
                            if (horloge_simulation < temps_de_simulation)
                            {
                                mettre_en_attente(evenement->manege, evenement_queue, horloge_simulation, file);
                            }
                        }
                        else
                        {
                            Visiteur *visiteur;
                            int n = (rand() % compt_queue_non_vide) + 1; // Nombre aléatoire entre 1 et compt_queue_non_vide
                            int j = 1;

                            for (int i = 0; i < nombre_de_maneges; i++)
                            {
                                if (maneges[i]->manege_queue->longueur != 0)
                                {
                                    if (j == n)
                                    {
                                        visiteur = trouver_visiteur_de_tete(maneges[i]->manege_queue);
                                        q_couper_tete_queue(maneges[i]->manege_queue);
                                    }
                                    j++;
                                }
                            }

                            tour_visiteur(evenement->manege, visiteur, evenement_queue, temps_de_tour_moyene, horloge_simulation, file);
                        }
                    }
                    else
                    {
                        Visiteur *visiteur = trouver_visiteur_de_tete(evenement->manege->manege_queue);
                        q_couper_tete_queue(evenement->manege->manege_queue);

                        tour_visiteur(evenement->manege, visiteur, evenement_queue, temps_de_tour_moyene, horloge_simulation, file);
                    }
                }
                else
                {
                    perror("Pas trouver de type d'evenement correspondant");
                    exit(EXIT_FAILURE);
                }

                fprintf(file, "-------------------------------\n");
            }

            /* Liberer les queues des maneges*/
            for (int i = 0; i < nombre_de_maneges; i++)
            {
                while (!q_est_vide(maneges[i]->manege_queue))
                {
                    q_couper_tete_queue(maneges[i]->manege_queue);
                }
                free(maneges[i]->manege_queue);
            }
        }

        /* Stats */
        float temps_moyen_passe_dans_le_parc = temps_total_dans_le_parc / total_visiteur_ayant_fait_un_manege;
        float sq_diff_temps_passe_d_parc = 0.0;

        for (int i = 0; i < total_visiteur_ayant_fait_un_manege; i++)
        {
            sq_diff_temps_passe_d_parc = sq_diff_temps_passe_d_parc + ((temps_dans_le_parc[i] - temps_moyen_passe_dans_le_parc) * (temps_dans_le_parc[i] - temps_moyen_passe_dans_le_parc));
        }

        float ecarttype_temps_passer_dans_parc = sqrtf(sq_diff_temps_passe_d_parc / total_visiteur_ayant_fait_un_manege);
        temps_moyen_passe_dans_le_parc_1 = temps_moyen_passe_dans_le_parc;

        if (mode == 2)
        {
            printf("------------Statistics-------------\n");

            printf("Nombre de visiteurs: %d\n", nombre_de_visiteurs);
            printf("Nombre de maneges: %d\n", nombre_de_maneges);
            printf("Temps de simulation: %f\n", temps_de_simulation);
            printf("Temps moyen d'un tour de manege: %f\n", temps_de_tour_moyene);

            printf("total visiteurs ayant fait un manege : %d\n", total_visiteur_ayant_fait_un_manege);
            printf("Temps total requis pour faire faire un tour a tous les visiteurs : %f\n", temps_de_tour_total);
            printf("Nombre de maneges : %d\n", nombre_de_maneges);

            if (sim_compt == 0)
            {
                printf("Type de queue : Simple\n");
            }
            else
            {
                printf("Type de queue : Multiple\n");
            }

            printf("Temps moyen passe dans le parc : %f\n", temps_moyen_passe_dans_le_parc);
            printf("Ecart type : %f\n", ecarttype_temps_passer_dans_parc);
            printf("Temps maximum d'attente entre l'arrive d'un visiteur et son premier tour de  manege : %f\n", temps_attente_max);
            printf("Quantité totale de temps de service et de temps d'inactivite de chaque manege:\n");
            for (int i = 0; i < nombre_de_maneges; i++)
            {
                printf("manege %d\t", i + 1);
                printf("temps de service: %f\t\t", maneges[i]->temps_de_tour_total);
                printf("temps d'inactivite: %f\n", maneges[i]->temps_attente_total);
            }

            printf("-------------- Simulation finie -------------\n");
            fprintf(file, "-------------- Simulation finie -------------\n");
        }
    }

    /* Free maneges */
    for (int i = 0; i < nombre_de_maneges; i++)
    {
        free(maneges[i]);
    }

    fclose(file);

    return temps_moyen_passe_dans_le_parc_1;
}

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        printf("Entrez tous les arguments\n");
        exit(EXIT_SUCCESS);
    }

    int nombre_de_visiteur = atoi(argv[1]);
    int nombre_de_manege = atoi(argv[2]);
    float temps_de_simulation = atof(argv[3]);
    float temps_de_service_moyen = atof(argv[4]);

    lancer_simulation(nombre_de_visiteur, nombre_de_manege, temps_de_simulation, temps_de_service_moyen, 2);

    FILE *fgp;
    fgp = fopen("output/plot.txt", "w");
    if (fgp == NULL)
    {
        perror("impossible d'ouvrir le fichier");
        exit(1);
    }

    for (int manege_compt = 1; manege_compt < nombre_de_manege; manege_compt++)
    {
        float avg_time = lancer_simulation(nombre_de_visiteur, manege_compt, temps_de_simulation, temps_de_service_moyen, 1);
        fprintf(fgp, "%d %f %0.2f\n", manege_compt, avg_time, avg_time);
    }

    fclose(fgp);

    /* Plot graph */
    FILE *pipe = popen("gnuplot -persist", "w");
    fprintf(pipe, "set terminal png\n");
    fprintf(pipe, "set output '%s'\n", "output/plot.png");
    fprintf(pipe, "set title 'Temps moyen qu un visiteur passe dans le parc versus le nombre de manege'\n");
    fprintf(pipe, "set xlabel 'manege'\n");
    fprintf(pipe, "set ylabel 'avg time (seconds)'\n");
    fprintf(pipe, "set style fill solid 1.0\n");
    fprintf(pipe, "%s\n", "set style data histograms");
    fprintf(pipe, "%s\n", "plot 'output/plot.txt' using 1:2 with linespoints notitle, '' using 1:2:3 with labels notitle");
    fclose(pipe);

    return 0;
}
