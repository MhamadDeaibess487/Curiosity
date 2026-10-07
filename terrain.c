
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
  int l=0, h=0;   // Dimensions du terrain
  int rx=-1, ry=-1; // Coordonnées initiales du robot
  char c[DIM_MAX];


  if (f == NULL) {
    return ERREUR_FICHIER;
  }

  // Lecture de la largeur
  if((fscanf(f,"%d",&l)==0)||(l<=0)||(l>=DIM_MAX)){
    return ERREUR_FICHIER;
  }
  t->largeur=l;

  // Lecture de la hauteur
  if((fscanf(f,"%d",&h)==0)||(h<=0)||(h>=DIM_MAX)){
    return ERREUR_FICHIER;
  }
  t->hauteur=h;

  // Lecture du terrain
  for(int j=0;j<h;j++){
   fscanf(f, "%255s", c);

    for(int i=0;i<l;i++){
      
      if(c[i]=='.'){
        t->tab[i][j]=LIBRE;
      }else if(c[i]=='#'){
        t->tab[i][j]=ROCHER;
      }else if(c[i]=='~'){
        t->tab[i][j]=EAU;
      }else if (c[i]== 'C'){
        t->tab[i][j]=LIBRE;
        rx=i;
        ry=j;
      }else{
        return ERREUR_FICHIER;
      }
    }
  }

  // Initialisation de la position du robot
  *x=rx;
  *y=ry;

  return OK;
}

/* À compléter */

int largeur(Terrain *t){
  return t->largeur;
}

int hauteur(Terrain *t){
  return t->hauteur;
}

int est_case_libre(Terrain *t, int x, int y){
  if(x>=0 && x<largeur(t)){
    if(y>=0 && y< hauteur(t)){
      if(t->tab[x][y]==LIBRE){
        return 1;
      }
    }
  }
  return 0;
}


void afficher_terrain(Terrain *t){
  for(int j=0;j<hauteur(t);j++){
    for(int i=0;i<largeur(t);i++){
      if(t->tab[i][j]==LIBRE){
        printf(".");
      }else if(t->tab[i][j]==ROCHER){
        printf("#");
      }else if(t->tab[i][j]==EAU){
        printf("~");
      }else {
        printf("!");
      }
    }
    printf("\n");
  }
}

void ecrire_terrain(FILE *f, Terrain *t, int x, int y){
  for(int j=0;j<hauteur(t);j++){
    for(int i=0;i<largeur(t);i++){
      if(i==x && j==y){
        fprintf(f,"%s","C");
      }else if(t->tab[i][j]==LIBRE){
        fprintf(f,"%s",".");
      }else if(t->tab[i][j]==ROCHER){
        fprintf(f,"%s","#");
      }else if(t->tab[i][j]==EAU){
        fprintf(f,"%s","~");
      }
    }
    fprintf(f,"%s","\n");
  }
}