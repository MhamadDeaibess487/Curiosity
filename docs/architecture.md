# Analyse technique du projet

## Périmètre et décisions

L’analyse couvre les 29 fichiers C, les 8 headers, l’unique Makefile, le README,
les notes, les programmes, les terrains et les scénarios du dépôt d’origine.
L’[inventaire](inventaire.md) donne le déplacement et le rôle de chaque fichier.
Les sources, headers et données déplacés restent identiques octet par octet.
Aucun algorithme ni résultat attendu d’un scénario n’a été réécrit pour obtenir
une suite verte. Les anciens rapports générés sont retirés du suivi Git et
conservés localement ; les notes et exemples de terrains commentés sont archivés.

La racine initiale mélangeait modules, interfaces, neuf exécutables déjà
compilés, rapports et données. La nouvelle séparation distingue les points
d’entrée (`apps`), les modules (`src`), leurs interfaces (`include`), les outils
et scénarios (`tests`) et l’explication du travail (`docs`). Les données restent
dans un même répertoire afin que les noms relatifs contenus dans les scénarios
restent valides. Les renommer ou les disperser aurait imposé des modifications
inutiles de leur contenu ou du lecteur C.

## Chaîne d’exécution

```text
terrain + programme
        ↓
initialise_environnement + lire_programme
        ↓
init_etat → exec_pas → environnement → robot + terrain
                ↓             ↓
         piles de données   observateur
         et de retours
```

`terrain.h` définit une grille `tab[x][y]` de capacité 256 × 256. L’origine
est en haut à gauche ; l’abscisse croît à droite et l’ordonnée vers le bas.
Le lecteur accepte des dimensions strictement inférieures à 256.
`robot.h` contient les coordonnées et l’une des quatre orientations.
La géométrie du robot est indépendante des collisions : celles-ci sont
effectuées par `environnement.c`. Une sortie/eau/collision est signalée avant
de déplacer le robot dans la case problématique.

`programme.c` lit les instructions dans un tableau de commandes et associe
les ouvertures/fermetures de blocs via une pile auxiliaire. Les espaces sont
ignorés et `#` démarre un commentaire jusqu’à la fin de ligne. `interprete.c`
maintient le compteur de programme et deux piles : valeurs/adresses de blocs,
et adresses de retour. Les blocs sont empilés sans exécution immédiate.
`type_pile.c` utilise un tableau fixe ; ce n’est pas une liste chaînée.
Les allocations dynamiques visibles servent aux messages d’erreur du lecteur.

## Langage effectivement présent

| Instruction | Effet de l’interprète principal |
| --- | --- |
| `A`, `G`, `D` | Avancer, tourner à gauche, tourner à droite |
| entier | Empiler une valeur entière |
| `M` | Dépiler une direction de mesure et empiler son résultat |
| `{ ... }`, `!` | Empiler une adresse de bloc, puis exécuter un bloc dépilé |
| `?` | Dépiler bloc faux, bloc vrai et condition ; exécuter le bloc choisi |
| `+`, `-`, `*`, `/` | Arithmétique sur les deux valeurs du sommet |
| `X`, `C`, `I` | Échanger, dupliquer, retirer le sommet |
| `R` | Rotation des valeurs avec nombre d’éléments et pas dépilés |
| `B` | Répétition d’un bloc avec compteur |
| `P` | Instruction reconnue, sans action de marquage |

La mesure accepte les directions 0 à 8 : sur place, devant, devant-droite,
droite, derrière-droite, derrière, derrière-gauche, gauche, devant-gauche.
Ses résultats sont 0 (libre), 1 (eau), 2 (rocher) et 3 (paramètre incorrect).
La promesse des commentaires « hors terrain = libre » n’est pas correctement
protégée dans l’implémentation : les indices calculés sont utilisés sans garde.
Le lecteur reconnaît un signe `-` suivi de chiffres, mais empile leur valeur
positive ; ne pas présenter les nombres négatifs comme une fonctionnalité fiable.

## Observateurs et variantes

`environnement.c` émet l’événement `M` uniquement pour une mesure devant (1).
`observateur.c` refuse un avancement sans cet événement immédiatement disponible ;
une rotation après mesure consomme cet état. `environnement_alt.c` émet `M`
pour une mesure à gauche (7), et `observateur2.c` refuse une rotation gauche
sans mesure disponible. L’état d’erreur est absorbant et la validation finale
teste simplement que cet état n’a pas été atteint. Les deux points d’entrée
`curiosity-obs.c` et `curiosity-obs2.c` sont identiques ; le lien des modules
sélectionne la propriété contrôlée. Ils limitent leur boucle à 1 000 000 de pas.

Les différences suivantes proviennent de la comparaison des instructions C,
après exclusion des commentaires et des lignes vides. Leur intention exacte
n’est pas documentée dans le dépôt ; elles s’apparentent à des mutations
pédagogiques pour éprouver les tests.

| Fichier dans `src/variants/` | Différence avec `interprete.c` |
| --- | --- |
| `interprete0.c` | `C` ajoute deux copies au lieu d’une |
| `interprete1.c` | Instructions équivalentes à l’interprète principal |
| `interprete2.c` | `X` réempile les valeurs dans leur ordre initial |
| `interprete3.c` | La mesure reçoit `param % 8` |
| `interprete4.c` | Le bloc faux reçoit aussi l’adresse du bloc vrai |
| `interprete5.c` | Le début de bloc empile deux fois son adresse |
| `interprete6.c` | Les résultats eau et rocher sont échangés |
| `interprete7.c` | Instructions équivalentes à l’interprète principal |
| `interprete8.c` | La boucle exécute aussi le bloc quand le compteur vaut zéro |
| `interprete9.c` | La soustraction calcule `a - b` au lieu de `b - a` |

Le Makefile initial proposait `curiosity-test%` mais omettait `observateur.o`,
nécessaire à l’environnement : ces variantes ne se liaient plus correctement
avec ce Makefile. Le nouveau lien ajoute ce module sans modifier les variantes.
Les pseudo-exécutables `observateur`, `observateur2`, `environnement`,
`environnement_alt` et `generation_terrains` de l’ancien Makefile n’avaient
pas de `main` ; ils restent des modules, pas des programmes autonomes annoncés.

## Génération et expérimentation

`generation_aleatoire` part d’une grille libre et ajoute aléatoirement eau ou
rochers jusqu’à la densité visée, sans occuper le centre. `existe_chemin_vers_sortie`
utilise un tableau de marques et recherche une connexion entre centre et bord.
Le test de génération conserve les terrains ayant un chemin ; le programme
`curiosity-perf` simule directement les terrains produits sans ce filtrage.
Le premier initialise l’aléatoire avec l’heure ; le second accepte une graine.
Le simulateur principal n’a pas de limite de pas, contrairement aux scénarios,
aux observateurs et à l’outil d’expérimentation.

## Défauts existants à traiter séparément

Ces constats ne sont pas corrigés par la réorganisation afin de préserver les
algorithmes et le comportement. Les reproductions confirmées sont dans
[le bilan](validation.md) ; les autres points sont issus de la lecture du code.

| Zone | Constat et conséquence |
| --- | --- |
| `terrain.c` | Lectures et longueurs de lignes incomplètement contrôlées ; absence de `C` acceptée avec coordonnées -1 ; plusieurs erreurs détaillées du header ne sont jamais produites |
| `terrain.c` | `ecrire_terrain` n’écrit pas les dimensions, malgré le commentaire annonçant un format relisible |
| `programme.c` | Signe négatif perdu ; capacités programme/pile non contrôlées ; descripteurs et messages d’erreur non libérés |
| `type_pile.c`, `interprete.c` | Empilement sans contrôle de capacité ; paramètres de rotation non validés pouvant produire des indices invalides |
| `environnement*.c` | Mesures hors grille sans contrôle des bornes ; fichier non fermé lors d’une erreur d’initialisation |
| `generation_terrains.c` | Densité trop élevée incompatible avec centre libre, pouvant empêcher la terminaison ; dimensions non positives non protégées |
| `generation_terrains.c` | Recherche de chemin : remise de `x` à 1 au changement de ligne et absence de tests `x1 >= 0`, `y1 >= 0` |
| `curiosity-perf.c` | État d’observateur non initialisé dans l’environnement construit manuellement ; ouverture de fichier résultat et `N > 0` non validés |
| `test_generation_terrains.c` | Tolérance de densité ±1 peu informative ; somme des densités présentée comme moyenne ; répétition non bornée si aucun terrain acceptable n’est produit |
| `curiosity-test.c` | `fscanf` non vérifiés et chaînes sans largeur ; résultats incohérents renvoyés avec code zéro ; événement `N` sans contrôle explicite de `OK_ROBOT` |
| Outils interactifs | EOF de `scanf` non traité ; relance possible en boucle ; `test_terrain` peut appeler `fclose(NULL)` |
| Observateurs CLI | Résultats de lecture non vérifiés ; propriétés affichées sans code de retour distinct pour une violation |

GCC signale également le type de pointeur du `scanf` dans `test_terrain`,
l’absence de retour sur tous les chemins des deux fonctions `transition`,
et une variable fichier inutilisée dans `curiosity-perf`. Les exécutions réussies
ne constituent pas une preuve d’absence de comportement indéfini. Une future
correction mérite une branche dédiée, des cas limites et des vérifications
avec sanitizers plutôt qu’une modification cachée dans ce rangement.
