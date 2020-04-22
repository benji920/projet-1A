#include <allegro.h>
#include <time.h>
#include <math.h>

void menu();//affichage du menu et s�lection
void modedemploi();//affichage des r�gles
void reglage();//affichage des reglages
void jeux();//lancement du jeux


int main()
{
    BITMAP *page;
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
    BITMAP *decor;
    BITMAP *mde;
    BITMAP *reglages;
    BITMAP *quitter;
    BITMAP *page;
    BITMAP *credits;
    BITMAP *jouer;
    BITMAP *hachette;

    clear(screen);

    decor=load_bitmap("images/decor1.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver decor.bmp");
        exit(EXIT_FAILURE);
    }
    blit(decor,screen,0,0, (SCREEN_W-decor->w)/2, (SCREEN_H-decor->h)/2, decor->w, decor->h);

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

    hachette=load_bitmap("images/hachette.bmp",NULL);
    if (!hachette)
    {
        allegro_message("pas pu trouver hachette.bmp");
        exit(EXIT_FAILURE);
    }
    //blit(towerdefense,screen,0,0, (SCREEN_W-towerdefense->w)/2, (SCREEN_H-towerdefense->h)/2-100, towerdefense->w, towerdefense->h);
    draw_sprite(screen,hachette,100,200);


    while ( !key[KEY_ESC] )
    {
        textprintf_ex(screen,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);



    draw_sprite(screen,hachette,100,200);

        if (mouse_b&1 && mouse_x>=(SCREEN_W-towerdefense->w)/2 && mouse_x<=(SCREEN_W+towerdefense->w)/2 && mouse_y>=(SCREEN_H-towerdefense->h)/2-100 && mouse_y<=(SCREEN_H+towerdefense->h)/2-100)
        {
            jeux();
        }
        if (mouse_b&1 && mouse_x>=(SCREEN_W-mde->w) && mouse_x<=(SCREEN_W+mde->w) && mouse_y>=0 && mouse_y<=(mde->w))
        {
            modedemploi();
        }
        if (mouse_b&1 && mouse_x>=0 && mouse_x<=(reglages->w) && mouse_y>=0 && mouse_y<=(reglages->w))
        {
            reglage();
        }
        if (mouse_b&1 && mouse_x>=(SCREEN_W-quitter->w) && mouse_x<=(SCREEN_W+quitter->w) && mouse_y>=(SCREEN_H-quitter->h) && mouse_y<=(SCREEN_H+quitter->h))
        {
            ;
        }
    }
}

void modedemploi()
{
    BITMAP *mde;
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
    clear(screen);
    textprintf_ex(screen,font,550,570,makecol(255,0,0),makecol(0,0,0)," JEUX Appuyer sur DROITE pour revenir au menu ");
    while ( !key[KEY_ESC] )
    {
        if (key[KEY_RIGHT])
        {
            menu();
        }
    }
}

