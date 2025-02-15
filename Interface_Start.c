#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "fonctions_fichers.h"
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>

int main(){
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
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1024,832, SDL_WINDOW_RESIZABLE);
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
    //SDL_Texture* fond= charger_image( "fond.bmp", ecran );
    

    //créer le terrain
    int nbLig=0;
    int nbCol=0;
    char** G=allouer_tab_2D(nbLig,nbCol);
    taille_fichier("Start.txt",&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol);
    G=lire_fichier("Start.txt");
    afficher_tab_2D(G,nbLig,nbCol);
    
   

    
    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* pavage= charger_image_transparente( "pavage.bmp", ecran,r,g,b);
    
    //charger l'image sur fond
    
    SDL_Rect SrcR_pavage[10][16];
     for(int i=0; i<10; i++)
    {
        for(int j=0; j<16; j++)
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
    

         
    //charger le texte
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    char Jeu[] = "Hunter";
    char Start[] ="Start";
    char Help[]="Help";
    SDL_Texture* jeu= charger_texte(Jeu,ecran,font,color);
    SDL_Texture* start= charger_texte(Start,ecran,font,color);
    SDL_Texture* help= charger_texte(Help,ecran,font,color);
    SDL_Rect jeu_pos; 
    SDL_Rect start_pos;
    SDL_Rect help_pos;
    // Position du texte
    jeu_pos.x = 400;
    jeu_pos.y = 128;
    jeu_pos.w = 224; 
    jeu_pos.h = 60; 
    
    start_pos.x = 450;
    start_pos.y = 300;
    start_pos.w = 124; 
    start_pos.h = 60; 
    
    help_pos.x = 450;
    help_pos.y = 400;
    help_pos.w = 124; // Largeur du texte en pixels (à récupérer)
    help_pos.h = 60; // Hauteur du texte en pixels (à récupérer)
    
    // Boucle principale
    while(!terminer)
    {
        SDL_RenderClear(ecran);
       // SDL_RenderCopy(ecran,fond,NULL,NULL);

        for(int i=0; i<nbLig; i++)
        {
            for(int j=0;j<nbCol;j++)
            {

                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[(int)G[i][j]/16-3][(int)G[i][j]%16], &DestR_pavage[i][j]);
            }
        }
        

        int x=0;
        int y=0;
        while( SDL_PollEvent( &evenements ) )
            switch(evenements.type)
            {
                case SDL_QUIT:terminer = true; 
                break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(evenements.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            x=evenements.button.x;
                            y=evenements.button.y;
                            if(x>450&&x<574&&y>300&&y<360){
                                SDL_DestroyRenderer(ecran);
                                SDL_DestroyWindow(fenetre);
                                SDL_Quit();
                                system("./main");
                            }
                            if(x>450&&x<574&&y>400&&y<460){
                                SDL_DestroyRenderer(ecran);
                                SDL_DestroyWindow(fenetre);
                                SDL_Quit();
                                system("./help");
                            }
                            break;
                        case SDL_BUTTON_RIGHT:
                            break;
                }
            }
       //Appliquer la surface du texte sur l’écran
        SDL_RenderCopy(ecran,jeu,NULL,&jeu_pos);
        SDL_RenderCopy(ecran,start,NULL,&start_pos);
        SDL_RenderCopy(ecran,help,NULL,&help_pos);
        SDL_RenderPresent(ecran);  
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
