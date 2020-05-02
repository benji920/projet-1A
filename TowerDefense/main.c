#include "fichier.h"

typedef struct tour
{
    int postx, posty;
    int posfx, posfy;
    int tx,ty;
    int depfx;
    int etat;
}t_tour;

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

typedef struct sequence
{
    char *nomSource; // nom du fichier image contenant la séquence
    int nimg;        // nombre d'images dans la séquence
    int tx,ty;       // largeur et hauteur des images de la séquence
    int ncol;        // nbr images cotes à cotes horizontalement dans le fichier image
    BITMAP **img;    // tableau de pointeurs pour indiquer les images
} t_sequence;

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

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);


    while ( !key[KEY_ESC] )
    {
    menu();
    }

    return 0;
}
END_OF_MAIN();

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
    t_acteur * mesActeurs1[50];
    t_tour * mesTours[50];
    int compteur=0;
    int compteurTour=0;
    int piece=500;
    int *pointeurpiece=&piece;
    // BITMAP servant de buffer d'affichage (double buffer)
    BITMAP *page;
    BITMAP *img[NIMAGE];
    BITMAP *img1[NIMAGE];
    BITMAP *decor;
    BITMAP *tour;
    BITMAP *fleche;
    int i=0;
    char nomfichier[256];
    int x=30;
    int y=30;
    int u;

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

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
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"champignon%d.bmp",i);

        img1[i] = load_bitmap(nomfichier,NULL);
        if (!img1[i]){
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

    fleche=load_bitmap("images/fleche.bmp",NULL);
    if (!fleche)
    {
        allegro_message("pas pu trouver fleche.bmp");
        exit(EXIT_FAILURE);
    }

    tour=load_bitmap("images/tour.bmp",NULL);
    if (!tour)
    {
        allegro_message("pas pu trouver tour.bmp");
        exit(EXIT_FAILURE);
    }

    int imgcourante=0;
    int cptimg=0, tmpimg=4;

    int imgcourante1=0;
    int cptimg1=0, tmpimg1=150;

    int *imgcourante2=0;
    int *cptimg2=0, *tmpimg2=150;

    remplirTabActeurs(mesActeurs);
    remplirTabActeurs1(mesActeurs1);
    remplirTabTour(mesTours);

    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {
        // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)

        clear_bitmap(page);
        blit(decor,page,0,0,0,0, SCREEN_W, SCREEN_H);

        textprintf_ex(page,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        textprintf_ex(page,font,850,20,makecol(255,255,255),-1,"vos pieces : %d",piece);

         // 2) DETERMINER NOUVELLEs POSITIONs
        actualiserTabActeurs(mesActeurs);
       // actualiserTabActeurs(mesActeurs1);

        cptimg++;

        if (cptimg>=tmpimg){
            cptimg=0;
            imgcourante++;
            if (imgcourante>=NIMAGE)
                imgcourante=0;
        }
        for (i=0;i<10;i++)
        {
            if(mesActeurs[i]->etat==1)
            {
            draw_sprite(page,img[imgcourante], mesActeurs[i]->posx,mesActeurs[i]->posy);
            }
        }

        masked_blit(img1[2],page,0,0,x,y, img1[2]->w, img1[2]->h);
        masked_blit(tour,page,0,0,150,0, tour->w, tour->h);

        if(!(mouse_b&1))
        u=0;

        if(mouse_b&1 && u==0 && mouse_x>=0 && mouse_x<=120 && mouse_y>=0 && mouse_y<=130 )
        {
            mesActeurs1[compteur]->etat=1;
            draw_sprite(page,img1[imgcourante1], mouse_x,mouse_y);
            compteur++;
            argent(pointeurpiece);
            u=1;
        }

        if(mouse_b&1 && u==0 && mouse_x>=150 && mouse_x<=250 && mouse_y>=0 && mouse_y<=220 )
        {
            mesTours[compteurTour]->etat=1;
            draw_sprite(page,tour, mouse_x,mouse_y);
            compteurTour++;
            argent(pointeurpiece);
            u=2;
        }

        if (mouse_b&1 && u==2)
        {
            mesTours[compteurTour-1]->postx = mouse_x;
            mesTours[compteurTour-1]->posty = mouse_y;
            mesTours[compteurTour-1]->posfx = mouse_x;
        }

        if (mouse_b&1 && u==1 )
        {
            mesActeurs1[compteur-1]->posx = mouse_x;
            mesActeurs1[compteur-1]->posy = mouse_y;
        }
        cptimg1++;

        if (cptimg1>=tmpimg1)
        {
            cptimg1=0;
            imgcourante1++;
            if (imgcourante1>=2)
            imgcourante1=0;
        }

        for (i=0;i<20;i++)
        {
            if(mesActeurs1[i]->etat==1)
            {
            draw_sprite(page,img1[imgcourante1], mesActeurs1[i]->posx,mesActeurs1[i]->posy);
            }
        }

        for (i=0;i<20;i++)
        {
            if(mesTours[i]->etat==1)
            {
            draw_sprite(page,tour, mesTours[i]->postx,mesTours[i]->posty);
            draw_sprite(page,fleche, mesTours[i]->posfx,mesTours[i]->posty);
            mesTours[i]->posfx=mesTours[i]->posfx + mesTours[i]->depfx;
            if(mesTours[i]->posfx>SCREEN_W)
                {
                mesTours[i]->posfx=mesTours[i]->postx;
                }
            }
        }

        textprintf_ex(page,font,100,300,makecol(0,255,0),makecol(0,0,0),"%d",compteur);

        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // 5) ON FAIT UNE PETITE PAUSE à chaque fois sinon ça va trop vite...
        rest(20);
    }

    return 0;
}

void argent(int *pointeurpiece)
{
    *pointeurpiece=*pointeurpiece-50;
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
void remplirTabActeurs(t_acteur * tab[50])
{
    int i;

    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau
    for (i=0;i<50;i++)
        tab[i]=creerActeur();
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

    // Position aléatoire (on tient compte de la taille...)
    acteur->posx = 100;
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

void remplirTabActeurs1(t_acteur * tab[50])
{
    int i;

    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau
    for (i=0;i<50;i++)
        tab[i]=creerActeur1();
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

t_tour * creerTour()
{
    // pointeur sur l'acteur qui sera créé (et retourné)
    t_tour * tour;

    tour->etat=0;

    // Création (allocation)
    tour = (t_tour *)malloc(1*sizeof(t_tour));

    tour->tx = rand()%40+40;
    tour->ty = rand()%40+40;

    // Position aléatoire (on tient compte de la taille...
    tour->depfx = 15;

    return tour;
}

void remplirTabTour(t_tour *tab[50])
{
    int i;
    for (i=0;i<50;i++)
        tab[i]=creerTour();
}









