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

int main()
{
  int N;
  char souhait;
  printf("Saisissez la taille du tableau :");
  scanf("%d", &N);
  
  int **resolu = malloc(sizeof(int *) * N);//tableau résolu
  int **T = malloc(sizeof(int *)* N);//tableau a résoudre
  
  for (int i = 0; i < N; ++i) {
    resolu[i] = malloc(sizeof(int) * N);
  }
  
  for (int i = 0; i < N; ++i) {
    T[i] = malloc(sizeof(int)* N);
  }

  
  initialisation(resolu, N);
  souhait = menu();

   if (majuscule(souhait) == 'A') {//tableau généré aléatoirement
      initialisation(T, N);
      melange(T, N, N-1, N-1);
    }
    else if(majuscule(souhait) == 'C') lecture(T, N);//tableau charger depuis un fichier

   affichage(T, resolu, N);

  for (int i = 0; i < N; ++i) {
    free(resolu[i]);
  }
  for (int i = 0; i < N; ++i) {
    free(T[i]);
  }
  free(resolu);
  free(T);
  T = NULL;
  resolu = NULL;
  return 0;
}
