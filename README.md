# Curiosity — Simulation d'un robot explorateur en C

## Description

Projet universitaire de programmation en langage C inspiré du rover martien Curiosity.

L'objectif est de développer un environnement de simulation dans lequel un robot explore un terrain et exécute des programmes constitués d'instructions.

Le projet met en pratique la programmation modulaire, les structures de données dynamiques et la conception d'un interpréteur de langage.

## Fonctionnalités développées

### Simulation du robot

- Représentation d'un terrain.
- Gestion de la position et de l'orientation du robot.
- Déplacements et rotations.
- Exécution des instructions du programme.
- Détection des conditions d'arrêt et des erreurs d'exécution.

### Interpréteur d'instructions

Développement d'un interpréteur permettant de lire et d'exécuter des séquences d'instructions.

Les instructions étudiées comprennent notamment :

- Déplacement et rotation : `A`, `G`, `D`.
- Opérations arithmétiques : `+`, `-`, `*`.
- Manipulation de données à travers une pile.
- Instructions conditionnelles et blocs de programmes.
- Manipulation et exécution de séquences d'instructions.

### Gestion des structures de données

- Implémentation de piles.
- Manipulation de listes chaînées.
- Gestion dynamique de la mémoire.
- Représentation de programmes et sous-programmes.

### Génération et expérimentation

- Génération de terrains aléatoires.
- Configuration des dimensions et de la densité d'obstacles.
- Vérification de l'existence de chemins vers la sortie.
- Exécution de simulations avec un nombre maximal d'étapes.
- Collecte de résultats d'exécution.

## Technologies

- **Langage :** C
- **Compilation :** Makefile
- **Environnement :** Linux / terminal
- **Outils :** GCC ou Clang selon l'environnement

## Architecture du projet

Le projet est organisé en plusieurs modules :

| Module | Responsabilité |
|---|---|
| `robot` | Déplacements et orientation |
| `terrain` | Représentation du terrain |
| `environnement` | Gestion de la simulation |
| `programme` | Lecture et représentation des programmes |
| `interprete` | Interprétation et exécution |
| `type_pile` | Gestion de la pile |
| `observateur` | Observation des exécutions |
| `generation_terrains` | Génération aléatoire de terrains |

## Compilation

Le projet utilise un Makefile.

```bash
make
```

Les exécutables et leurs paramètres dépendent de la variante compilée.

## Concepts informatiques abordés

- Programmation procédurale et modulaire
- Pointeurs et allocation dynamique
- Structures et listes chaînées
- Piles et manipulation d'instructions
- Interprétation d'un langage
- Simulation algorithmique
- Gestion des erreurs
- Génération pseudo-aléatoire

## Contexte académique

Projet réalisé dans le cadre de l'UE INF304, en programmation C.

## Bilan

Ce projet a permis d'approfondir la programmation en C à travers la réalisation d'un interpréteur et d'un système de simulation.

Il mobilise des compétences en algorithmique, structures de données, gestion de la mémoire et décomposition d'un problème complexe en modules indépendants.
