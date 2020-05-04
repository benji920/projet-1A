#include "fichier.h"

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

    SAMPLE *sample;
sample=load_wav("son1.wav");
install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);

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

play_sample(sample,100,100,1000,0);


    while ( !key[KEY_ESC] )
    {


        blit(decor,page,0,0,0,0, SCREEN_W, SCREEN_H);
        textprintf_ex(page,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);

    if(mouse_x<=850 && mouse_x>=600 && mouse_y<=420 && mouse_y>=350)
    {
        draw_sprite(page,hachette,530-30,360-10);
    }

    if(mouse_x<=456 && mouse_x>=200 && mouse_y<=420 && mouse_y>=350)
    {
        draw_sprite(page,hachette,110-30,360-10);

    }
    if(mouse_x<=456 && mouse_x>=200 && mouse_y<=570 && mouse_y>=500)
    {
        draw_sprite(page,hachette,110-30,510-10);
    }
    if(mouse_x<=880 && mouse_x>=600 && mouse_y<=570 && mouse_y>=500)
    {
        draw_sprite(page,hachette,530-30,510-10);
    }
        if (mouse_b&1 && mouse_x>=200 && mouse_x<=456 && mouse_y>=350 && mouse_y<=420)
        {
            jouer1();
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
