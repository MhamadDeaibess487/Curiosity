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
#include "observateur.h"


int main(int argc,char *argv[]){
    if(argc!=3){
        printf("pas assez d'argument\n");
        exit(1);
    }
    resultat_inter res;
    FILE *fichier_terrain,*fichier_programme;
    fichier_terrain=fopen(argv[1],"r");
    Terrain T;
    Programme prog;
    int x,y;
    int nbstepmax = 1000000;
    Environnement envt;
    lire_terrain(fichier_terrain,&T,&x,&y);
    initialise_environnement(&envt,argv[1]);
    fclose(fichier_terrain);
    fichier_programme = fopen(argv[2],"r");
    lire_programme(&prog,argv[2]);
    fclose(fichier_programme);

    etat_inter etat;
    




    //afficher_envt(&envt);

    init_etat(&etat);
    res = OK_ROBOT;
    for (int nbstep = 0; (nbstep < nbstepmax) && (res == OK_ROBOT); nbstep++) {
        res = exec_pas(&prog, &envt, &etat);
    /* Affichage du terrain et du robot */
        //afficher_envt(&envt);
    };

    /* Résultat de l’observateur */
    if (resultat_observateur(&envt)) {
        printf("Observateur : propriété valide\n");
    } else {
        printf("Observateur : propriété fausse !\n");
    }




}