#include "Point.h"

//Code principal
//******************************************************************************************************************************************************

int main(int argc, char *argv[])
{


     game myGame;
     gameState state;

     unsigned int frameLimit = SDL_GetTicks() + 16;
     Player Joueur1;
     Player Joueur2;
     Balle Ball;

     Ball.centre.x=SCREEN_WIDTH/2;
     Ball.centre.y=SCREEN_HEIGHT/2;

     Ball.vitessex=-1;
     Ball.vitessey=-1;

     font mFont;

     int choix=0;



     state.g_bRunning=1;


        //Create texture for drawing in texture or load picture
        myGame.g_ptexture=SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);

        //Lancement du jeu
        while(state.g_bRunning){



                if(choix==0){

                    printf("Appuyez sur 1 pour lancer le jeu\n");
                    printf("Appuyez sur n'importe quel autre touche pour quitter\n");

                    scanf("%i",&choix);


                }
                switch (choix){
                        case 1:init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame,&mFont);
                                while(state.g_bRunning){


                                    handleEvents(&state,&Joueur1,&Joueur2);
                                    BougeRaquette(&Joueur1,&Joueur2);
                                    BougeBalle(&Ball);
                                    Gestion_Collision_Balle(&Ball,&Joueur1,&Joueur2);
                                    Gamewindow(&myGame,&Joueur1,&Joueur2,&Ball);
                                    //writeScore(&myGame,mFont);  Crée des bugs pour l'instant

                                }

                                 break;
                        default:return 0;


                }

                 system ("cls");

             // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;



        }

        destroy(&myGame);

        SDL_Quit();


    return 0;
}



//******************************************************************************************************************************************************



