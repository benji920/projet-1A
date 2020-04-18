#include <allegro.h>
#include <time.h>
#include <math.h>

void menu();//affichage du menu et sélection
void modedemploi();//affichage des règles
void reglages();//affichage des reglages


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
    menu();
    while ( !key[KEY_ESC] )
    {

    }

    return 0;
}
END_OF_MAIN();

void menu()
{
    clear(screen);
    textprintf_ex(screen,font,SCREEN_W/2-100,270,makecol(255,255,0),makecol(0,0,0),"  APPUYER POUR JOUER ");
    textprintf_ex(screen,font,SCREEN_W/2,300,makecol(0,255,0),makecol(0,0,0),"  APPUYER SUR HAUT POUR MODE D'EMPLOI ");
    textprintf_ex(screen,font,SCREEN_W/2,330,makecol(0,0,255),makecol(0,0,0),"  APPUYER SUR BAS POUR REGLAGES ");
    textprintf_ex(screen,font,550,570,makecol(255,0,0),makecol(0,0,0),"  Appuyer sur ESC pour quitter ");
    while ( !key[KEY_ESC] )
    {
        if (mouse_b&1 && mouse_x>=SCREEN_W/2-100 && mouse_x<=SCREEN_W/2+100 && mouse_y<=285 && mouse_y>=255)
        {
            modedemploi();
        }
        if (key[KEY_DOWN])
        {
            reglages();
        }
    }
}

void modedemploi()
{
    clear(screen);
    textprintf_ex(screen,font,550,570,makecol(255,0,0),makecol(0,0,0),"  Appuyer right pour revenir au menu ");
    while ( !key[KEY_ESC] )
    {
        if (key[KEY_RIGHT])
        {
            menu();
        }
    }
}

void reglages()
{
    clear(screen);
    textprintf_ex(screen,font,550,570,makecol(255,0,0),makecol(0,0,0),"  Appuyer sur DROITE pour revenir au menu ");
    while ( !key[KEY_ESC] )
    {
        if (key[KEY_RIGHT])
        {
            menu();
        }
    }
}
