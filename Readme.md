# Morpion 

## Description
Ce projet est un jeu de Morpion (Tic-Tac-Toe) développé en C utilisant la bibliothèque SDL2 pour l'affichage graphique. Le jeu oppose un joueur humain à un joueur contrôlé par une IA. L'IA utilise l'algorithme **Minimax** pour jouer de manière optimale.

## Fonctionnalités
- Mode de jeu 1v1 (humain contre IA).
- L'IA utilise Minimax pour maximiser ses chances de gagner.
- Détection des victoires et des égalités.

## Structure du projet
- `src/` : Contient le code source du projet.
  - `main.c` : Point d'entrée du programme.
  - `game.c` : Contient la logique du jeu (gestion du plateau, algorithme Minimax, etc.).
  - `render.c` : Contient les fonctions pour afficher le plateau et les résultats.
  - `test_game.c` : Tests unitaires pour le jeu.
  
- `include/` : Contient les fichiers d'en-tête.
  - `game.h` : Prototypes des fonctions du jeu.
  - `render.h` : Prototypes des fonctions d'affichage.

## Compilation et Exécution

### Prérequis
- SDL2 : Vous pouvez l'installer sur Ubuntu avec `sudo apt-get install libsdl2-dev`.
- CUnit (pour les tests unitaires) : Installez avec `sudo apt-get install libcunit1-dev`.

### Compilation
Pour compiler le projet :
```bash
make
```

### Exécution
Pour lancer le jeu :
```bash
./morpion
```

### Tests Unitaires
Pour exécuter les tests unitaires :
```bash
make test
```

## Algorithme Minimax
Le joueur IA utilise l'algorithme Minimax pour choisir les coups optimaux. L'algorithme évalue tous les coups possibles, cherche à maximiser les gains pour l'ordinateur tout en minimisant ceux du joueur.

## Auteurs
Projet développé dans le cadre de l'apprentissage du langage C et des algorithmes d'intelligence artificielle.