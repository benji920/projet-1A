#include <allegro.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define NIMAGE 9
#define NACTEUR 30
#define NSEQUENCE 6


void menu();//affichage du menu et s�lection
void modedemploi();//affichage des r�gles
void reglage();//affichage des reglages
void jeux();//lancement du jeux
void jouer2();
void credit();



typedef struct sequence
{
    char *nomSource; // nom du fichier image contenant la séquence
    int nimg;        // nombre d'images dans la séquence
    int tx,ty;       // largeur et hauteur des images de la séquence
    int ncol;        // nbr images cotes à cotes horizontalement dans le fichier image
    BITMAP **img;    // tableau de pointeurs pour indiquer les images
} t_sequence;

typedef struct acteur
{
    // coordonnée (du coin sup. gauche)
    int posx, posy;

    // vecteur deplacement
    int depx, depy;

    // tailles : horizontal/vertical
    int tx,ty;

    // couleur de l'élément graphique
    int couleur;

    // type :   0 rectangle   1 ellipse   2 triangle
    //          ( codes arbitraires : convention )


    // comportement :   0 inertie     1 inertie + changements aléatoires
    //                  ( codes arbitraires : convention )
    int comportement;

    int imgcourante; // indice de l'image courante
    int tmpimg;      // ralentir séquence (image suivante 1 fois sur tmpimg)
    int cptimg;

    int etat;

    int type;

} t_acteur;

t_sequence tabSequences[NSEQUENCE] =
{
        //          nomSource           , nimg,  tx,  ty, ncol
        { "images/dragon/dragon.bmp"    ,    6, 128,  64,    3 },
        { "images/dragon/poisson.bmp"   ,    3,  64,  32,    3 },
        { "images/dragon/crabe.bmp"     ,    4,  64,  32,    4 },
        { "images/dragon/abeille.bmp"   ,    6,  50,  40,    6 },
        { "images/dragon/moustique.bmp" ,    6,  50,  40,    6 },
        { "images/dragon/serpent.bmp"   ,    7, 100,  50,    4 }
};



int main()
{

    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();
    BITMAP *page;
    SAMPLE *sample;

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


sample=load_wav("son1.wav");
install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    show_mouse(screen);

    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);


play_sample(sample,100,100,1000,0);

    while ( !key[KEY_ESC] )
    {
    menu();
    }

    return 0;
}
END_OF_MAIN();

void menu()
{
    BITMAP *towerdefense;
    BITMAP *hachette;
    BITMAP *decor;
    BITMAP *mde;
    BITMAP *reglages;
    BITMAP *quitter;
    BITMAP *credits;
    BITMAP *jouer;
    BITMAP *page;
    BITMAP *img[NIMAGE];

       char nomfichier[256];
       int i;


    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear(page);


    decor=load_bitmap("images/decor31.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }


    hachette=load_bitmap("images/hachette.bmp",NULL);
    if (!hachette)
    {
        allegro_message("pas pu trouver hachette.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(towerdefense,screen,0,0, (SCREEN_W-towerdefense->w)/2, (SCREEN_H-towerdefense->h)/2-100, towerdefense->w, towerdefense->h);
    //draw_sprite(screen,hachette,100,200);




    while ( !key[KEY_ESC] )
    {


        blit(decor,page,0,0,0,0, SCREEN_W, SCREEN_H);
        textprintf_ex(page,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);

    if(mouse_x<=850 && mouse_x>=600 && mouse_y<=420 && mouse_y>=350)
    {
        draw_sprite(page,hachette,530,360);
    }

    if(mouse_x<=456 && mouse_x>=200 && mouse_y<=420 && mouse_y>=350)
    {
        draw_sprite(page,hachette,110,360);

    }
    if(mouse_x<=456 && mouse_x>=200 && mouse_y<=570 && mouse_y>=500)
    {
        draw_sprite(page,hachette,110,510);
    }
    if(mouse_x<=880 && mouse_x>=600 && mouse_y<=570 && mouse_y>=500)
    {
        draw_sprite(page,hachette,530,510);
    }
        if (mouse_b&1 && mouse_x>=200 && mouse_x<=456 && mouse_y>=350 && mouse_y<=420)
        {
            jouer2();
        }
        if (mouse_b&1 && mouse_x>=200 && mouse_x<=456 && mouse_y>=500 && mouse_y<=571)
        {
            modedemploi();
        }

        if (mouse_b&1 && mouse_x>=385 && mouse_x<=863 && mouse_y>=350 && mouse_y<=420)
        {
            credit();
        }

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        rest(20);
    }
}
void credit()
{
    BITMAP *mde;
    BITMAP *retour;
    BITMAP *decor;

    clear(screen);


    mde=load_bitmap("images/credits2.bmp",NULL);
    if (!mde)
    {
        allegro_message("pas pu trouver mde.bmp");
        exit(EXIT_FAILURE);
    }
    blit(mde,screen,0,0, (SCREEN_W-mde->w)/2,0, mde->w, mde->h);


    while ( !key[KEY_ESC] )
    {
        textprintf_ex(screen,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        if (mouse_b&1 && mouse_x>=822 && mouse_x<=973 && mouse_y>=651 && mouse_y<=757)
        {
            menu();
        }
    }
}
void modedemploi()
{
    BITMAP *mde;
    BITMAP *retour;
    BITMAP *decor;

    clear(screen);


    mde=load_bitmap("images/mde.bmp",NULL);
    if (!mde)
    {
        allegro_message("pas pu trouver mde.bmp");
        exit(EXIT_FAILURE);
    }
    blit(mde,screen,0,0, (SCREEN_W-mde->w)/2,0, mde->w, mde->h);


    while ( !key[KEY_ESC] )
    {
        textprintf_ex(screen,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        if (mouse_b&1 && mouse_x>=822 && mouse_x<=973 && mouse_y>=651 && mouse_y<=757)
        {
            menu();
        }
    }
}

void reglage()
{
    BITMAP *reglages;
    BITMAP *retour;
    BITMAP *decor;

    clear(screen);

    decor=load_bitmap("images/decor.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }
    blit(decor,screen,0,0, (SCREEN_W-decor->w)/2, (SCREEN_H-decor->h)/2, decor->w, decor->h);

    reglages=load_bitmap("images/reglages.bmp",NULL);
    if (!reglages)
    {
        allegro_message("pas pu trouver reglages.bmp");
        exit(EXIT_FAILURE);
    }
    blit(reglages,screen,0,0, (SCREEN_W-reglages->w)/2,0, reglages->w, reglages->h);

    retour=load_bitmap("images/retour.bmp",NULL);
    if (!reglages)
    {
        allegro_message("pas pu trouver retour.bmp");
        exit(EXIT_FAILURE);
    }
    blit(retour,screen,0,0, (SCREEN_W-retour->w),(SCREEN_H-retour->h), retour->w, retour->h);

    while ( !key[KEY_ESC] )
    {
        textprintf_ex(screen,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        if (mouse_b&1 && mouse_x>=(SCREEN_W-retour->w) && mouse_x<=(SCREEN_W+retour->w) && mouse_y>=(SCREEN_H-retour->h) && mouse_y<=(SCREEN_H+retour->h))
        {
            menu();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jouer2()
{
  // Le tableau regroupant tous les acteurs
    // c'est un tableau de pointeurs sur structures t_acteurs
    t_acteur * mesActeurs[50];
    int *compteur=20;
    int piece=200;
    int x,y;
    int etattda=0;
    int v;
    int compt;//nb de tda
    int f; //coordonée fléche
    int df=20;//vitesse déplacement fleche
    // BITMAP servant de buffer d'affichage (double buffer)
    BITMAP *page;
    BITMAP *img[NIMAGE];
    BITMAP *img1[NIMAGE];
    BITMAP *decor;
    BITMAP *tda;
    BITMAP *fleche;
    int i=0;
    char nomfichier[256];
    //for(i=0;i<50;i++)
    //  mesActeurs[i]=NULL;
    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

        tda=load_bitmap("images/tower2.bmp",NULL);
        if (!tda)
        {
        allegro_message("images/tower2.bmp");
        exit(EXIT_FAILURE);
        }

        fleche=load_bitmap("images/fleche.bmp",NULL);
        if (!tda)
        {
        allegro_message("images/fleche.bmp");
        exit(EXIT_FAILURE);
        }

    for (i=0;i<NIMAGE;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"zombiemarche/Walk (%d).bmp",i);

        img[i] = load_bitmap(nomfichier,NULL);
        if (!img[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }
    for (i=0;i<3;i++)
    {
        img1[i] = load_bitmap("champignon%d.bmp",i);
        if (!img[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }

    decor=load_bitmap("images/background.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }

    int imgcourante=0;

    int cptimg=0, tmpimg=4;
    remplirTabActeurs(mesActeurs);

    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {
        // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)
        clear_bitmap(page);
        blit(decor,page,0,0,0,0, SCREEN_W, SCREEN_H);

        textprintf_ex(page,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        textprintf_ex(page,font,100,100,makecol(255,255,255),-1,"vos pieces : %d",piece);

         // 2) DETERMINER NOUVELLEs POSITIONs
        actualiserTabActeurs(mesActeurs);


        if(etattda==0)
        {
            x=-30;
            y=-30;
            masked_blit(tda,page,0,0,x,y, tda->w, tda->h);
        }

        if((mouse_b&1)&& mouse_x>=x+30 && mouse_x<=x+140 && mouse_y>=y+30 && mouse_y<=y+190 &&piece>150)
        {
            etattda=1;
            piece=piece-150;
        }

        if(etattda==1)
        {
            if(mouse_b&1 && mouse_x>=x+30 && mouse_x<=x+140 && mouse_y>=y+30 && mouse_y<=y+190)
            {
                x = mouse_x-90;
                y = mouse_y-70;
                f = mouse_x;
            }
            masked_blit(tda,page,0,0,x,y, tda->w, tda->h);
            masked_blit(fleche,page,0,0,f+110,y+43,fleche->w,fleche->h);
            f=f+df;
            if(f>SCREEN_W)
            {
            f=x;
            }
        }

        compt=piece/50;

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
       //dessinerTabActeurs(page,mesActeurs,img);

          /* cptimg++;
        if (cptimg>=tmpimg){
            cptimg=0;

            imgcourante++;

            // quand l'indice de l'image courante arrive à NIMAGE
            // on recommence la séquence à partir de 0
            if (imgcourante>=NIMAGE)
                imgcourante=0;
        }
*/


    for (i=0;i<10;i++)
    {
if(mesActeurs[i]!=NULL)
        {
        mesActeurs[i]->cptimg++;
        if (mesActeurs[i]->cptimg>=mesActeurs[i]->tmpimg){
            mesActeurs[i]->cptimg=0;

            mesActeurs[i]->imgcourante++;

            // quand l'indice de l'image courante arrive à NIMAGE
            // on recommence la séquence à partir de 0
            if (mesActeurs[i]->imgcourante>=NIMAGE)
                mesActeurs[i]->imgcourante=0;
        }

        draw_sprite(page,img[mesActeurs[i]->imgcourante], mesActeurs[i]->posx,mesActeurs[i]->posy);

        }
    }

    if(mouse_b&1)
     {

     }


    /*    mesActeurs[20]=creerActeur();
            mesActeurs[20]->posx=x;
            mesActeurs[20]->posy=y;
            compteur++;*/
        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // 5) ON FAIT UNE PETITE PAUSE à chaque fois sinon ça va trop vite...
        rest(20);
    }

    return 0;
}

// Allouer et initialiser (aléatoirement) un acteur
t_acteur * creerActeur()
{
    // pointeur sur l'acteur qui sera créé (et retourné)
    t_acteur *acteur;
    acteur->imgcourante=0;
    acteur->cptimg=0;
    acteur->tmpimg=4;

    acteur->etat=1;

    // Création (allocation)
    acteur = (t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialisation
    acteur->imgcourante=0;

    acteur->tx = rand()%40+40;
    acteur->ty = rand()%40+40;

    // Position aléatoire (on tient compte de la taille...)
    acteur->posx = 1050+rand()%(2500-1050+1);
    acteur->posy = 1+rand()%(3);
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

    // Vitesse aléatoire symétrique
    // avec composantes horizontales et verticales non nulles

        acteur->depx = -3;
        acteur->depy = 0;

    // Comportement au hasard (0 ou 1)
    acteur->comportement = 0;

    // Pour mieux visualiser on associe 2 domiantes couleurs distinctes
    // aux 2 comportement (mais ce n'est pas obligé)
    if ( acteur->comportement == 0 )
        acteur->couleur = makecol(rand()%64+196,rand()%40+40,rand()%40+40);
    else
        acteur->couleur = makecol(rand()%40+40,rand()%64+196,rand()%40+40);

    // on retourne cet acteur fraichement créé
    // ( en fait on retourne le POINTEUR sur lui )
    return acteur;
}

// Remplir un tableau avec des (pointeurs sur) acteurs créés
void remplirTabActeurs(t_acteur * tab[NACTEUR])
{
    int i;

    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau
    for (i=0;i<NACTEUR;i++)
        tab[i]=creerActeur();
}



// Actualiser un acteur (bouger ...)
void actualiserActeur(t_acteur *acteur)
{

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    acteur->posx = acteur->posx + acteur->depx;
    acteur->posy = acteur->posy + acteur->depy;
}

// Gérer l'évolution de l'ensemble des acteurs
void actualiserTabActeurs(t_acteur * tab[NACTEUR])
{
    int i;

    for (i=0;i<NACTEUR;i++)
        actualiserActeur(tab[i]);


}

