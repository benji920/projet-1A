#include "fichier.h"

void InitialiserEnnemies(t_acteur *tab[50],int *ennemies1, int *ennemies2,int *ennemies3)
{
    int i;
    for(i=0;i<*ennemies1;i++)
    {
        tab[i]->etat=1;
        if(tab[i]->type==1)
        {
            tab[i]->posx=1050+rand()%(1500-1050+1);//position pour vagye 1
        }
        if(tab[i]->type==2)
            {tab[i]->vie=300;
            tab[i]->depx=-1.5;
            tab[i]->posx=2100+rand()%(2500-2100+1);}//position pour vagye 2
        if(tab[i]->type==3)
            {tab[i]->vie=400;
            tab[i]->depx=-1.2;
            tab[i]->posx=3500+rand()%(4000-3500+1);}//position pour vague 3
    }

}
