#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mouvement.h"
#include "fonction_importante.h"


char aide(int **resolu,int **T, int N, int x, int y, char prec){
  //cette fonction proposera un coup au joueur en fonction des coups possible
  //on va chercher le coup qui rapproche le plus la case déjà proche de sa position voulu
  char coup;
  int min = N;
  
  if (x - 1 >= 0 && prec != 'B') {
    int x1 = 0, y1 = 0;
    int valeur = T[x - 1][y];//valeur de la case du dessus

    while(valeur != resolu[x1][y1]){//on récupère la position voulu de la valeur 
      y1++;
      if (y1 == N) {//on change de ligne
	y1 = 0;
	x1 ++;
      }
    }
    
    if ((x - 1 != x1) && x - x1 <= 0) {
      //on vérifie si la case n'est pas à sa position et il faut la descendre
      if (abs(x - x1) < min) {
	min = abs(x - x1);
	coup = 'H';
      }
    }
  }
  
  if (x + 1 <= N-1 && prec != 'H') {

    int x1 = 0, y1 = 0;
    int valeur = T[x + 1][y];//valeur de la case du dessus

    while(valeur != resolu[x1][y1]){//on récupère la position voulu de la valeur 
      y1++;
      
      if (y1 == N) {//on change de ligne
	y1 = 0;
	x1 ++;
      }
    }
    
    if ((x + 1 != x1) && x - x1 >= 0) {
    //on vérifie si la case n'est pas à sa position et si il faut la monter
      if (abs(x - x1) < min) {
	min = abs(x - x1);
	coup = 'B';
      }
    }
    
  }
  
  if (y - 1 >= 0 && prec != 'D') {

    int x1 = 0, y1 = 0;
    int valeur = T[x][y - 1];//valeur de la case du dessus

    while(valeur != resolu[x1][y1]){//on récupère la position voulu de la valeur 
      y1++;
      
      if (y1 == N) {//on change de ligne
	y1 = 0;
	x1 ++;
      }
    }
    
    if ((y - 1 != y1) && y - y1 <= 0) {
    //on vérifie si la case n'est pas à sa position et si il faut la déplacer à droite
	
      if (abs(y - y1) < min) {
	min = abs(y - y1);
	coup = 'G';
      }
    }
    
  }
  
  if (y + 1 <= N-1 && prec != 'G') {

    int x1 = 0, y1 = 0;
    int valeur = T[x][y + 1];//valeur de la case du dessus

    while(valeur != resolu[x1][y1]){//on récupère la position voulu de la valeur 
      y1++;
      
      if (y1 == N) {//on change de ligne
	y1 = 0;
	x1 ++;
      }
    }
    
    if ((y + 1 != y1) && y - y1 >= 0) {
    //on vérifie si la case n'est pas à sa position et si il faut la déplacer à gauche
      if (abs(y - y1) < min) {
	min = abs(y - y1);
	coup = 'D';
      }
    }
  }
  return coup;
}

//Fonction utilisée dans le taquin version Terminal linux remplacé par les saisie claviers possibles avec le SDL

/*void jeu(int **resolu, int ** T, int N){
  int x = 0;
  int y = 0;
  int continuer = 1;
  for (int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j){
      if (T[i][j] == N*N) x = i, y = j;// on récupère la position de la case vide
    }
  }
  
  while(continuer == 1){
    affiche(T, N);
    if (resolution(resolu, T, N) == 1) printf("BRAVO VOUS AVEZ RÉUSSI !!!!\n"), continuer = 0;

    else {
      char coup;
      while ((coup = getchar()) != '\n' && coup != EOF);//vide stdin
      char coupPossible[100] = "Quel déplacement souhaitez-vous faire ";
      char mouv[5] = "";//sauvegarder les coups possibles
      // on vérifie d'abord les coup possible

      if (y + 1 <= N -1){
	strcat(coupPossible, "(D)roite ");
	strcat(mouv, "D");
      }
      
      if (y - 1 >= 0) {
	strcat(coupPossible, "(G)auche ");
	strcat(mouv, "G");
      }
      
      if (x + 1 <= N -1){
	strcat(coupPossible, "(B)as ");
	strcat(mouv, "B");
      }
      if (x - 1 >= 0){
	strcat(coupPossible, "(H)aut ");
	strcat(mouv, "H");
      }
      
      printf("%s? ", coupPossible);
      coup = getchar();

      if (majuscule(coup) == 'G' && strchr(mouv, majuscule(coup)) != NULL) {//on vérifie si le coup est valide

	y = gauche(T, N, x, y);
      }
      
      else if (majuscule(coup) == 'D' && strchr(mouv, majuscule(coup)) != NULL) {
	y = droite(T, N, x, y);
      }
      
      else if (majuscule(coup) == 'H' && strchr(mouv, majuscule(coup)) != NULL) {
	x = haut(T, N, x, y);
      }
      
      else if (majuscule(coup) == 'B' && strchr(mouv, majuscule(coup)) != NULL) {
	x = bas(T, N, x, y);
      }
      else printf("Vous n'avez pas sélectionné de coup valide.\n");
    }
  }
}*/