﻿
# Bienvenue sur DbHandball !!!
# Gautier VAULOUP 3SI5

![DbHandball](logo.png)

## Mon Application de Gestion de Championnat

Cette application permet de gérer des championnats sportifs, incluant la création d'équipes, l'ajout de joueurs et la mise à jour des statistiques. Tout en garantissant la sécurité grâce au chiffrement des fichiers de sauvegarde.

<br><br>

## Table des Matières
1. [Installation](#installation)
2. [Utilisation](#utilisation)
3. [Explications des choix](#explications)

<br><br>

## Installation

1. Clonez ce projet :
    ```bash
    git clone https://github.com/Gautierrr/DbProject.git
    ```

2. Assurez-vous que les bibliothèques/dépendances nécessaires sont installées :
    - Gcc pour compiler le projet :
      ```bash
      sudo apt install gcc
      ```
    - OpenSSL pour le chiffrement :
      ```bash
      sudo apt-get install libssl-dev
      ```
    - Valgrind pour l'analyse des fuites de mémoire :
      ```bash
      sudo apt install valgrind
      ```

3. Désormais vous pouvez utiliser le Makefile :
    - Compiler le programme :
      ```bash
      make
      ```
    - Analyse valgrind du programme :
      ```bash
      make valgrind
      ```
    - Supprimer l'application :
      ```bash
      make clean
      ```

4. L'application est maintenant prête à être utilisée !

<br><br>

## Utilisation

1. Démarrez l'application :
    ```bash
    ./dbHandball
    ```

2. Suivez le tutoriel pour comprendre comment utiliser l'application.

3. Vous pourrez ajouter des équipes et des joueurs via leur interfaces respectives.

4. Enfin, les données pourront être sauvegardées puis chargées à partir d'un fichier JSON chiffré avec le mot de passe de votre choix.

<br><br>

## Explications

1. Version de gcc:
    ```bash
    gcc 13.2.0

2. Les Compiler Flags (CFLAGS):
    - Inclut les informations de débogage utiles pour l'utilisation de valgrind :
    ```bash
    -g
    ```
    - Active le maximum d'avertissements possible :
    ```bash
    -Wall
    ```

3. Le bonus avec les sorties de l'outil valgrind se trouvent dans le dossier valgrind.

4. J'ai choisis d'utiliser des arbres binaires de type AVL afin de faciliter l'équilibrage automatique tout en gardant une efficacité des opérations.

<br><br>

# Amusez-vous bien avec DbHandball !!!
