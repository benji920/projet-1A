#include "fichier.h"

void jouer2()
{

    t_acteur * mesActeurs[50];
    t_acteur * mesActeurs1[50];
    t_tour * mesTours[50];
    t_rondin *mesRondins[50];

    int compteur=0;
    int piece=300;
    int ennemies1=12;
    int ennemies2=3;
    int ennemies3=3;
    int compteurTour=0;
    int compteurRondin=0;
    int i=0;
    int x=30;
    int y=30;
    int cx;
    int cy;
    int u;
    int imgcourante=0;
    int cptimg=0, tmpimg=4;
    int imgcourante1=0;
    int cptimg1=0, tmpimg1=150;
    int cptargent=0;
    int cptfleche=0, tmpfleche=150;
    int cptvictoire=0;
    int a=0;
    int b=0;
    int v;


    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

 char nomfichier1[256];
for (i=0;i<3;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier1,"champignon%d.bmp",i);

        img1[i] = load_bitmap(nomfichier1,NULL);
        if (!img1[i]){
            allegro_message("pas pu trouver %s",nomfichier1);
            exit(EXIT_FAILURE);
        }
    }

rondin=load_bitmap("images/rondin.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver rondin.bmp");
        exit(EXIT_FAILURE);
    }


        //on remplie les tableaux des différents acteurs
    remplirTabActeurs(mesActeurs);
    remplirTabActeurs1(mesActeurs1);
    remplirTabTour(mesTours);
    remplirTabRondin(mesRondins);
    //on initialise le nombre d'ennemis
    InitialiserEnnemies(mesActeurs,&ennemies1,&ennemies2,&ennemies3);
    int jeu=0;

    while (jeu==0 )
    {

        cptfleche++;
        if(cptfleche>tmpfleche)
            cptfleche=0;
        clear_bitmap(page);
        blit(decor2,page,0,0,0,0, SCREEN_W, SCREEN_H);

        textprintf_ex(page,font,0,SCREEN_H-10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        textprintf_ex(page,font,850,20,makecol(255,255,255),-1,"vos pieces : %d",piece);


        actualiserTabActeurs(mesActeurs);//actualiser position des orcs


        for (i=0;i<50;i++)
        {
            if(mesTours[i]->etat==1 && mesTours[i]->depfx==0 && cptfleche>=tmpfleche)
                {mesTours[i]->depfx=3;}
        }
            //on verifie les collisions entre tous les acteurs
        collision2(mesTours,mesActeurs,&cptfleche,&tmpfleche);
        collision3(mesRondins,mesActeurs);
        collision(mesActeurs1,mesActeurs);

        argent(mesActeurs1, &piece, &cptargent);//on incrémente l'argent en fct du nombre de champignons actifs



cptimg++;
        if (cptimg>=tmpimg){
            cptimg=0;
            imgcourante++;
            if (imgcourante>=6)
                imgcourante=0;
        }

        for (i=0;i<50;i++)
    {
        if(mesActeurs[i]->vie<=0)
        {
        mesActeurs[i]->etat=0;

        }
    }
//on enleve les rondins si plus de vie
for (i=0;i<50;i++)
    {
        if(mesRondins[i]->vie<=0)
        {
        mesRondins[i]->etat=0;

        }
    }

    for (i=0;i<50;i++)
    {
       if(mesTours[i]->etat==1)
       {if(mesTours[i]->posfx<=270)
        {
        mesTours[i]->etatf=0;
        }
        if(mesTours[i]->posfx>270)
        {
        mesTours[i]->etatf=1;
        }
       }
    }

//on affiche les orcs avec différents
    for (i=0;i<ennemies1;i++)
    {
        if(mesActeurs[i]->etat==1 && mesActeurs[i]->vie>0)
        {
        if(mesActeurs[i]->type==1)
        draw_sprite(page,imgorc1[imgcourante], mesActeurs[i]->posx,mesActeurs[i]->posy);
        if(mesActeurs[i]->type==2)
            draw_sprite(page,imgorc2[imgcourante], mesActeurs[i]->posx,mesActeurs[i]->posy);
        if(mesActeurs[i]->type==3)
            draw_sprite(page,imgorc3[imgcourante], mesActeurs[i]->posx,mesActeurs[i]->posy);

        textprintf_ex(page,font,mesActeurs[i]->posx+5,mesActeurs[i]->posy-5,makecol(255,255,255),-1,"vie : %d",mesActeurs[i]->vie);

        }
    }





  masked_blit(img1[2],page,0,0,x,y, img1[2]->w, img1[2]->h);
  masked_blit(tour,page,0,0,150,0, tour->w, tour->h);
  masked_blit(rondin,page,0,0,300,20, rondin->w, rondin->h);



if(!(mouse_b&1))
u=0;


        if(mouse_b&1 && u==0 && mouse_x>=27 && mouse_x<=106 && mouse_y>=30 && mouse_y<=134 &&piece>=75 )
        {
            mesActeurs1[compteur]->etat=1;
            draw_sprite(page,img1[imgcourante1], mouse_x,mouse_y);
            compteur++;
            piece=piece-75;
            u=1;
        }

       if(mouse_b&1 && u==0 && mouse_x>=158 && mouse_x<=240 && mouse_y>=10 && mouse_y<=130 && piece>=150 )
        {
            mesTours[compteurTour]->etat=1;
            draw_sprite(page,tour, mouse_x,mouse_y);
            compteurTour++;
            piece=piece-150;
            u=2;
        }

        if(mouse_b&1 && u==0 && mouse_x>=288 && mouse_x<=361 && mouse_y>=10 && mouse_y<=130 && piece>=100 )
        {
            mesRondins[compteurRondin]->etat=1;
            draw_sprite(page,rondin, mouse_x,mouse_y);
            compteurRondin++;
            piece=piece-100;
            u=3;
        }

        if(mouse_x<285 && mouse_y>180 && mouse_y<580){

//On blinde le placement des tours sur les carrés
 if (mouse_b&1 && u==2)
        {
            mesTours[compteurTour-1]->postx = mouse_x;
            mesTours[compteurTour-1]->posty = mouse_y;
            mesTours[compteurTour-1]->posfx = mouse_x;


            if(mouse_x>=2 && mouse_x<=135 && mouse_y>=200 && mouse_y<=315 )
        {
            mesTours[compteurTour-1]->postx=65-50;
            mesTours[compteurTour-1]->posty=250-80;
            mesTours[compteurTour-1]->posfx=50-50;
            mesTours[compteurTour-1]->posfy=mesTours[compteurTour-1]->posty;

        }
        if(mouse_x>=2 && mouse_x<=135 && mouse_y>=315 && mouse_y<=455)
        {
            mesTours[compteurTour-1]->postx=65-50;
            mesTours[compteurTour-1]->posty=385-80;
            mesTours[compteurTour-1]->posfx=65-50;
            mesTours[compteurTour-1]->posfy=mesTours[compteurTour-1]->posty;
        }
        if(mouse_x>=2 && mouse_x<=135 && mouse_y>=455 && mouse_y<=581)
        {
           mesTours[compteurTour-1]->postx=65-50;
            mesTours[compteurTour-1]->posty=515-80;
            mesTours[compteurTour-1]->posfx=65-50;
            mesTours[compteurTour-1]->posfy=mesTours[compteurTour-1]->posty;
        }
        if(mouse_x>=135 && mouse_x<=270 && mouse_y>=200 && mouse_y<=315)
        {
            mesTours[compteurTour-1]->postx=200-50;
            mesTours[compteurTour-1]->posty=250-80;
            mesTours[compteurTour-1]->posfx=200-50;
            mesTours[compteurTour-1]->posfy=mesTours[compteurTour-1]->posty;
        }
        if(mouse_x>=135 && mouse_x<=270 && mouse_y>=315 && mouse_y<=455)
        {
            mesTours[compteurTour-1]->postx=200-50;
            mesTours[compteurTour-1]->posty=385-80;
            mesTours[compteurTour-1]->posfx=200-50;
            mesTours[compteurTour-1]->posfy=mesTours[compteurTour-1]->posty;
        }
        if(mouse_x>=135 && mouse_x<=270 && mouse_y>=455 && mouse_y<=581)
        {
            mesTours[compteurTour-1]->postx=200-50;
            mesTours[compteurTour-1]->posty=515-80;
            mesTours[compteurTour-1]->posfx=200-50;
            mesTours[compteurTour-1]->posfy=mesTours[compteurTour-1]->posty;
        }
        }

//On blinde le placement des champignons sur les carrés
        if (mouse_b&1 && u==1 )
        {
            mesActeurs1[compteur-1]->posx = mouse_x;
            mesActeurs1[compteur-1]->posy = mouse_y;

            if(mouse_x>=2 && mouse_x<=135 && mouse_y>=190 && mouse_y<=315 && a==0)
        {
            mesActeurs1[compteur-1]->posx=65-10;
            mesActeurs1[compteur-1]->posy=250-15;
        }
        if(mouse_x>=2 && mouse_x<=135 && mouse_y>=315 && mouse_y<=455)
        {
            mesActeurs1[compteur-1]->posx=65-10;
            mesActeurs1[compteur-1]->posy=385-15;
        }
        if(mouse_x>=2 && mouse_x<=135 && mouse_y>=455 && mouse_y<=581)
        {
            mesActeurs1[compteur-1]->posx=65-10;
            mesActeurs1[compteur-1]->posy=515-15;
        }
        if(mouse_x>=135 && mouse_x<=270 && mouse_y>=190 && mouse_y<=315)
        {
            mesActeurs1[compteur-1]->posx=200-10;
            mesActeurs1[compteur-1]->posy=250-15;
        }
        if(mouse_x>=135 && mouse_x<=270 && mouse_y>=315 && mouse_y<=455)
        {
            mesActeurs1[compteur-1]->posx=200-10;
            mesActeurs1[compteur-1]->posy=385-15;
        }
        if(mouse_x>=135 && mouse_x<=270 && mouse_y>=455 && mouse_y<=581)
        {
            mesActeurs1[compteur-1]->posx=200-10;
            mesActeurs1[compteur-1]->posy=515-15;
        }
        }
        }
if(mouse_x>285 && mouse_y>180 && mouse_y<600){
if (mouse_b&1 && u==3 )
        {
            mesRondins[compteurRondin-1]->posx = mouse_x;
            mesRondins[compteurRondin-1]->posy = mouse_y;}}


 cptimg1++;
        if (cptimg1>=tmpimg1){
            cptimg1=0;
            imgcourante1++;
            if (imgcourante1>=2)
                imgcourante1=0;
        }

 for (i=0;i<50;i++)
    {
        if(mesActeurs1[i]->etat==1)
        {

        draw_sprite(page,img1[imgcourante1], mesActeurs1[i]->posx,mesActeurs1[i]->posy);//si le champignon est vivant, on le blit

        }
    }


actualiserrondins(mesRondins, page,  rondin);//on actualise la position des rondins

actualisertour(mesTours, page, tour, fleche);//on actualise la position des tours et des fleches



        // 4) on affiche le buffer
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        for(i=0;i<50;i++)
    {
        if(mesActeurs[i]->posx<=50 && mesActeurs[i]->etat==1)//conditions de défaite

            jeu=1;//on sort de la boucle while
    }

cptvictoire=0;
    for (i=0;i<50;i++)
    {
        if(mesActeurs[i]->etat==0)
        {

        cptvictoire=cptvictoire+1;
        if (cptvictoire==50)//condition de victoire


            jeu=2;//on sort de la boucle while



        }
    }

        // 5) on fait une pause
        rest(20);
    }

if(jeu==2)
{
    blit(victoire,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(5000);
    jouer3();
}

if(jeu==1)
{
    blit(gameover,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(5000);

}

    allegro_exit();

}
