#include <allegro.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define NIMAGE 9
#define NACTEUR 5
#define NSEQUENCE 6


void menu();//affichage du menu et s�lection
void modedemploi();//affichage des r�gles
void reglage();//affichage des reglages
void jeux();//lancement du jeux
void jouer2();

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
    int type;

    // comportement :   0 inertie     1 inertie + changements aléatoires
    //                  ( codes arbitraires : convention )
    int comportement;

    int imgcourante; // indice de l'image courante
    int tmpimg;      // ralentir séquence (image suivante 1 fois sur tmpimg)
    int cptimg;

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

/*
    towerdefense=load_bitmap("images/sprite1.bmp",NULL);
    if (!towerdefense)
    {
        allegro_message("pas pu trouver towerdefense.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(towerdefense,screen,0,0, (SCREEN_W-towerdefense->w)/2, (SCREEN_H-towerdefense->h)/2-100, towerdefense->w, towerdefense->h);
    draw_sprite(screen,towerdefense,(SCREEN_W-towerdefense->w)/2,0);

    mde=load_bitmap("images/sprite8.bmp",NULL);
    if (!mde)
    {
        allegro_message("pas pu trouver mde.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(mde,screen,0,0, (SCREEN_W-mde->w),0, mde->w, mde->h);
    draw_sprite(screen,mde,(SCREEN_W-towerdefense->w)/2-150,(SCREEN_H-towerdefense->h)/2+250);

    reglages=load_bitmap("images/sprite_reglages.bmp",NULL);
    if (!reglages)
    {
        allegro_message("pas pu trouver reglages.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(reglages,screen,0,0,0,0, reglages->w, reglages->h);
    draw_sprite(screen,reglages,(SCREEN_W-towerdefense->w)/2+200,(SCREEN_H-towerdefense->h)/2+100);

    quitter=load_bitmap("images/sprite5.bmp",NULL);
    if (!quitter)
    {
        allegro_message("pas pu trouver quitter.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(quitter,screen,0,0, (SCREEN_W-quitter->w),(SCREEN_H-quitter->h), quitter->w, quitter->h);
    draw_sprite(screen,quitter,(SCREEN_W-quitter->w),(SCREEN_H-quitter->h));

     credits=load_bitmap("images/spritecredits.bmp",NULL);
    if (!credits)
    {
        allegro_message("pas pu trouver towerdefense.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(towerdefense,screen,0,0, (SCREEN_W-towerdefense->w)/2, (SCREEN_H-towerdefense->h)/2-100, towerdefense->w, towerdefense->h);
    draw_sprite(screen,credits,(SCREEN_W-towerdefense->w)/2+200,(SCREEN_H-towerdefense->h)/2+250);

    jouer=load_bitmap("images/sprite2.bmp",NULL);
    if (!jouer)
    {
        allegro_message("pas pu trouver towerdefense.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(towerdefense,screen,0,0, (SCREEN_W-towerdefense->w)/2, (SCREEN_H-towerdefense->h)/2-100, towerdefense->w, towerdefense->h);
    draw_sprite(screen,jouer,(SCREEN_W-towerdefense->w)/2-150,(SCREEN_H-towerdefense->h)/2+100);
    */
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
        textprintf_ex(screen,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        blit(decor,page,0,0,0,0, SCREEN_W, SCREEN_H);

    if(mouse_x<=850 && mouse_x>=600 && mouse_y<=420 && mouse_y>=350)
    {
        draw_sprite(page,hachette,530,360);
    }

    if(mouse_x<=456 && mouse_x>=200 && mouse_y<=420 && mouse_y>=350)
    {
        draw_sprite(page,hachette,110,360);

    }


        if (mouse_b&1 && mouse_x>=200 && mouse_x<=456 && mouse_y>=350 && mouse_y<=420)
        {
            jouer2();
        }
        if (mouse_b&1 && mouse_x>=200 && mouse_x<=456 && mouse_y>=500 && mouse_y<=571)
        {
            modedemploi();
        }

        if (mouse_b&1 && mouse_x>=(SCREEN_W-quitter->w) && mouse_x<=(SCREEN_W+quitter->w) && mouse_y>=(SCREEN_H-quitter->h) && mouse_y<=(SCREEN_H+quitter->h))
        {
            ;
        }

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        rest(20);
    }
}

void modedemploi()
{
    BITMAP *mde;
    BITMAP *retour;
    BITMAP *decor;

    clear(screen);

    decor=load_bitmap("images/decor31.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }
    blit(decor,screen,0,0, (SCREEN_W-decor->w)/2, (SCREEN_H-decor->h)/2, decor->w, decor->h);

    mde=load_bitmap("images/mde.bmp",NULL);
    if (!mde)
    {
        allegro_message("pas pu trouver mde.bmp");
        exit(EXIT_FAILURE);
    }
    blit(mde,screen,0,0, (SCREEN_W-mde->w)/2,0, mde->w, mde->h);

    retour=load_bitmap("images/retour.bmp",NULL);
    if (!mde)
    {
        allegro_message("pas pu trouver retour.bmp");
        exit(EXIT_FAILURE);
    }
    blit(retour,screen,0,0, (SCREEN_W-retour->w),(SCREEN_H-retour->h), retour->w, retour->h);

    while ( !key[KEY_ESC] )
    {
        if (mouse_b&1 && mouse_x>=(SCREEN_W-retour->w) && mouse_x<=(SCREEN_W+retour->w) && mouse_y>=(SCREEN_H-retour->h) && mouse_y<=(SCREEN_H+retour->h))
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
        if (mouse_b&1 && mouse_x>=(SCREEN_W-retour->w) && mouse_x<=(SCREEN_W+retour->w) && mouse_y>=(SCREEN_H-retour->h) && mouse_y<=(SCREEN_H+retour->h))
        {
            menu();
        }
    }
}

void jeux()
{

    // LES INFORMATIONS SUIVANTES VONT ALLER DANS UNE STRUCTURE ACTEUR
    //   ( pour pouvoir gérer plusieurs sprites animés )

    // Données géométriques de l'animation
    int x,y;
    int dx,dy;
    int tx,ty;

    // Pour pouvoir avancer très lentement on avance moins souvent
    //  ( ajouter dx une fois tous les tmpdx, initialement à chaque fois )
    int cptdx=0, tmpdx=1;

    // Gestion de l'enchainement des images de la séquence
    // indice de l'image courante
    int imgcourante=0;
    // on passe à l'image suivante une fois tous les tmpimg
    int cptimg=0, tmpimg=4;

    // Séquence d'animation
    BITMAP *img[NIMAGE];



    // AUTRES VARIABLES NE CONCERNANT PAS SPECIFIQUEMENT LE CHAT

    // BITMAP servant de buffer d'affichage (double buffer)

    // Image de fond
    BITMAP *decor;

    // La tempo générale (fonction rest) sera réglable
    int tempoglobale=10;

    // Pour charger la séquence
    int i;
    char nomfichier[256];


    // Lancer allegro et le mode graphique


    // charger image de fond
    decor=load_bitmap("images/decor1.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver images/decor1.bmp");
        exit(EXIT_FAILURE);
    }

    // charger les images de la séquence d'animation
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

    // initialisation des données du chat

    tx = img[0]->w; // pour la taille on se base sur la 1ère image de la séquence
    ty = img[0]->h;
    x = 0;
    y = SCREEN_H-2*ty;
    dx = 5;
    dy = 0;

    cptdx=0;
    tmpdx=1;

    imgcourante=0;
    cptimg=0;
    tmpimg=5;


    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {
        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // appel d'un sous programme de réglage interactif des parametres
        // ( seulement utile sur cet exemple ou pour du debug )


        // gestion déplacement du chat
        if ( (x<0 && dx<0) || (x+tx>SCREEN_W && dx>0) )
            dx = -dx;

        cptdx++;
        if (cptdx>=tmpdx){
            cptdx=0;
            x+=dx;
        }

        y+=dy;

        // gestion enchainement des images
        // incrémenter imgcourante une fois sur tmpimg
        cptimg++;
        if (cptimg>=tmpimg){
            cptimg=0;

            imgcourante++;

            // quand l'indice de l'image courante arrive à NIMAGE
            // on recommence la séquence à partir de 0



        // affichage du buffer à l'écrane


        // la petite pause...
        rest(tempoglobale);
    }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jouer2()
{
  // Le tableau regroupant tous les acteurs
    // c'est un tableau de pointeurs sur structures t_acteurs
    t_acteur * mesActeurs[NACTEUR];
    int compteur;
    t_acteur* acteur[100];
    // BITMAP servant de buffer d'affichage (double buffer)
    BITMAP *page;
    BITMAP *img[NIMAGE];
 int i;
    char nomfichier[256];

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


    remplirTabActeurs(mesActeurs);


    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {


        // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)
        clear_bitmap(page);

         // 2) DETERMINER NOUVELLEs POSITIONs
        actualiserTabActeurs(mesActeurs);

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        dessinerTabActeurs(page,mesActeurs,img);

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

    // Création (allocation)
    acteur = (t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialisation
    acteur->imgcourante=0;

    acteur->tx = rand()%40+40;
    acteur->ty = rand()%40+40;

    // Position aléatoire (on tient compte de la taille...)
    acteur->posx = 1050;
    acteur->posy = rand()%(SCREEN_H - acteur->ty);

    // Vitesse aléatoire symétrique
    // avec composantes horizontales et verticales non nulles

        acteur->depx = -3;
        acteur->depy = 0;


    // Type au hasard 0, 1, 2
    acteur->type = 0;

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


// Dessiner un acteur sur une bitmap bmp
void dessinerActeur(BITMAP *bmp, t_acteur *acteur)
{


            rectfill(bmp,acteur->posx,acteur->posy,acteur->posx+acteur->tx,acteur->posy+acteur->ty,acteur->couleur);






}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerTabActeurs(BITMAP *bmp,t_acteur * tab[NACTEUR])
{
    int i;

    for (i=0;i<NACTEUR;i++)
        dessinerActeur(bmp,tab[i]);

}

