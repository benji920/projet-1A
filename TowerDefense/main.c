#include "fichier.h"

int main()
{

    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();


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
    chargerBITMAP();

    while ( !key[KEY_ESC] )
    {
    menu();
    }

    return 0;
}
END_OF_MAIN();

void chargerBITMAP()
{
   int i=0;
   char nomfichier[256];

   mde=load_bitmap("images/credits2.bmp",NULL);
    if (!mde)
    {
        allegro_message("pas pu trouver mde.bmp");
        exit(EXIT_FAILURE);
    }
    mde2=load_bitmap("images/mde.bmp",NULL);
    if (!mde)
    {
        allegro_message("pas pu trouver mde.bmp");
        exit(EXIT_FAILURE);
    }
    decor=load_bitmap("images/decor.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }
    reglages=load_bitmap("images/reglages.bmp",NULL);
    if (!reglages)
    {
        allegro_message("pas pu trouver reglages.bmp");
        exit(EXIT_FAILURE);
    }
    retour=load_bitmap("images/retour.bmp",NULL);
    if (!reglages)
    {
        allegro_message("pas pu trouver retour.bmp");
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
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"champignon%d.bmp",i);

        img1[i] = load_bitmap(nomfichier,NULL);
        if (!img1[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
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

    decor=load_bitmap("images/image0.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }

    gameover=load_bitmap("images/gameover.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }
    for (i=0;i<7;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"images/Orc1/orc1%d.bmp",i);

        imgorc1[i] = load_bitmap(nomfichier,NULL);
        if (!imgorc1[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }
    for (i=0;i<7;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"images/Orc2/orc2%d.bmp",i);

        imgorc2[i] = load_bitmap(nomfichier,NULL);
        if (!imgorc2[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }
    for (i=0;i<7;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier,"images/Orc3/orc3%d.bmp",i);

        imgorc3[i] = load_bitmap(nomfichier,NULL);
        if (!imgorc3[i]){
            allegro_message("pas pu trouver %s",nomfichier);
            exit(EXIT_FAILURE);
        }
    }

decor2=load_bitmap("images/image1.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor1.bmp");
        exit(EXIT_FAILURE);
    }
    decor3=load_bitmap("images/image2.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver iamge2.bmp");
        exit(EXIT_FAILURE);
    }
    victoire=load_bitmap("images/victoire.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver iamge2.bmp");
        exit(EXIT_FAILURE);
    }


}

void credit()
{

    clear(screen);


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



    clear(screen);



    blit(mde2,screen,0,0, (SCREEN_W-mde->w)/2,0, mde->w, mde->h);


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


    clear(screen);


    blit(decor,screen,0,0, (SCREEN_W-decor->w)/2, (SCREEN_H-decor->h)/2, decor->w, decor->h);


    blit(reglages,screen,0,0, (SCREEN_W-reglages->w)/2,0, reglages->w, reglages->h);


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


void argent(t_acteur *tab[50], int *piece, int *p1)
{
        int i;
        for(i=0;i<10;i++)
        {
            if(tab[i]->etat==1)
{

        *p1=*p1+1;
        if (*p1>=100){
            *p1=0;
            *piece=*piece+25;}}}

}














