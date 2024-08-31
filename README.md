# BabyRain

Binôme:
* Alexandre LECONTE
* Juliette BOURDIAU

# Mécanique principale du jeu
L'objectif est d'attrapper les bébés portées par le cygognes avec la poussette avant qu'ils atteignent le sol. Attention aux cygognes piégées !!

## La poussette
Le mouvement de la poussette est contrôlé par les touches Q (mouvement vers la gauche) et D (mouvement vers la droite).

## Les Cygognes classiques
Pour récupérer les bébés, il faut shooter les cygognes à l'aide de sa souris.

## Les Cygnognes piégées

# Conception

## Diagramme de classe
![diagramme](diag_de_classe.png)

# Bibliothèques externes

## [SFML](https://www.sfml-dev.org/)
Pour gérer la partie graphique et les interactions avec l'utilisateur dans le jeu.

## [Box2D](https://box2d.org/)
Permet d'utiliser des propriétés physiques dans le jeu.
1 unité sur Box2D correspond à 30 pixels dans SFML.