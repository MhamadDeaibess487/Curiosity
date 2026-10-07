#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "terrain.h"
#include "robot.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void gestion_erreur_terrain(erreur_terrain e) {
  switch (e) {
  case OK:
    break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE :
    printf("Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}


void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}


void gestion_erreur_programme(erreur_programme e) {
  switch (e.type_err) {
  case OK_PROGRAMME:
    break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}


int verif_evenement(char e, resultat_inter res){
  switch (e)
  {
    case 'O':
        if (res != CRASH_ROBOT) {
        printf("le robot n'etait pas cense rencontrer un obstacle\n");
        return 1;
        }
        break;
    case 'S':
        if (res != SORTIE_ROBOT) {
        printf("le robot n'etait pas cense sortir du terrain\n");
        return 1;
        }
        break;
    case 'F':
        if (res != ARRET_ROBOT) {
        printf("le programme n'etait pas cense se terminer\n");
        return 1;
        }
        break;
    case 'P':
        if (res != PLOUF_ROBOT) {
        printf("le robot n'etait pas cense tomber dans l'eau\n");
        return 1;
        }
        break;
  }
  return 0;
}


char orientation_char(Orientation orientation) {
    switch (orientation) {
        case Nord: return 'N';
        case Sud: return 'S';
        case Est: return 'E';
        case Ouest: return 'O';
        default: return '?'; 
    }
}


int verif_position_orientation(Environnement envt, char o_attendue, char e, int x_attendu, int y_attendu) {
    if (e=='N'||e=='F'){
        if (envt.r.x != x_attendu || envt.r.y != y_attendu) {
            printf("Position incorrecte du robot. Attendue : (%d, %d), Obtenu : (%d, %d)\n",
                   x_attendu, y_attendu, envt.r.x, envt.r.y);
            return 1;
        }

        Orientation o_enum;
        switch (o_attendue) {
            case 'N': o_enum = Nord; break;
            case 'S': o_enum = Sud; break;
            case 'E': o_enum = Est; break;
            case 'O': o_enum = Ouest; break;
            default: o_enum = Nord;
        }

        if (envt.r.o != o_enum) {
            printf("Erreur : Orientation incorrecte du robot. Attendue : %c, Obtenu : %c\n",
                   o_attendue, orientation_char(envt.r.o));
            return 1;//l'orientattin est incorrecte.
        }
    }
    return 0;//la position et l'orientation sont correctes.
}



int main(int argc, char **argv) {
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;

  FILE *f;
  char ter[100];
  char pro[100];
  unsigned int max;
  char e;
  int x,y;
  char o;
  if (argc!=2) {
    printf("nombre d'arguments incorrect.");
    return -1;
  }

  
  f=fopen(argv[1], "r");
  if (f==NULL){
    printf("impossible d'ouvrir le fichier. %s\n", argv[1]);
    return -1;
  }
  
  fscanf(f,"%s\n",ter); //fichier terrain.
  fscanf(f,"%s\n",pro); //fichier programme.
  fscanf(f,"%d\n",&max); //nombre maximum d'execution.
  fscanf(f,"%c\n",&e); //evenement final (S N F O P).
  if (e=='N'||e=='F'){
    fscanf(f, "%d %d\n",&x,&y); //coordonees attendues x y.
    fscanf(f,"%c",&o); //orientation attendue (N S E O).
  }
  fclose(f);

  /*Initialisation de l'environnement : lecture du terrain, initialisation de la position du robot*/
  errt = initialise_environnement(&envt, ter);
  gestion_erreur_terrain(errt);

  /*Lecture du programme*/
  errp = lire_programme(&prog, pro);
  gestion_erreur_programme(errp);

  /* Initialisation de l'état */
  init_etat(&etat);
  int i=0;
  do {
    i++;
    res = exec_pas(&prog, &envt, &etat);
    /*Affichage du terrain et du robot*/
    afficher_envt(&envt);
  } while (res == OK_ROBOT && i < max);


  printf("l'abssice est: %d\n",envt.r.x);
  printf("l'ordonnée est: %d\n",envt.r.y);
  printf("l'orientation est: %c\n",orientation_char(envt.r.o));

 
  if (e=='N'||e=='F'){
    if ((0==verif_evenement(e,res)) && (0 == verif_position_orientation(envt,o,e,x,y))){
        printf("OK\n");
    }
  }
  else{
    if(verif_evenement(e,res) == 0){
        printf("OK\n");
    }
  }
 return 0;
}