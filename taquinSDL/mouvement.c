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

int haut(int **T, int N, int x, int y){
  int change = T[x - 1][y];
  int tmp = N*N;
  T[x - 1][y] = tmp;
  T[x][y] = change;
  return x - 1;
}

int bas(int **T, int N, int x, int y){
  int change = T[x + 1][y];
  int tmp = N*N;
  T[x + 1][y] = tmp;
  T[x][y] = change;
  return x + 1;
}

int gauche(int **T, int N, int x, int y){
  int change = T[x][y - 1];
  int tmp = N*N;
  T[x][y - 1] = tmp;
  T[x][y] = change;
  return y - 1;
}

int droite(int **T, int N, int x, int y){
  int change = T[x][y + 1];
  int tmp = N*N;
  T[x][y + 1] = tmp;
  T[x][y] = change;
  return y + 1;
}
