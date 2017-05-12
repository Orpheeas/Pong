#include "Point.h"


//Procédures et Fonctions
//******************************************************************************************************************************************************
int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame, font *mFont){
//But Initialiser tout le programme
//Entrée Le titre, les positions x et y, la hauteur pour la fenetre ainsi que l'element jeu contenent le nécéssaire et la police
//Sortie tous les éléments précédent initialisé

    myGame->g_pWindow=NULL;
    myGame->g_pRenderer=NULL;
    myGame->g_psurface=NULL;
    myGame->g_ptexture=NULL;


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_PRESENTVSYNC);


            }

    }else{

        return 0;
        }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    mFont->g_font=TTF_OpenFont("./assets/fonts/adlery/Adlery_TRIAL.ttf",65);

    if(!mFont->g_font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        SDL_Delay(5000);
        exit(EXIT_FAILURE);
    }

    return 1;

}

void Gamewindow(game *myGame,Player *Joueur1,Player *Joueur2, Balle *Ball ) {
//But gérér la fenetre de jeu (les dessins et leur affichage)
//Entrée Les joueurs (qui contiennent les raquettes) la balle et le jeu
//Sortie les dessins bien placés

        int i;

       //Dessin de la raquette du joueur 1
        Joueur1->Raquette.x=RAQUETTE1_POSITION_X;//debut x
        Joueur1->Raquette.y=Joueur1->co.y;       //debut y
        Joueur1->Raquette.w=RAQUETTE_WIDHT;      //Largeur
        Joueur1->Raquette.h=RAQUETTE_HEIGHT;     //Hauteur


        //Dessin de la raquette du joueur 2
        Joueur2->Raquette.x=RAQUETTE2_POSITION_X;//debut x
        Joueur2->Raquette.y=Joueur2->co.y;       //debut y
        Joueur2->Raquette.w=RAQUETTE_WIDHT;      //Largeur
        Joueur2->Raquette.h=RAQUETTE_HEIGHT;     //Hauteur

        //Dessin du cercle
        for (i=0; i<NBPOINT; i++){
            Ball->point.x=(RAYON*cos(i)+Ball->centre.x);
            Ball->point.y=(RAYON*sin(i)+Ball->centre.y);
            SDL_SetRenderDrawColor(myGame->g_pRenderer,255,0,0,255);
            SDL_RenderDrawPoint(myGame->g_pRenderer, Ball->point.x, Ball->point.y);
        }


        //Draw in texture
        SDL_SetRenderDrawColor(myGame->g_pRenderer,255,0,0,255);
        SDL_SetRenderTarget(myGame->g_pRenderer, myGame->g_ptexture); //on modifie la texture

        SDL_RenderFillRect(myGame->g_pRenderer, &Joueur1->Raquette);
        SDL_RenderFillRect(myGame->g_pRenderer, &Joueur2->Raquette);

        SDL_SetRenderTarget(myGame->g_pRenderer, NULL);// Dorénavent, on modifie à nouveau le renderer

        SDL_Rect position;//position de la texture dans screen
        position.x = 0;
        position.y = 0;
        SDL_QueryTexture(myGame->g_ptexture, NULL, NULL, &position.w, &position.h);
        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,NULL,&position);


         SDL_RenderPresent(myGame->g_pRenderer);

         SDL_SetRenderDrawColor(myGame->g_pRenderer,0,0,0,255);
         SDL_DestroyTexture(myGame->g_ptexture);
         SDL_RenderClear(myGame->g_pRenderer);




}

void destroy(game *myGame){
//But Détruire les différenst éléments de game
//Entrée Le jeu
//Sortie Les éléments détruit
      //Destroy render
     if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);

      //Destroy texture
     if(myGame->g_ptexture!=NULL)
        SDL_DestroyTexture(myGame->g_ptexture);

    //Destroy surface
     if(myGame->g_psurface!=NULL)
         SDL_FreeSurface(myGame->g_psurface);

    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}


void handleEvents(gameState *state,Player *Joueur1,Player *Joueur2){
//But gérer les inputs
//Entrée Le Gamestate et les joueurs
//Sortie Les Etat des joueurs adaptés au inputs

    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:                                //
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_UP: ;Joueur2->Etat=Monte; break;
                                case SDLK_DOWN:Joueur2->Etat=Des ; break;
                                case SDLK_z: Joueur1->Etat=Monte; break;
                                case SDLK_s: Joueur1->Etat=Des; break;
                            }
                            break;

        case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                            {
                                case SDLK_UP: ;Joueur2->Etat=Immo; break;
                                case SDLK_DOWN:Joueur2->Etat=Immo ; break;
                                case SDLK_z: Joueur1->Etat=Immo; break;
                                case SDLK_s: Joueur1->Etat=Immo; break;
                            }
                            break;

        default:break;

        }
    }


}

void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}

void BougeRaquette(Player *Joueur1, Player *Joueur2){
//But déplacer les raquettes
//Entrée les raquettes
//Sortie les raquette déplacés
        if ((Joueur1->Etat==Des) && (Joueur1->co.y>0)){

        Joueur1->co.y+=4;
        }else if((Joueur1->Etat==Monte) && (Joueur1->co.y<SCREEN_HEIGHT)){
         Joueur1->co.y-=4;
        }

        if ((Joueur2->Etat==Des) && (Joueur2->co.y>0)){

        Joueur2->co.y+=4;
        }else if((Joueur2->Etat==Monte) && (Joueur2->co.y<SCREEN_HEIGHT)){
         Joueur2->co.y-=4;
        }

        if (Joueur1->co.y<0){ Joueur1->co.y=1;}
        if (Joueur2->co.y<0){ Joueur2->co.y=1;}

        if (Joueur1->co.y>SCREEN_HEIGHT-RAQUETTE_HEIGHT){ Joueur1->co.y=SCREEN_HEIGHT-RAQUETTE_HEIGHT;}
        if (Joueur2->co.y>SCREEN_HEIGHT-RAQUETTE_HEIGHT){ Joueur2->co.y=SCREEN_HEIGHT-RAQUETTE_HEIGHT;}

}

void BougeBalle(Balle *Ball){
//But Bouger la balle
//Entrée la balle
//Sortie la balle avec une vitesse différente si nécéssaire

    //Gestion de la vitesse horinzontale
    if (Ball->vitessex==-1){

        Ball->centre.x-=2;
    }

    if (Ball->vitessex==1){

        Ball->centre.x+=2;
    }

    //Gestion de la vitesse verticale
    if (Ball->vitessey==-1){

        Ball->centre.y-=2;
    }

    if (Ball->vitessey==1){

        Ball->centre.y+=2;
    }


}

void Gestion_Collision_Balle(Balle *Ball, Player *Joueur1, Player *Joueur2 ){
//But Gérer les collisions de la balle
//Entrée La balle + les joueurs
//Sortie Les différentes collisions gérer ainsi que le score si nécéssaire

    int i;

    for (i=0; i<NBPOINT; i++){
        //Gestion des côtes

        if ((RAYON*sin(i)+Ball->centre.y)<=0){
            Ball->vitessey=1;
        }else if ((RAYON*sin(i)+Ball->centre.y)>=SCREEN_HEIGHT){
            Ball->vitessey=-1;

        //Gestion avec buts
        }else if ((RAYON*sin(i)+Ball->centre.x)<=0){
            Ball->vitessex=1;
            Ball->centre.x=SCREEN_WIDTH/2;
            Ball->centre.y=SCREEN_HEIGHT/2;
            Joueur2->Score+=1;
        }else if((RAYON*sin(i)+Ball->centre.x)>=SCREEN_WIDTH){
            Ball->vitessex=-1;
            Ball->centre.x=SCREEN_WIDTH/2;
            Ball->centre.y=SCREEN_HEIGHT/2;
            Joueur1->Score+=1;

        //Gestion avec les raquettes
        }else if (Collision(&Ball->centre, &Joueur1->Raquette) == true ){

            Ball->vitessex=1;
        }else if (Collision(&Ball->centre, &Joueur2->Raquette) == true ){

            Ball->vitessex=-1;
        }
    }

}

bool Collision(coordonnees *coordo,SDL_Rect *box)
{
//But Gère les collisions
//Entrée Les coordonées à tester ainsi que l'objet qu'elle peut potentiellement toucher
//Sortie Vrai ou Faux selon si l'objet est en colision ou non
   if (( (coordo->x) >= (box->x) )
    && ( (coordo->x) < (box->x + box->w) )
    && ( (coordo->y) >= (box->y) )
    && ( (coordo->y) < (box->y + box->h) ))
       return true;
   else
       return false;
}

void writeScore(game *myGame,font mFont){
//But Ecrire le score
//Entrée le jeu et la police
//Sortie le score écrit
    SDL_Color fontColor={255,0,0};

        myGame->g_psurface=TTF_RenderText_Blended(mFont.g_font, "SCORE :", fontColor);//Charge la police

        if(myGame->g_psurface){


                //Définition du rectangle dest pour afficher la chaine
                SDL_Rect rectangle;
                rectangle.x=SCREEN_WIDTH/4;//debut x
                rectangle.y=0;//debut y
                rectangle.w=100; //Largeur
                rectangle.h=50; //Hauteur


                 myGame->g_ptexture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_psurface); // Préparation de la texture pour la chaine
                 SDL_FreeSurface(myGame->g_psurface); // Libération de la ressource occupée par le sprite

                 if(myGame->g_ptexture){

                        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,NULL,&rectangle); // Copie du sprite grâce au SDL_Renderer
                        SDL_RenderPresent(myGame->g_pRenderer); // Affichage
                 }
                 else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de creation surface pour chaine (%s)\n",SDL_GetError());
        }


}
//******************************************************************************************************************************************************
