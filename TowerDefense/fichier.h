#ifndef H_FICHIER
#define H_FICHIER
#include <allegro.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define NIMAGE 9
#define NACTEUR 20
#define NSEQUENCE 6

typedef struct acteur
{
    // coordonnée (du coin sup. gauche)
    int posx, posy;
    // vecteur deplacement
    int depx, depy;
    // tailles : horizontal/vertical
    int tx,ty;
    int comportement;
    int imgcourante;
    int tmpimg;
    int cptimg;
    int etat;
    int vie;
    int type;
} t_acteur;

typedef struct tour
{
    int postx, posty;
    int posfx, posfy;
    int tx,ty;
    int depfx;
    int etat;
    int etatf;
}t_tour;

typedef struct rondin
{
    int posx, posy;
    int tx,ty;
    int etat;
    int vie;

}t_rondin;

void menu();//affichage du menu et s�lection
void modedemploi();//affichage des r�gles
void reglage();//affichage des reglages
void jeux();//lancement du jeux
void jouer2();
void credit();
void remplirTabRondin(t_tour *tab[50]);
void actualiserrondins(t_rondin * mesRondins[50], BITMAP * page, BITMAP* rondin);
BITMAP *page;
BITMAP *mde;
BITMAP *img[NIMAGE];
BITMAP *img1[3];
BITMAP *decor;
BITMAP *decor2;
BITMAP *decor3;
BITMAP *tour;
BITMAP *fleche;
BITMAP *gameover;
BITMAP *reglages;
BITMAP *retour;
BITMAP *mde;
BITMAP *mde2;
BITMAP *imgorc1[7];
    BITMAP *imgorc2[7];
    BITMAP *imgorc3[7];
    BITMAP *rondin;
    BITMAP *victoire;


#endif // H_FICHIER
