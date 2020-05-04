#include "fichier.h"



void collision(t_acteur *champi[50], t_acteur *zombi[50])
{
int i,j;
for(j=0;j<50;j++)
{
    for(i=0;i<50;i++)
    {
        if(zombi[i]->posx+30<=champi[j]->posx)
        {
            if(champi[j]->posy<=zombi[i]->posy+140 && champi[j]->posy>=zombi[i]->posy-20)
               {

                if(champi[j]->etat==1 && zombi[i]->etat==1)//si les deux acteurs sont en vie
                champi[j]->etat=0;
                }
        }

    }
}
}

void collision2(t_tour *tour[50], t_acteur *zombi[50], int *cmtfleche, int *tmpfleche)
{
int i,j;
for(j=0;j<50;j++)
{
    for(i=0;i<50;i++)
    {
        if(zombi[i]->posx<=tour[j]->posfx)
        {
          if(zombi[i]->posy>=tour[j]->posfy-100 && zombi[i]->posy<=tour[j]->posfy+80)
            {
                if(zombi[i]->etat==1 && tour[j]->etat==1)
                {
                if(tour[j]->etatf==1)
                {tour[j]->posfx=tour[j]->postx;
                zombi[i]->vie=zombi[i]->vie-100;}

                if(*cmtfleche<*tmpfleche)
                tour[j]->depfx=0;



                }
            }

        }

    }
}
}

void collision3(t_rondin *rondin[50], t_acteur *zombi[50])
{
    int i,j;
for(j=0;j<50;j++)
{
    for(i=0;i<50;i++)
    {
        if(zombi[i]->posx<=rondin[j]->posx)
        {
          if(zombi[i]->posy>=rondin[j]->posy-100 && zombi[i]->posy<=rondin[j]->posy+80)
            {
                if(zombi[i]->etat==1 && rondin[j]->etat==1)
                {
                zombi[i]->depx=0;
                zombi[i]->vie=zombi[i]->vie-0.5;
                rondin[j]->vie=rondin[j]->vie-2;
                }
                if(zombi[i]->etat==1 && rondin[j]->etat==0)
                   {
                    if(zombi[i]->type==1)
                    zombi[i]->depx=-1.8;
                    if(zombi[i]->type==2)
                    zombi[i]->depx=-1.5;
                    if(zombi[i]->type==3)
                    zombi[i]->depx=-1.2;}


            }

        }

    }
}
}
