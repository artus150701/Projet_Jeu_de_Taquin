#ifndef LIB
#define LIB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#endif

#ifndef HEADER
#define HEADER
#include "fonction_importante.h"
#include "jeu.h"
#include "affichage.h"
#include "mouvement.h"
#endif

#include <SDL/SDL_mixer.h>


char menu(){
  //retourne un char en fonction du choix du joueur  
  char choix = 'A';

  SDL_Surface *ecran = NULL, *titre = NULL, *dev = NULL, *choix1 = NULL, *choix2 = NULL;
  SDL_Rect position, position1, position2;
  SDL_Event event;
  TTF_Font *police = NULL;
  SDL_Color blanc = {255, 255, 255};
  SDL_Color vert = {0, 100, 0};
  int continuer = 1;

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  ecran = SDL_SetVideoMode(500, 350, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("MENU", NULL);

  police = TTF_OpenFont("bodoni.ttf", 60);
  titre = TTF_RenderText_Blended(police, "Jeu de Taquin", blanc);

  position.x = ecran->w / 2 - titre->w / 2;
  position.y = 30;

  police = TTF_OpenFont("bodoni.ttf", 20);
  dev = TTF_RenderUTF8_Blended(police, "Proposé par Paul CHASTEL et Corentin GUILLOT", blanc);

  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 30, 30));
  SDL_BlitSurface(titre, NULL, ecran, &position);

  position.x = ecran->w / 2 - dev->w / 2;
  position.y = 30 + titre->h;

  SDL_BlitSurface(dev, NULL, ecran, &position);

  police = TTF_OpenFont("bodoni.ttf", 30);
  choix1 = TTF_RenderUTF8_Blended(police, "Générer un tableau aléatoire", blanc);
  choix2 = TTF_RenderUTF8_Blended(police, "Charger un tableau", blanc);
  
  position1.x = ecran->w / 2 - choix1->w / 2;
  position1.y = ecran->h / 2 + choix1->h / 2 + 50;

  position2.x = ecran->w / 2 - choix2->w / 2;
  position2.y = ecran->h / 2 - choix2->h / 2;

  SDL_BlitSurface(choix1, NULL, ecran, &position1);
  SDL_BlitSurface(choix2, NULL, ecran, &position2);
  
  SDL_Flip(ecran);

  while (continuer) {
    SDL_WaitEvent(&event);
    
    switch (event.type) {
      
    case SDL_QUIT:
      continuer = 0;
      break;

    case SDL_MOUSEMOTION:
      // cas on passe la souri sur les choix pour changer la couleur
      if ((event.motion.x >= position1.x && event.motion.x <= position1.x + choix1->w) &&
	    (event.motion.y >= position1.y && event.motion.y <= position1.y + choix1->h)) {
	choix1 = TTF_RenderUTF8_Blended(police, "Générer un tableau aléatoire", vert);
	SDL_BlitSurface(choix1, NULL, ecran, &position1);
	SDL_Flip(ecran);
      }
      else if ((event.motion.x >= position2.x && event.motion.x <= position2.x + choix2->w) &&
		 (event.motion.y >= position2.y && event.motion.y <= position2.y + choix2->h)){
	choix2 = TTF_RenderUTF8_Blended(police, "Charger un tableau", vert);
	SDL_BlitSurface(choix2, NULL, ecran, &position2);
	SDL_Flip(ecran);
      }
      else{
	choix1 = TTF_RenderUTF8_Blended(police, "Générer un tableau aléatoire", blanc);
	choix2 = TTF_RenderUTF8_Blended(police, "Charger un tableau", blanc);
	SDL_BlitSurface(choix2, NULL, ecran, &position2);
	SDL_BlitSurface(choix1, NULL, ecran, &position1);
	SDL_Flip(ecran);
	
      }
      break;

    case SDL_MOUSEBUTTONUP:
      //cas où on va cliquer sur l'un des choix
      if (event.button.button == SDL_BUTTON_LEFT) {
	if ((event.button.x >= position1.x && event.button.x <= position1.x + choix1->w) &&
	    (event.button.y >= position1.y && event.button.y <= position1.y + choix1->h)) {
	  //si on clique sur aléatoire
	  choix = 'A';
	  continuer = 0;
	}
	else if ((event.button.x >= position2.x && event.button.x <= position2.x + choix2->w) &&
		 (event.button.y >= position2.y && event.button.y <= position2.y + choix2->h)){
	  //si on clique sur charger
	  choix = 'C';
	  continuer = 0;
	}
      }
      break;
    }
  }

  TTF_CloseFont(police);
  TTF_Quit();

  SDL_FreeSurface(titre);
  SDL_FreeSurface(dev);
  SDL_FreeSurface(choix1);
  SDL_FreeSurface(choix2);
  SDL_Quit();
  return choix;
}

void affichage(int **T,int **resolu, int N){

  SDL_Surface *ecran = NULL, *cellule = NULL, *celluleVide = NULL, *valeur = NULL, *gagne = NULL,
  *help = NULL;
  SDL_Rect position, positionVide, positionNbr;
  SDL_Event event;
  TTF_Font *police = NULL;
  SDL_Color noir = {0, 0, 0}, blanc = {255, 255, 255};
  char nombre[5] = "";
  int continuer = 1;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  TTF_Init();

  ecran = SDL_SetVideoMode(300, 300, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("TAQUIN", NULL);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 30, 30));
  
  cellule = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w / N - 2, ecran->h / N - 2, 32, 0, 0, 0, 0);
  //on crée une case

  celluleVide = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w / N - 2, ecran->h / N - 2, 32, 0, 0, 0, 0);
  SDL_FillRect(celluleVide, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  //on crée une case noire pour représenter la case vide
  //le "- 2" à l'assignation des tailles sert à créer les bordures noires autour des cases
  
  police = TTF_OpenFont("bodoni.ttf", 30);

  position.x = 0, position.y = 0;
  
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      
      if (T[i][j] == N*N) {
	SDL_BlitSurface(celluleVide, NULL, ecran, &position);
	positionVide.x = position.x;
	positionVide.y = position.y;
	//on garde la position de la case vide
      }
      else{
	SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	//on rempli la case de blanc
	sprintf(nombre, "%d", T[i][j]);
	valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
	positionNbr.x = cellule->w / 2 - valeur->w / 2;
	positionNbr.y = cellule->h / 2 - valeur->h / 2;
	SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
	SDL_Flip(cellule);
	// on écrit la valeur dans la case
	SDL_BlitSurface(cellule, NULL, ecran, &position);
      }
      position.x += ecran->w / N;// on se décale sur la droite
    }
    position.x = 0; // on se remet au début de la ligne
    position.y += ecran->h / N; //on descend d'une ligne
  }
  
  SDL_Flip(ecran);

  char prec = 'a'; //pour sauvegarder le coup précédent
  int x = 0, y = 0;//position case vide dans T

  while (T[x][y] != N*N) {//on récupère la position de la case vide
    y++;
    if (y == N) {
      y = 0, x++;
    }
  }
  int son = 0;
  
  while (continuer) {

    if (resolution(resolu, T, N) == 1) {
      police = TTF_OpenFont("bodoni.ttf", 40);
      gagne = TTF_RenderUTF8_Shaded(police, "Vous avez réussi !!", noir, blanc);
      position.x = ecran->w /2 - gagne->w /2;
      position.y = ecran->h /2 - gagne->h /2;
      SDL_BlitSurface(gagne, NULL, ecran, &position);
      SDL_Flip(ecran);
      
      Mix_Chunk *wave = NULL;
      if (son == 0) {// pour dire la phrase"bomb has been difused" en cas de réussite 
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024);
  
	wave = Mix_LoadWAV("bomb.wav");

	Mix_Volume(-1, MIX_MAX_VOLUME/2);
  
	Mix_PlayChannel(-1, wave, 0); 

	son = 1;
      }
 

      
	SDL_WaitEvent(&event);
	switch (event.type) {
      
	case SDL_QUIT:
	  continuer = 0;
	  
	Mix_FreeChunk(wave);
	Mix_CloseAudio();

	  break;
	}
      }

    else{
      switch (aide(resolu, T, N, x, y, prec)) {//affiche la case pour aider le joueur
      case 'H':
	SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 0, 100, 0));//on l'affiche en vert
	//on rempli la case de blanc
	sprintf(nombre, "%d", T[x - 1][y]);
	valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
	positionNbr.x = cellule->w / 2 - valeur->w / 2;
	positionNbr.y = cellule->h / 2 - valeur->h / 2;
	SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
	SDL_Flip(cellule);
	// on écrit la valeur dans la case
	position.x = positionVide.x;
	position.y = positionVide.y - cellule->h - 2;
	SDL_BlitSurface(cellule, NULL, ecran, &position);
	break;

      case 'B':
	SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 0, 100, 0));
	//on rempli la case de blanc
	sprintf(nombre, "%d", T[x + 1][y]);
	valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
	positionNbr.x = cellule->w / 2 - valeur->w / 2;
	positionNbr.y = cellule->h / 2 - valeur->h / 2;
	SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
	SDL_Flip(cellule);
	// on écrit la valeur dans la case
	position.x = positionVide.x;
	position.y = positionVide.y + cellule->h + 2;
	SDL_BlitSurface(cellule, NULL, ecran, &position);
	break;

      case 'G':
	SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 0, 100, 0));
	//on rempli la case de blanc
	sprintf(nombre, "%d", T[x][y - 1]);
	valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
	positionNbr.x = cellule->w / 2 - valeur->w / 2;
	positionNbr.y = cellule->h / 2 - valeur->h / 2;
	SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
	SDL_Flip(cellule);
	// on écrit la valeur dans la case
	position.x = positionVide.x - cellule->w - 2;
	position.y = positionVide.y;
	SDL_BlitSurface(cellule, NULL, ecran, &position);
	break;

      case 'D':
	SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 0, 100, 0));
	//on rempli la case de blanc
	sprintf(nombre, "%d", T[x][y + 1]);
	valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
	positionNbr.x = cellule->w / 2 - valeur->w / 2;
	positionNbr.y = cellule->h / 2 - valeur->h / 2;
	SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
	SDL_Flip(cellule);
	// on écrit la valeur dans la case
	position.x = positionVide.x + cellule->w + 2;
	position.y = positionVide.y;
	SDL_BlitSurface(cellule, NULL, ecran, &position);
	break;
      }

      SDL_Flip(ecran);
      SDL_WaitEvent(&event);
      switch (event.type) {
      
      case SDL_QUIT:
	continuer = 0;
	break;

      case SDL_KEYDOWN:
	if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_h) && x - 1 >= 0) {
	  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 30, 30));//on reset l'écran
	  x = haut(T, N, x, y);
	  prec = 'H';
	  position.x = 0;
	  position.y = 0;
	  // puis on ré-affiche le nouveau tableau
	  for (int i = 0; i < N; ++i) {
	    for (int j = 0; j < N; ++j) {
      
	      if (T[i][j] == N*N) {
		SDL_BlitSurface(celluleVide, NULL, ecran, &position);
		positionVide.x = position.x;
		positionVide.y = position.y;
		//on garde la position de la case vide
	      }
	      else{
		SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
		//on rempli la case de blanc
		sprintf(nombre, "%d", T[i][j]);
		valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
		positionNbr.x = cellule->w / 2 - valeur->w / 2;
		positionNbr.y = cellule->h / 2 - valeur->h / 2;
		SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
		SDL_Flip(cellule);
		// on écrit la valeur dans la case
		SDL_BlitSurface(cellule, NULL, ecran, &position);
	      }
	      position.x += ecran->w / N;// on se décale sur la droite
	    }
	    position.x = 0; // on se remet au début de la ligne
	    position.y += ecran->h / N; //on descend d'une ligne
	  }
	  
	}
	
	else if ((event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_b) && x + 1 <= N-1) {
	  x = bas(T, N, x, y);
	  prec = 'B';
	  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 30, 30));
	  position.x = 0;
	  position.y = 0;
	  for (int i = 0; i < N; ++i) {
	    for (int j = 0; j < N; ++j) {
      
	      if (T[i][j] == N*N) {
		SDL_BlitSurface(celluleVide, NULL, ecran, &position);
		positionVide.x = position.x;
		positionVide.y = position.y;
		//on garde la position de la case vide
	      }
	      else{
		SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
		//on rempli la case de blanc
		sprintf(nombre, "%d", T[i][j]);
		valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
		positionNbr.x = cellule->w / 2 - valeur->w / 2;
		positionNbr.y = cellule->h / 2 - valeur->h / 2;
		SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
		SDL_Flip(cellule);
		// on écrit la valeur dans la case
		SDL_BlitSurface(cellule, NULL, ecran, &position);
	      }
	      position.x += ecran->w / N;// on se décale sur la droite
	    }
	    position.x = 0; // on se remet au début de la ligne
	    position.y += ecran->h / N; //on descend d'une ligne
	  }
	  
	}
	
	else if ((event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) && y + 1 <= N-1) {
	  y = droite(T, N, x, y);
	  prec = 'D';
	  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 30, 30));
	  position.x = 0;
	  position.y = 0;
	  for (int i = 0; i < N; ++i) {
	    for (int j = 0; j < N; ++j) {
      
	      if (T[i][j] == N*N) {
		SDL_BlitSurface(celluleVide, NULL, ecran, &position);
		positionVide.x = position.x;
		positionVide.y = position.y;
		//on garde la position de la case vide
	      }
	      else{
		SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
		//on rempli la case de blanc
		sprintf(nombre, "%d", T[i][j]);
		valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
		positionNbr.x = cellule->w / 2 - valeur->w / 2;
		positionNbr.y = cellule->h / 2 - valeur->h / 2;
		SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
		SDL_Flip(cellule);
		// on écrit la valeur dans la case
		SDL_BlitSurface(cellule, NULL, ecran, &position);
	      }
	      position.x += ecran->w / N;// on se décale sur la droite
	    }
	    position.x = 0; // on se remet au début de la ligne
	    position.y += ecran->h / N; //on descend d'une ligne
	  }
	  
	}
	
	else if ((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_g) && y - 1 >= 0) {
	  y = gauche(T, N, x, y);
	  prec = 'G';
	  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 30, 30));
	  position.x = 0;
	  position.y = 0;
	  for (int i = 0; i < N; ++i) {
	    for (int j = 0; j < N; ++j) {
      
	      if (T[i][j] == N*N) {
		SDL_BlitSurface(celluleVide, NULL, ecran, &position);
		positionVide.x = position.x;
		positionVide.y = position.y;
		//on garde la position de la case vide
	      }
	      else{
		SDL_FillRect(cellule, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
		//on rempli la case de blanc
		sprintf(nombre, "%d", T[i][j]);
		valeur = TTF_RenderUTF8_Blended(police, nombre, noir);
		positionNbr.x = cellule->w / 2 - valeur->w / 2;
		positionNbr.y = cellule->h / 2 - valeur->h / 2;
		SDL_BlitSurface(valeur, NULL, cellule, &positionNbr);
		SDL_Flip(cellule);
		// on écrit la valeur dans la case
		SDL_BlitSurface(cellule, NULL, ecran, &position);
	      }
	      position.x += ecran->w / N;// on se décale sur la droite
	    }
	    position.x = 0; // on se remet au début de la ligne
	    position.y += ecran->h / N; //on descend d'une ligne
	  }
	}
      }
      SDL_Flip(ecran);
    }
  }

  TTF_CloseFont(police);
  TTF_Quit();

  SDL_FreeSurface(cellule);
  SDL_FreeSurface(celluleVide);
  SDL_FreeSurface(valeur);
  SDL_FreeSurface(gagne);
  SDL_FreeSurface(help);
  SDL_Quit();
}
