#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y,val;
  char nouveau_F[256];

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  val=lire_terrain(f, &t, &x, &y);
  while (val==ERREUR_FICHIER){
    printf("la lecture du fichier renvoie ERREUR_FICHIER\n");
    printf("choisissez un autre fichier :\n");
    fclose(f);
    scanf("%s",&nouveau_F);
    f = fopen(nouveau_F, "r");
    val=lire_terrain(f, &t, &x, &y);

    
  }
  fclose(f);
  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);
}
