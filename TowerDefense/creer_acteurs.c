#include "fichier.h"
// Allouer un acteur
t_acteur * creerActeur()
{
    // pointeur sur l'acteur qui sera créé (et retourné)
    t_acteur *acteur;
    acteur->imgcourante=0;
    acteur->cptimg=0;
    acteur->tmpimg=4;

    acteur->etat=0;

    // Création (allocation)
    acteur = (t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialisation
    acteur->imgcourante=0;
    acteur->tx = rand()%40+40;
    acteur->ty = rand()%40+40;



    acteur->posy = 1+rand()%(3);
    if(acteur->posy==1)
    {
        acteur->posy=170;
    }
    if(acteur->posy==2)
    {
        acteur->posy=310;
    }
    if(acteur->posy==3)
    {
        acteur->posy=445;
    }

        acteur->depx=-1.8;
        acteur->depy=0;

        acteur->vie=200;

       acteur->type=1+rand()%(3-1+1);


    return acteur;
}


t_acteur * creerActeur1()
{
    // pointeur sur l'acteur qui sera créé (et retourné)
    t_acteur *acteur;
    acteur->imgcourante=0;
    acteur->cptimg=0;
    acteur->tmpimg=4;

    acteur->etat=0;

    // Création (allocation)
    acteur = (t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialisation
    acteur->imgcourante=0;

    acteur->tx = rand()%40+40;
    acteur->ty = rand()%40+40;


    acteur->posx = 100;
    acteur->posy = 1+rand()%(3);//position aléatire sur l'un des trois axes horizontaux
    if(acteur->posy==1)
    {
        acteur->posy=190;
    }
    if(acteur->posy==2)
    {
        acteur->posy=310;
    }
    if(acteur->posy==3)
    {
        acteur->posy=440;
    }

        acteur->depx = -3;
        acteur->depy = 0;



    return acteur;
}

t_tour * creerTour()
{
    // pointeur sur l'acteur qui sera créé (et retourné)
    t_tour * tour;

    tour->etat=0;

    // Création (allocation)
    tour = (t_tour *)malloc(1*sizeof(t_tour));

    tour->tx = rand()%40+40;
    tour->ty = rand()%40+40;
    tour->depfx = 3;
    tour->etatf=1;

    return tour;
}

t_rondin * creerRondin()
{
    // pointeur sur l'acteur qui sera créé (et retourné)
    t_rondin * rondin;

    rondin->etat=0;

    // Création (allocation)
    rondin = (t_rondin *)malloc(1*sizeof(t_rondin));

    rondin->tx = rand()%40+40;
    rondin->ty = rand()%40+40;

    rondin->vie=200;


    return rondin;
}
