#include "fichier.h"
//remplir le tableau de zombies
void remplirTabActeurs(t_acteur * tab[50])
{
    int i;

    // On "accroche" 50 nouveaux acteurs
    // à chaque case du tableau
    for (i=0;i<50;i++)
        tab[i]=creerActeur();
}
//remplir le tableau de champignons
void remplirTabActeurs1(t_acteur * tab[50])
{
    int i;

    // On "accroche" 50 nouveaux acteurs
    // à chaque case du tableau
    for (i=0;i<50;i++)
        tab[i]=creerActeur1();
}

void remplirTabTour(t_tour *tab[50])
{
    int i;
    for (i=0;i<50;i++)
        tab[i]=creerTour();
}

void remplirTabRondin(t_tour *tab[50])
{
    int i;
    for (i=0;i<50;i++)
        tab[i]=creerRondin();
}
