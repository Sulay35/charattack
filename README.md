# Char GPT : AI playing Tank game
IA qui jour au jeu tank [Tank](https://en.wikipedia.org/wiki/Tank_(video_game))

Modèle d'IA : Q Learning apprentissage par renforcement 

## Jeu : 
Deux (ou plus) s'affrontent dans une arène composé de murs. Les tanks peuvent tirer des missiles pour abbattre leur ennemi.

### Mécaniques : 
Mouvements : 
- Tourner dans le sens des aiguilles d'une montre, D_KEY
- Tourner dans le sens inverse des aiguilles d'une montre, Q_KEY
- Avancer : Z_KEY
- Reculer : S_KEY

Il n'est possible de faire qu'une action à la fois

## Entrainement : 
Deux agents jouent sur une carte aléatoire (seed) et doivent s'affronter, ils ont 3 vies. 
Les agents sont récompensés ou punis en fonctions de leurs actions : 

Actions positives +: 
+ Abbattre un ennemi
+ Finir un ennemi 
+ Survivre (temps) 
+ Eviter une balle 

Actions négatives -: 
- Mourir
- Perdre la partie 
- Toucher un mur 

# Etapes de développement : 
1. développer le jeu en lui même 
    a. Créer un controlleur joueur qui modifie un environnement
    b. Créer un viewer graphique pour représenter le jeu

# Environment : 
- size : w and h 
- Takes an map object specifying every thing about the game or -1 to random
    - the map contains : 
        - walls : list of all walls 
        - player positions : list of player position

### Idées bonus 
- différents terrains : boue, eau, arbres... qui ralentissent
- mines 
- shield
- dash multidirectionnel pour éviter les balles 


Controller(env, agent) : appelle la fonction move 

TODO : 
- Controller 
- Create the env from a string 
- Texture manager : loads and hold a dictionary of textures
- Get state in gameManager
    - Agentpos 
    - agent angle %15
    - Agent detectors (3) states
    - Agent detectors (3) distances to walls
    - Agent distance to ennemy 
    - Angle to enemy 
- Get reward 
- Render at subpixel precision : Frect et RenderCopyExF

## Bugs rencontrés
Le vecteur de GameObject se redimensionne en même temps qu'il est parcouru. Or durant le redimensionnement les pointeurs sont déplacés (move) donc ils deviennent invalides. -> fix : utiliser des listes d'ajout/suppressions des objets pour les faires avant l'accès aux pointeurs