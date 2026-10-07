#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "terrain.h"
#include "generation_terrains.h"
#include "robot.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




// Fonction pour afficher la position d'une erreur dans le programme
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

// Fonction pour gérer les erreurs liées au programme
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

int main(int argc, char **argv) {
    Programme prog;
    erreur_programme errp;
    FILE *resFile,*fichier_programme;
    Terrain T;

    int N,L,H,graine,nb_step_max;
    float d; 
    
    int pas;
    int sorti=0,arret=0,eau=0,rocher=0,tot=0,tot_pas=0;

    if (argc < 9) {
        printf("Usage: %s <fichier_programme> <N> <L> <H> <d> <graine> <nb_step_max> <fichier_res>\n", argv[0]);
        return 1;
    }
    
    fichier_programme=fopen(argv[1],"r");
    N = strtol(argv[2], NULL, 10);
    L = strtol(argv[3], NULL, 10);
    H = strtol(argv[4], NULL, 10);
    d = strtof(argv[5], NULL);
    graine=strtol(argv[6],NULL,10);
    nb_step_max=strtol(argv[7],NULL,10);
    resFile=fopen(argv[8],"w");
    errp = lire_programme(&prog, argv[1]);
    gestion_erreur_programme(errp);
    // test de l et h
    if (L > DIM_MAX || L % 2 == 0) {
        printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
        return 1;
    }
    if (H > DIM_MAX || H % 2 == 0) {
        printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
        return 1;
    }
    if ((d> 1) || (d < 0)) {
        printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
        return 1;
    }

    // Initialisation de la fonction random
    srand(graine);

    // Ouverture du fichier résultat

    // Écriture du nombre de terrains
    fprintf(resFile, "%d\n", N);

    
    
    for (int i=0;i<N;i++){
        //printf("c'est le terrain numero %d\n",i);
	      Environnement envt;
	      etat_inter etat;
    	  resultat_inter res = OK_ROBOT;
        envt.r.o=Est;
        envt.r.x=L/2;
        envt.r.y=H/2 ;
        
        generation_aleatoire(&T,L,H,d);
        
        envt.t= T;
        
        
        

        /* Initialisation de l'état */
        
        init_etat(&etat);
        pas=0;
        
        while (res == OK_ROBOT && pas<nb_step_max){
        pas++;
        res = exec_pas(&prog, &envt, &etat);
        /* Affichage du terrain et du robot */
        //afficher_envt(&envt);
        } 
        
        
        

        /* Affichage du résultat */
        switch (res) {
        case SORTIE_ROBOT:
            fprintf(resFile,"%d\n",pas);
            sorti++;
            tot_pas=tot_pas+pas;
        break;
        case ARRET_ROBOT:
            fprintf(resFile,"-1\n");
            arret++;
            break;
        case PLOUF_ROBOT:
            fprintf(resFile,"-2\n");
            eau++;
            break;
        case CRASH_ROBOT:
            fprintf(resFile,"-3\n");
            rocher++;
            break;
        /*case ERREUR_PILE_VIDE:
            fprintf(resFile,"ERREUR_PILE_VIDE\n");
            break;
        case ERREUR_ADRESSAGE:
            fprintf(resFile,"ERREUR_ADRESSAGE\n");
            break;
        case ERREUR_DIVISION_PAR_ZERO:
            fprintf(resFile,"ERREUR_DIVISION_PAR_ZERO\n");
            break;*/
	      default:
	          fprintf(resFile, "-1\n");
            arret++;
            break;
            }
      tot+=pas;
      if (res!=SORTIE_ROBOT){
        printf("le terrain est :\n");
        afficher_envt(&envt);
        printf("\n");
      }
      
    }

    fclose(resFile);
    printf("Résultats pour %d terrains :\n", N);
    printf("Sorti avec succès : %d (%.1f%%)\n", sorti, 100.0 * sorti / N);
    printf("Bloqué : %d (%.1f%%)\n", arret, 100.0 * arret / N);
    printf("Tombé dans l'eau : %d (%.1f%%)\n", eau, 100.0 * eau / N);
    printf("Écrasé contre un obstacle : %d (%.1f%%)\n", rocher, 100.0 * rocher / N);
    if (sorti > 0) {
        printf("Nombre moyen de pas pour sortir : %.1f\n", (float)tot_pas / sorti);
    }
    
    return 0;
}