#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "fonctions_fichers.h"
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define SPEED 50
/**
    * \brief La fonction rafrachit l'écran en fonction de touche de clavier
    * \param abs abscisse de hunter 
    * \param ord ordonne de hunter
    * \param abs1 abscisse de monstre 
    * \param ord1 ordonne de monstre
    * \param p si le monstre  tue hunter
    */
    void refresh_graphics(int* abs,int* ord,char dir,char** G,char** G2,SDL_Rect* DestR_character,SDL_Rect* Mort_pos,SDL_Rect* Restart_pos,int* abs1,int* ord1,int* p){
        if((int)G[*ord/64][*abs/64]%16==7||(int)G2[*ord/64][*abs/64]%16==8)
            {
                switch(dir)
                    {
                        case 'h':
                            *ord=*ord+64; 
                                     break;
                        case 'b':
                            *ord=*ord-64; 
                                     break;
                        case 'g':
                            *abs=*abs+64; 
                                     break;
                        case 'd':
                            *abs=*abs-64;
                                     break;
                    
                    }
            }
        if((int)G2[*ord/64][*abs/64]%16==3)
            {
                        *p=1;
                        *abs=-100;
                        *ord=-100;
                        (*DestR_character).x =-100;
                        (*DestR_character).y =-100;
                        (*Mort_pos).x = 400;
                        (*Mort_pos).y = 350;
                        (*Mort_pos).w = 224; // Largeur du texte en pixels (à récupérer)
                        (*Mort_pos).h = 132; // Hauteur du texte en pixels (à récupérer)
    
                        (*Restart_pos).x = 462;
                        (*Restart_pos).y = 487;
                        (*Restart_pos).w = 100; // Largeur du texte en pixels (à récupérer)
                        (*Restart_pos).h = 50; // Hauteur du texte en pixels (à récupérer)
            }
                    (*DestR_character).x =*abs;
                    (*DestR_character).y =*ord;
        if(*abs<*abs1+64&&*ord<*ord1+64&&*abs>*abs1-64&&*ord>*ord1-64)//monstre tue hunter
            {   
                (*Mort_pos).x = 400;
                (*Mort_pos).y = 350;
                (*Mort_pos).w = 224; // Largeur du texte en pixels (à récupérer)
                (*Mort_pos).h = 132; // Hauteur du texte en pixels (à récupérer)
                (*Restart_pos).x = 462;
                (*Restart_pos).y = 487;
                (*Restart_pos).w = 100; // Largeur du texte en pixels (à récupérer)
                (*Restart_pos).h = 50; // Hauteur du texte en pixels (à récupérer)
                *abs=-100;
                *ord=-100;
                (*DestR_character).x =-100;
                (*DestR_character).y =-100;
                *p=1;
            }
    }
    
/**
    * \brief monster deplace automatique
    * \param abs abscisse de monstre
    * \param ord ordonne de monstre
    */
    void move_monster(int* abs,int* ord,char dir,char** G,char** G2,SDL_Rect* DestR_monster){
        int t=rand()%4;
        switch(t)
                {
                     case 0:
                         *abs=*abs-64; 
                         dir='g';
                                     break;
                     case 1:
                         *ord=*ord-64; 
                         dir='h';
                                     break;
                     case 2:
                         *abs=*abs+64; 
                         dir='d';
                                     break;
                     case 3:
                         *ord=*ord+64; 
                         dir='b';
                                    break;
                 }
        
            if((int)G[*ord/64][*abs/64]%16==7||(int)G2[*ord/64][*abs/64]%16==3||(int)G2[*ord/64][*abs/64]%16==8)
            {
                switch(dir)
                    {
                     case 'h':
                         *ord=*ord+64; 
                                     break;
                     case 'b':
                         *ord=*ord-64; 
                                     break;
                     case 'g':
                         *abs=*abs+64; 
                                     break;
                     case 'd':
                         *abs=*abs-64;
                                    break;
                    }
            }
        (*DestR_monster).x =*abs;
        (*DestR_monster).y =*ord;
        }
        
/**
    * \brief balle deplace automatique
    * \param abs abscisse de balle 
    * \param ord ordonne de balle
    * \param abs1 abscisse de monstre 
    * \param ord1 ordonne de monstre
    * \param k si le monstre est tuee
    */
void move_balle(SDL_Window* fenetre,SDL_Renderer* ecran,int* abs,int* ord,char dir,char** G,char** G2,SDL_Rect* DestR_balle,int* i,int* abs1,int* ord1,SDL_Rect* DestR_monster,int* k){
        switch(dir)
            {
                case 'h':
                        *ord=*ord-SPEED;
                break;
                case 'b':
                        *ord=*ord+SPEED;
                break;
                case 'g':
                        *abs=*abs-SPEED;
                break;
                case 'd':
                        *abs=*abs+SPEED;
                break;
            }
        (*DestR_balle).x =*abs;
        (*DestR_balle).y =*ord;
        if((int)G[*ord/64][*abs/64]%16==7||(int)G2[*ord/64][*abs/64]%16==3||(int)G2[*ord/64][*abs/64]%16==8)
            {
                *i=0;
                (*DestR_balle).x =-100;
                (*DestR_balle).y =-100;
            }
        if(*abs<*abs1+64&&*ord<*ord1+64&&*abs>*abs1-64&&*ord>*ord1-64)//balle tue la monster
        {
            abs1=0;
            ord1=0;
            (*DestR_monster).x =-100;
            (*DestR_monster).y =-100;
            *k=1;
            SDL_DestroyRenderer(ecran);
            SDL_DestroyWindow(fenetre);
            SDL_Quit();
            system("./start");
        }
    
}


int main(){
    int nbLig=0;
    int nbCol=0;
    char** G=allouer_tab_2D(nbLig,nbCol);
    char** G2=allouer_tab_2D(nbLig,nbCol);
    
    
    int abs=64;//abscisse de hunter 
    int ord=64;//ordonne de hunter
    char dir='b'; // quartre option g: gauche h:haut d:droite b:bas
    
    int abs1=640;
    int ord1=640;//initialisation de monstre
    char dir1='d';
    
    int abs2=-100;
    int ord2=-100;//initialisation de balle  on mettre dehors de la carte
    
    srand(time(NULL));// Initialization
    // quartre option t=0: gauche t=1:haut t=2:droite t=3:bas
    
    
    SDL_Window* fenetre;  // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
        
    }
    
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1024, 832, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
        
    }
    
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    
    // Charger l’image
    SDL_Texture* fond= charger_image( "fond.bmp", ecran );
    
    //créer le terrain
    taille_fichier("terrain2.txt",&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol);
    G=lire_fichier("terrain2.txt");
    afficher_tab_2D(G,nbLig,nbCol);
    taille_fichier("fire2.txt",&nbLig,&nbCol);
    G2=allouer_tab_2D(nbLig,nbCol);
    G2=lire_fichier("fire2.txt");
    afficher_tab_2D(G2,nbLig,nbCol);
    
    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* pavage= charger_image_transparente("pavage.bmp", ecran,r,g,b);   
    SDL_Texture* character= charger_image_transparente("weapon.bmp", ecran,r,g,b); 
    SDL_Texture* monster= charger_image_transparente("eldritch.bmp", ecran,r,g,b);
    SDL_Texture* balle= charger_image_transparente("balle.bmp",ecran,r,g,b);
    
    SDL_Rect SrcR_pavage[13][15];
     for(int i=0; i<13; i++)
    {
        for(int j=0; j<15; j++)
        {  
            SrcR_pavage[i][j].x = j*32;
            SrcR_pavage[i][j].y = i*32;
            SrcR_pavage[i][j].w = 32; // Largeur du pavage
            SrcR_pavage[i][j].h = 32; // Hauteur du pavage
        }
    }
    SDL_Rect DestR_pavage[nbLig][nbCol];
    for(int i=0; i<nbLig; i++)
    {
        for(int j=0; j<nbCol; j++)
        {
            DestR_pavage[i][j].x =j*64;
            DestR_pavage[i][j].y =i*64;
            DestR_pavage[i][j].w = 64; // Largeur du pavage
            DestR_pavage[i][j].h = 64; // Hauteur du pavage
        }
        
    }
    
    SDL_Rect SrcR_character[4];
    for(int i=0; i<4; i++)
    {
        SrcR_character[i].x = 0;
        SrcR_character[i].y = i*49;
        SrcR_character[i].w = 39; // Largeur du pavage
        SrcR_character[i].h = 49; // Hauteur du pavage
    }
    SDL_Rect DestR_character;
    DestR_character.x =abs;
    DestR_character.y =ord;
    DestR_character.w = 64; // Largeur du hunter
    DestR_character.h = 64; // Hauteur du hunter
    
    SDL_Rect SrcR_monster;
    SrcR_monster.x = 0;
    SrcR_monster.y = 0;
    SrcR_monster.w = 236; // Largeur du monster
    SrcR_monster.h = 236; // Hauteur du monster
    SDL_Rect DestR_monster;
    DestR_monster.x =abs1;
    DestR_monster.y =ord1;
    DestR_monster.w = 64; // Largeur du monster
    DestR_monster.h = 64; // Hauteur du monster

    SDL_Rect SrcR_balle;
//     for(int i=0; i<15; i++)
//     {  
        SrcR_balle.x = 177;
        SrcR_balle.y = 177;
        SrcR_balle.w = 45; // Largeur du pavage
        SrcR_balle.h = 45; // Hauteur du pavage
//     }
    SDL_Rect DestR_balle;
//     for(int i=0; i<15; i++)
//     {  
        DestR_balle.x = abs2;
        DestR_balle.y = ord2;
        DestR_balle.w = 20; // Largeur du pavage
        DestR_balle.h = 20; // Hauteur du pavage
//     }
         
    //charger le texte
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    char Mort[] = "Tu es mort";
    char Restart[] ="Restart";
    SDL_Texture* mort= charger_texte(Mort,ecran,font,color);
    SDL_Texture* restart= charger_texte(Restart,ecran,font,color);
    SDL_Rect Mort_pos; 
    SDL_Rect Restart_pos;
    // Position du texte
    Mort_pos.x = -200;
    Mort_pos.y = -200;
    Mort_pos.w = 224; // Largeur du texte en pixels (à récupérer)
    Mort_pos.h = 132; // Hauteur du texte en pixels (à récupérer)
    
    Restart_pos.x = -200;
    Restart_pos.y = -200;
    Restart_pos.w = 100; // Largeur du texte en pixels (à récupérer)
    Restart_pos.h = 50; // Hauteur du texte en pixels (à récupérer)
    
    
    int tempsfin = 0, tempsdebut = 0;
    int i=0; // si le balle est present
    int dirb='b';// direction du balle
    int k=0;  // si le monster est tuee
    int p=0;  // si le monster  tue hunter
    int x=0;
    int y=0;
    // Boucle principale
    while(!terminer)
    {

        // chrono début
        tempsdebut = SDL_GetTicks();
        while( SDL_PollEvent( &evenements ) )
        {
            switch(evenements.type)
            {
                case SDL_QUIT:terminer = true; 
                break;
                case SDL_KEYDOWN:

                switch(evenements.key.keysym.sym)
                {
                     case SDLK_UP:
                         ord=ord-64; 
                         dir='h';
                                     break;
                     case SDLK_DOWN:
                         ord=ord+64; 
                         dir='b';
                                     break;
                     case SDLK_LEFT:
                         abs=abs-64; 
                         dir='g';
                                     break;
                     case SDLK_RIGHT:
                         abs=abs+64;
                         dir='d';
                                    break;
                    case SDLK_SPACE:
                        if(i==0&&p==0)
                        {
                        abs2=abs;
                        ord2=ord;
                        dirb=dir;
                        i=1;
                        }
                                    break;
                     case SDLK_q:
                         terminer = true;  break;
                    
                 }
                 case SDL_MOUSEBUTTONDOWN:
                    switch(evenements.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            x=evenements.button.x;
                            y=evenements.button.y;
                            if(x>462&&x<562&&y>487&&y<537){
                                SDL_DestroyRenderer(ecran);
                                SDL_DestroyWindow(fenetre);
                                SDL_Quit();
                                system("./start");
                            }
                            break;
                        case SDL_BUTTON_RIGHT:
                            break;
                }
            }
        }
        if(k==0)
        {
        move_monster(&abs1,&ord1,dir1,G,G2,&DestR_monster);
        }
        if(i!=0)
        {
            move_balle(fenetre,ecran,&abs2,&ord2,dirb,G,G2,&DestR_balle,&i,&abs1,&ord1,&DestR_monster,&k);
        }
        if(p==0)
        {
        refresh_graphics(&abs,&ord,dir,G,G2,&DestR_character,&Mort_pos,&Restart_pos,&abs1,&ord1,&p);
        }
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran,fond,NULL,NULL);
        
        for(int i=0; i<nbLig; i++)
        {
            for(int j=0;j<nbCol;j++)
            {

                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[(int)G[i][j]/16-3][(int)G[i][j]%16], &DestR_pavage[i][j]);
            }
        }
        for(int i=0; i<nbLig; i++)
        {
            for(int j=0;j<nbCol;j++)
            {

                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[(int)G2[i][j]/16-3][(int)G2[i][j]%16], &DestR_pavage[i][j]);
            }
        }
        SDL_RenderCopy(ecran,monster,&SrcR_monster,&DestR_monster);
        switch(dir)
                {
                     case 'h':
                         SDL_RenderCopy(ecran,character,&SrcR_character[3],&DestR_character);
                                     break;
                     case 'b':
                         SDL_RenderCopy(ecran,character,&SrcR_character[0],&DestR_character); 
                                     break;
                     case 'g':
                         SDL_RenderCopy(ecran,character,&SrcR_character[1],&DestR_character); 
                                     break;
                     case 'd':
                         SDL_RenderCopy(ecran,character,&SrcR_character[2],&DestR_character);
                                    break;
                    
                 }
        //Appliquer la surface du texte sur l’écran
        SDL_RenderCopy(ecran,mort,NULL,&Mort_pos);
        SDL_RenderCopy(ecran,restart,NULL,&Restart_pos);
        SDL_RenderCopy(ecran,balle,&SrcR_balle,&DestR_balle);
        SDL_RenderPresent(ecran);  
        
        
        // chrono fin
        tempsfin = SDL_GetTicks();
        
        
        
        // attente 2500/30 - durée
        SDL_Delay(2500/30 - (tempsfin - tempsdebut));
    }
    
    // Quitter SDL
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    // Fermer la police et quitter SDL_ttf
    TTF_CloseFont( font );
    TTF_Quit();
    return 0;
}
