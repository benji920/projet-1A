#include <allegro.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define NIMAGE 9
#define NACTEUR 2
#define NSEQUENCE 2


typedef struct sequence
{
    char *nomSource; // nom du fichier image contenant la séquence
    int nimg;        // nombre d'images dans la séquence
    int tx,ty;       // largeur et hauteur des images de la séquence
    int ncol;        // nbr images cotes à cotes horizontalement dans le fichier image
    BITMAP **img;    // tableau de pointeurs pour indiquer les images
} t_sequence;

// données personnelles de chaque acteur qui se déplace
// sur cet exemple on ne gère que des déplacements horizontaux (pas de dy...)
typedef struct acteur
{
    // géométrie et déplacements

    int x,y;         // position du coin sup. gauche
    int dx;          // deplacement
    int tmpdx;       // ralentir déplacements en x (1 pour ne pas ralentir)
    int cptdx;       // compteur pour ralentir déplacement
    int tx,ty;       // largeur hauteur

    // séquence d'images de l'animation

    int imgcourante; // indice de l'image courante
    int tmpimg;      // ralentir séquence (image suivante 1 fois sur tmpimg)
    int cptimg;      // compteur pour ralentir séquence

    // type = numéro de la sequence à utiliser dans tabSequences
    // ( ici : 0 Dragon  1 Poisson  2 Crabe  3 Abeille  4 Moustique  5 Serpent )

    int type;

} t_acteur;

t_acteur * creerActeur(int type, int x, int y, int dx, int tmpdx, int tmpimg);

void menu();//affichage du menu et s�lection
void modedemploi();//affichage des r�gles
void reglage();//affichage des reglages
void jeux();//lancement du jeux
void jouer2();
void credit();
void remplirTabActeurs(t_acteur * tab[NACTEUR]);
void actualiserActeur(t_acteur *acteur);
void actualiserTabActeurs(t_acteur * tab[NACTEUR]);
void dessinerActeur(BITMAP *bmp, t_acteur *acteur);
void dessinerTabActeurs(BITMAP *bmp,t_acteur * tab[NACTEUR]);
void chargerSequence(t_sequence * seq);
void chargerTabSequences();

t_sequence tabSequences[NSEQUENCE] =
{
        //          nomSource           , nimg,  tx,  ty, ncol
        { "images/champignon/champignon.bmp" ,    9, 181,  150,    3 },
        { "zombiemarche/Walk .bmp"   ,    3,  101,  70,    3 }
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
    t_acteur * mesActeurs[NACTEUR];

    BITMAP *decor;
    BITMAP *page;

    int compteur=0;
    int piece=200;

    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    decor=load_bitmap("images/background.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }

    chargerTabSequences();

    remplirTabActeurs(mesActeurs);

    while (!key[KEY_ESC])
    {

        // 1)  EFFACER BUFFER, en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // 2) DETERMINER NOUVELLEs POSITIONs
        actualiserTabActeurs(mesActeurs);

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        dessinerTabActeurs(page,mesActeurs);

        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // 5) ON FAIT UNE PETITE PAUSE à chaque fois sinon ça va trop vite...
        rest(20);
    }
}


t_acteur * creerActeur(int type, int x, int y, int dx, int tmpdx, int tmpimg)
{
    // pointeur sur l'acteur qui sera créé (et retourné)
    t_acteur *acteur;

    // Création (allocation)
    acteur = (t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialisation géométrie et déplacement
    acteur->x=x;           acteur->y=y;
    acteur->dx=dx;
    acteur->tmpdx=tmpdx;
    acteur->cptdx=0;
    acteur->tx=tabSequences[type].tx;
    acteur->ty=tabSequences[type].ty;

    // Initialisation séquence d'images de l'animation
    acteur->imgcourante=0;
    acteur->tmpimg=tmpimg;
    acteur->cptimg=0;

    // numéro de séquence
    acteur->type=type;

    // on retourne cet acteur fraichement créé
    return acteur;
}
// Remplir un tableau avec des (pointeurs sur) acteurs créés
void remplirTabActeurs(t_acteur * tab[NACTEUR])
{
    int i;

    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau
    for (i=0;i<NACTEUR;i++)
    {
                  //      (type,   x,   y,  dx, tmpdx, tmpimg )
        tab[0]=creerActeur(   0, 500,   0,  -5,     1,      5 );
        tab[1]=creerActeur(   1, 300, 400,   0,     1,      8 );
    }
}


// Actualiser un acteur (bouger ...)
void actualiserActeur(t_acteur *acteur)
{

    // gestion des bords "à la pac man"
    // sur cet exemple seulement sur l'axe x (car pas de dy)
    if (acteur->x+acteur->tx < 0) acteur->x=SCREEN_W;
    if (acteur->x > SCREEN_W) acteur->x=-acteur->tx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement seulement une fois sur tmpdx
    // sur cet exemple seulement sur l'axe x (car pas de dy)
    acteur->cptdx++;
    if (acteur->cptdx >= acteur->tmpdx){
        acteur->cptdx=0;
        acteur->x = acteur->x + acteur->dx;
    }

    // gestion enchainement des images
    // incrémenter imgcourante une fois sur tmpimg
    acteur->cptimg++;
    if (acteur->cptimg >= acteur->tmpimg){
        acteur->cptimg=0;
        acteur->imgcourante++;
        // quand l'indice de l'image courante arrive à nimg de la séquence
        // on recommence la séquence à partir de 0
        if ( acteur->imgcourante >= tabSequences[ acteur->type ].nimg )
            acteur->imgcourante=0;
    }
}

// Gérer l'évolution de l'ensemble des acteurs
void actualiserTabActeurs(t_acteur * tab[NACTEUR])
{
    int i;

    for (i=0;i<NACTEUR;i++)
        actualiserActeur(tab[i]);
}


// Dessiner un acteur sur une bitmap bmp
void dessinerActeur(BITMAP *bmp, t_acteur *acteur)
{
    // Pointeur sur la séquence concernée (prise en compte du type de l'acteur)
    t_sequence *seq;
    seq=&tabSequences[ acteur->type ];

    //  Prise en compte du numéro d'image courante de l'acteur dans cette séquence
    draw_sprite(bmp, seq->img[ acteur->imgcourante ], acteur->x, acteur->y);
}

// Dessiner l'ensemble des acteurs sur une bitmap bmp
void dessinerTabActeurs(BITMAP *bmp,t_acteur * tab[NACTEUR])
{
    int i;

    for (i=0;i<NACTEUR;i++)
        dessinerActeur(bmp,tab[i]);
}


// Charger les images d'une séquence d'animation
// Découpe une image source en plusieurs vignettes
// (doivent être rangées de gauche à droite et de haut en bas)
void chargerSequence(t_sequence * seq)
{
    BITMAP *img[seq->nimg];// la bitmap qui charge l'image de séquence (temporairement)
    int i;           // indice de l'image dans la séquence
    int ix,iy;       // indices (horizontal et vertical) dans le "tableau" des images
    int sx,sy;         // coordonnées correspondantes (en pixels)
    char nomfichier[256];


    for (i=0;i<(seq->nimg);i++)
    {
         sprintf(nomfichier,seq->nomSource"%d",i);
        img[i]= load_bitmap(nomfichier,NULL);
        if (!img[i]){
            allegro_message(pas pu trouver "%s",nomfichier);
            exit(EXIT_FAILURE);
        }
        seq->img[i]=create_bitmap(seq->tx,seq->ty);
        sx=ix*seq->tx;
        sy=iy*seq->ty;

        }
}


// Charger toutes les séquences du tableau global tabSequence
void chargerTabSequences()
{
    int i;

    for (i=0;i<NSEQUENCE;i++)
        chargerSequence(&tabSequences[i]);
}
