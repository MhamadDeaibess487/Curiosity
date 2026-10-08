#include "generation_terrains.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "terrain.h"

int nb_cases_occupees(Terrain *T) {
  int occupee = 0;
  int x, y;
  for (x = 0; x < largeur(T); x++) {
    for (y = 0; y < hauteur(T); y++) {
      if (T->tab[x][y] != LIBRE)
        occupee++;
    }
  }
  return occupee;
}


float densite(Terrain *T, int l, int h){
  float cmpt =0.0;
  for (int i=0 ; i<l;i++){
    for(int j=0 ; j<h;j++){
      if(T->tab[i][j]!=LIBRE){
        cmpt+=1.0;
      }
    }
  }
  return cmpt/(l*h);
}
// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv) {
  int N, i, l, h;
  float dObst;
  FILE *resFile;
  Terrain T;
  srand(time(NULL)); 
  if (argc < 6) {
    printf(
        "Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[1], NULL, 10);
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);

  // test de l et h
  if (l > DIM_MAX || l % 2 == 0) {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h > DIM_MAX || h % 2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[5], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  
  // A compléter

  // A compléter
  float d;
  i=0;
  int nb_totale =0 ;
  int nb_reussi =0 ;
  float nb_obs=0.0;
  
  while(i<N){
    
    generation_aleatoire(&T,l,h,dObst);

    nb_totale++;
    if(existe_chemin_vers_sortie(&T)!=0){
      nb_reussi++;
      
      d = densite(&T,l,h);
      fprintf(resFile,"la densite du terrain est : %f \n",d);
      if (d<dObst-1.0){
        fprintf(resFile,"la densite obtenue est inferieur a la densite demander\n");
      }else if ( d>dObst+1.0){
        fprintf(resFile,"la densite obtenue est superieur a la densite demander\n");

      }else {
        fprintf(resFile,"la densite obtenue est a peut pres egale a la densite demander\n");

      }
      ecrire_terrain(resFile,&T,(int)l/2,(int)h/2);
      fprintf(resFile,"\n");
      i++;
      nb_obs+=d;
    }
  }
  printf("le nb de reussi est %d\n",nb_reussi);
  printf("le nb total est %d\n",nb_totale);
  fprintf(resFile,"la densite d'obstacle moyenne sur les terrains est : %f\n",nb_obs);
  fprintf(resFile,"le pourcentage de terrain valide est : %f\n", ((float)nb_reussi / nb_totale) * 100);


  // Génération aléatoire des terrains
  // Écriture des terrains générés dans le fichier resFile
  // Écriture/Affichage des statistiques

  // fermeture des fichiers
  fclose(resFile);
  return 0;
}
