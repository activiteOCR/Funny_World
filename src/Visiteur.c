#include "Visiteur.h"
#include <stdlib.h>

Visiteur *nouveau_visiteur(float heure_arrive)
{
    Visiteur *visiteur = malloc(sizeof(Visiteur));
    visiteur->heure_arrive = heure_arrive;

    return visiteur;
}
