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

#include <time.h>

void initialisation(int ** T, int N){
  int compt = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      T[i][j] = ++compt;
    }

  }

}

void affiche(int **T, int N){
  
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      
      if (T[i][j] == N*N) {
	printf("   ");
      }
      
      else {
	
	if (T[i][j] < 10) {
	  printf(" %d ", T[i][j]);
	}
	else printf("%d ", T[i][j]);
      }
    }
      printf("\n");
  }

}

void melange(int **T, int N, int x, int y){
  srand(time(NULL));
  for (int i = 0; i < 100; ++i) {
    int nbr = rand()%4;
    switch (nbr) {
	
    case 0: {
      if (y - 1 >= 0) y = gauche(T, N, x, y);
      else i--;
      break;
    }

    case 1:{
      if (y + 1 <= N-1) y = droite(T, N, x, y);
      else i--;
      break;
    }

    case 2:{
      if (x + 1 <= N-1) x = bas(T, N, x, y);
      else i--;
      break;
    }

    case 3:{
      if (x - 1 >= 0) x = haut(T, N, x, y);
      else i--;
      break;
    }
	
    }
      
  }
}

int resolution(int **resolu, int ** T, int N){
  int continuer = 1;
  int i = 0, j = 0;
  while(continuer == 1 && !(i == N-1 && j == N-1)){
    //on parcours les tableaux tant que leur coefficient sont égaux
    if (resolu[i][j] != T[i][j]) continuer = 0;

    else{
      if (j == N-1 && i != N-1) {
	j = 0;
	i++;
      }
      else j++;
    }
  }
  return continuer;//1 si tous les coef sont égaux sinon 0
}

int majuscule(int carac){
  
        if (carac  >= 97 &&  carac <= 122) 
            carac = carac - 32;

    return carac;
}

void lecture(int **T, int N){
  int i = 0;
  char ligne[50] = "";
  FILE *fp = fopen("tableau.txt", "r");
  
  while(fgets(ligne, 50, fp)){// on récupère ligne par ligne du fichier
    int j = 0;
    int pos = 0;//position sur la ligne du fichier

    for (j = 0; j < N; ++j) {//on avance sur les colonnes du tableau
      char tmp[3] = "";
      
      if (ligne[pos] >= 48 && ligne[pos] <= 57) {//cas d'un chiffre
	tmp[0] = ligne[pos];
	pos++;
      
	if (ligne[pos] >= 48 && ligne[pos + 1] <= 57) {//cas d'un nombre inférieur à 100
	  tmp[1] = ligne[pos];
	  pos++;
	}
	T[i][j] = atoi(tmp);
      }
      else if(ligne[pos] == 32){//cas pour l'espace vide(représenté par un espace)
	T[i][j] = N*N;
	pos++;
      }
      pos++;//on saute l'espace entre chaque valeurs
    }
    i++;//on avance sur les lignes du tableau
  }
  fclose(fp);
}
