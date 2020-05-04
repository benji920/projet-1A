#include "fichier.h"

// Actualiser un acteur (bouger ...)
void actualiserActeur(t_acteur *acteur)
{

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    acteur->posx = acteur->posx + acteur->depx;
    acteur->posy = acteur->posy + acteur->depy;
}

// Gérer l'évolution de l'ensemble des acteurs
void actualiserTabActeurs(t_acteur * tab[50])
{
    int i;

    for (i=0;i<50;i++)
        actualiserActeur(tab[i]);


}

void actualisertour(t_tour * mesTours[50], BITMAP * page, BITMAP* tour, BITMAP *fleche)
{
int i;

    for (i=0;i<50;i++)
        {


            if(mesTours[i]->etat==1)
            {
            draw_sprite(page,tour, mesTours[i]->postx,mesTours[i]->posty);
            draw_sprite(page,fleche, mesTours[i]->posfx,mesTours[i]->posty+70);
            mesTours[i]->posfx=mesTours[i]->posfx + mesTours[i]->depfx;
            if(mesTours[i]->posfx>SCREEN_W)
                {
                mesTours[i]->posfx=mesTours[i]->postx;
                }
            }
        }
}

void actualiserrondins(t_rondin * mesRondins[50], BITMAP * page, BITMAP* rondin)
{
int i;

    for (i=0;i<50;i++)
        {


            if(mesRondins[i]->etat==1)
            {
            draw_sprite(page,rondin, mesRondins[i]->posx,mesRondins[i]->posy);
            textprintf_ex(page,font,mesRondins[i]->posx+5,mesRondins[i]->posy-5,makecol(255,255,255),-1,"vie : %d",mesRondins[i]->vie);


            }
        }
}
