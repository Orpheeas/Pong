#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

//Bibliothèque
//******************************************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>


//Constantes
//******************************************************************************************************************************************************

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780
#define RAQUETTE_HEIGHT 150
#define RAQUETTE_WIDHT 10
#define RAQUETTE1_POSITION_X+RAQUETTE_WIDHT
#define RAQUETTE2_POSITION_X SCREEN_WIDTH-RAQUETTE_WIDHT
#define TAILLE 100
#define NBPOINT 360
#define RAYON 10
#define true 1
#define false 0

//******************************************************************************************************************************************************


//Structures
//******************************************************************************************************************************************************
typedef int bool;

enum BOOL{

    Des,Immo,Monte
};

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_ptexture;
     SDL_Surface *g_psurface;


}game;

typedef struct gameState{

    int g_bRunning;


}gameState;

typedef struct coordonnees{

    double x;
    double y;

}coordonnees;

typedef struct Balle{

    coordonnees centre;    //Les coordonees sont celles du centre
    SDL_Point point;     //Pour dessiner le cercle
    int vitessex;         // -1 = va à gauche, 1 = va à droite
    int vitessey;       // -1 = va en haut, 1 = va en haut

}Balle;

typedef struct Player{

    coordonnees co;
    enum BOOL Etat;   //Immo la raquette ne bouge aps, Monte elle monte, Des elle descend
    SDL_Rect Raquette;
    int Score;

}Player;


typedef struct font{

    TTF_Font *g_font;

}font;
//******************************************************************************************************************************************************

//Prototypes
//******************************************************************************************************************************************************

extern int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame, font *mFont);
extern void destroy(game *myGame);
extern void handleEvents(gameState *state,Player *Joueur1,Player *Joueur2);
extern void delay(unsigned int frameLimit);
extern void BougeRaquette(Player *Joueur1, Player *Joueur2);
extern void BougeBalle(Balle *Ball);
extern void Gestion_Collision_Balle(Balle *Ball, Player *Joueur1, Player *Joueur2 );
extern void Gamewindow(game *myGame,Player *Joueur,Player *Joueur2, Balle *Ball );
extern void writeScore(game *myGame,font mFont);

//******************************************************************************************************************************************************


#endif // POINT_H_INCLUDED
