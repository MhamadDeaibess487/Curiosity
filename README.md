# Curiosity — Simulation d’un robot explorateur en C

Projet universitaire réalisé dans le cadre de l’UE INF304. Curiosity simule un
robot sur une grille et interprète des programmes écrits dans un petit langage
à pile. Le projet illustre la programmation modulaire en C, l’interprétation
d’instructions, les automates d’observation et la recherche de chemins.

## Fonctionnement

Un terrain contient des cases libres (`.`), des rochers (`#`), de l’eau (`~`) et
une position initiale (`C`). Le robot démarre orienté vers l’est. Le simulateur
affiche son évolution et s’arrête lorsque le programme se termine, que le robot
sort du terrain, rencontre un rocher ou de l’eau, ou que l’interprète détecte une
erreur (pile vide, adressage incorrect ou division par zéro).

Le langage permet les déplacements, les mesures du voisinage, les opérations
arithmétiques et de pile, les blocs, les conditions et les boucles. Le générateur
produit des terrains aléatoires en gardant la case centrale libre. Un outil
d’expérimentation exécute un programme sur plusieurs terrains avec une graine
et un nombre maximal de pas, puis écrit les résultats dans un fichier.

Deux observateurs contrôlent des propriétés de séquencement des actions :
mesurer devant avant d’avancer, ou mesurer à gauche avant de tourner à gauche.
Les dix variantes d’interprète du travail pédagogique sont conservées ; elles
ne constituent pas dix nouvelles fonctionnalités. Leurs différences sont
présentées dans [l’analyse technique](docs/architecture.md).

## Compilation

Prérequis : Linux ou environnement POSIX, GNU Make et GCC ou Clang.
Python 3 est utilisé uniquement par le lanceur de vérification.
Aucune bibliothèque externe ni connexion réseau n’est nécessaire.

Depuis la racine du dépôt :

```sh
make -j2                  # neuf exécutables principaux
make variants -j2         # dix variantes supplémentaires
make curiosity-test6     # une variante particulière
make clean               # supprime uniquement build/
make CC=gcc              # choix explicite du compilateur
# make clean && make CC=clang   # si Clang est installé
```

Les exécutables se trouvent dans `build/bin/`, les objets et dépendances dans
`build/`. Lors d’un changement de compilateur ou de flags, commencer par
`make clean`. Les dépendances des headers sont suivies automatiquement.

## Exemples d’utilisation

Depuis la racine du dépôt, simulation d’une sortie du terrain :

```sh
./build/bin/curiosity tests/fixtures/terrain_1.txt tests/fixtures/simple1.prg
```

La dernière ligne attendue est `Le robot est sorti :-)`.

```sh
# Déplacements interactifs : a = avancer, g = gauche, d = droite, f = fin
./build/bin/robot_terrain tests/fixtures/terrain_1.txt

# Vérification de l’observateur principal, sans affichage pas à pas
./build/bin/curiosity-obs tests/fixtures/terrain_1.txt tests/fixtures/simple1.prg

# Trois simulations sur terrains libres 5 × 5, graine 1, au plus 20 pas
./build/bin/curiosity-perf tests/fixtures/simple1.prg 3 5 5 0 1 20 build/resultats.txt

# Trois terrains libres 5 × 5 avec recherche d’un chemin vers le bord
./build/bin/test_generation_terrains 3 5 5 0 build/terrains.txt
```

`curiosity-perf` attend : programme, nombre de terrains, largeur, hauteur,
densité d’obstacles, graine, limite de pas et fichier de résultats. La première
ligne du résultat contient le nombre de terrains ; les suivantes contiennent
le nombre de pas pour une sortie, `-1` pour un arrêt/autre résultat, `-2` pour
l’eau ou `-3` pour un rocher. Utiliser des dimensions positives impaires et
une faible densité ; les limites du générateur sont détaillées dans l’analyse.
Les fichiers produits par le test de génération sont des rapports comprenant
des grilles ; ils ne sont pas directement des terrains d’entrée du simulateur.

Les scénarios de `curiosity-test` référencent des fichiers voisins. Les lancer
depuis leur répertoire :

```sh
(cd tests/fixtures && ../../build/bin/curiosity-test test1.txt)
(cd tests/fixtures && ../../build/bin/curiosity-test6 test2.txt)
```

La variante 6 échange les résultats eau/rocher : le second exemple illustre
une différence détectée par le scénario, pas un test attendu comme réussi.

## Organisation

```text
apps/               Entrées des simulateurs et du robot interactif
src/                Modules C communs et deux implémentations d’observateur
src/variants/       Dix variantes pédagogiques de l’interprète
include/            Interfaces des modules
tests/              Outils C historiques et lanceur Python
tests/fixtures/     Terrains, programmes et scénarios existants
docs/               Analyse technique, inventaire et résultats de validation
docs/archives/      Notes originales du travail universitaire
build/              Fichiers générés, ignorés par Git
```

| Module | Responsabilité |
| --- | --- |
| `robot` | Position, orientation, rotations et déplacement géométrique |
| `terrain` | Lecture et affichage de la grille, accès aux cases libres |
| `environnement` | Robot sur terrain, collisions, mesures et observation |
| `programme` | Lecture du langage et association des délimiteurs de blocs |
| `interprete` | Exécution pas à pas, pile de données et pile de retours |
| `type_pile` | Pile d’entiers dans un tableau de taille fixe |
| `observateur` / `observateur2` | Automates de contrôle des actions |
| `generation_terrains` | Génération aléatoire et recherche d’un chemin |

Les structures principales sont des tableaux de taille fixe ; le projet
n’implémente pas de listes chaînées. La capacité du programme est de 10 000
commandes et celle d’une pile de 999 entiers.

## Vérifications et limites connues

```sh
make smoke    # 12 contrôles représentatifs : simulation, outils et fichiers produits
make test     # vérification étendue, affiche aussi les échecs historiques
```

La réorganisation conserve les sources C, les headers et les données à
l’identique. Les neuf exécutables et les dix variantes compilent avec GCC.
Les 51 exécutions déterministes comparées avant/après ont des sorties et codes
de retour identiques.

La suite étendue rapporte actuellement **15 contrôles réussis et 4 échecs** :
les scénarios `test5`, `test6`, `test7` et `test8` ne correspondent pas à leurs
attentes. `test9` omet des coordonnées et expose des variables non initialisées
du runner C ; il est conservé mais exclu de la suite reproductible.
Le lanceur historique peut retourner zéro malgré un échec ; le lanceur Python
vérifie donc aussi les messages et retourne une erreur si une attente échoue.

L’instruction `P` est reconnue mais son action de marquage n’est pas implémentée.
Des contrôles de limites, de lecture et de fichiers restent incomplets. Cette
réorganisation ne corrige pas ces algorithmes et ne prétend pas que tous les
tests passent. Voir [l’analyse](docs/architecture.md),
[l’inventaire](docs/inventaire.md) et [le bilan de validation](docs/validation.md).
