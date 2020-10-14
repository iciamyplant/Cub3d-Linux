### Plan :
### I - Qu'est ce que Cub3d ?
  -  Le sujet
  -  Le raycasting dans la théorie
### II - Comment ai-je fait Cub3d ? 11 étapes
  - étape 1  :  Parser le fichier .cub
  - étape 2  :  Comprendre la minilibx et imprimer des carrés et des triangles
  - étape 3  :  Créer la minimap pour apprendre à utiliser la Minilibx
  - étape 4  :  Savoir récupérer les keys et les utiliser dans la minimap
  - étape 5  :  Le raycasting sans textures dans la pratique
  - étape 6  :  La couleur du sol et du plafond
  - étape 7  :  Ajouter les textures
  - étape 8  :  Les Sprites
  - étape 9  :  --save
  - étape 10 :  Les derniers petits éléments
  - étape 11 :  Les leaks
### III - Les trucs utiles que j'ai appris
  -  Techniques de débogage
  -  VIM
  -  Git

# I - Qu'est ce que Cub3d ? 
### Le sujet
### Le raycasting dans la théorie

# II - Comment ai-je fait Cub3d ? 11 étapes
## étape 1  : Parsing
- parser dans un tableau de char à double entrée (il est également possible de parser dans un tableau de int, mais j’ai préféré la solution des char).
- checker que la map soit entourée de murs
- a chaque fois faire passer par la fonction qui vérifie qu'il n'y a pas d'autres caractères que 0,1,2
- a chaque fois faire passer par la fonction qui vérifie si y a la position dedans si y a N,S,E,W et s’il y a la position remplacer par 0 et retenir dans une variable ou c’est et la direction
- faire un tableau de chaînes de caractères
- il faut savoir que la map doit être carré. donc ajouter des 1 avant ou après pour que toutes les lignes soit de la taille de la ligne la plus grande.
- read une première fois pour trouver la taille de la chaîne la plus longue de la map + le nombre de chaînes qu’il y a dans la map. pour le malloc de map**
- malloquer le tableau avec le nombre de char * qu’il y a dedans
- malloquer ensuite chaine de caractère par chaîne de caractères dans le tableau
- remplacer tous les espaces par des murs + ajouter des murs au bout pour que la taille de la chaîne soit suffisamment grande

Tous les trucs tricky auxquels il faut penser pour le parsing de tout sauf la map :
- il manque quelque chose (R, NO, SO, S…)
- deux fois la même chose (deux R, deux NO..)
- résolution avec des int plus grands que int max
- résolution avec une virgule ou un autre caractère dedans
- résolution avec 3 chiffres, ou un seul, ou un 0
- F ou C avec un chiffre qui manque, ou un chiffre en trop
- F ou C avec une virgule en moins ou une virgule en trop 
- F ou C avec un int supérieur à int max : doit renvoyer une erreur
- F ou C avec un chiffre supérieur à 255
- un identifiant mauvais genre (X au lieu de R, ou E au lieu de EA)

Tous les trucs tricky auxquels il faut penser pour le parsing de la map :
- une ligne vide dans la map : “Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s)”.
- un caractère incorrect dans la map, genre un 4
- une map ouverte
- “Les espaces sont une partie valable de la carte, c’est à vous de les gérer correctement” : pour moi les espaces vides sont des murs.
- la map est avant un autre élément 
- il n’y a pas de map
- pas de joueur ou plusieurs joueurs

Tous les trucs tricky auxquels il faut penser à propos des arguments :
- nombre d’arguments invalide : moins de 2 arguments ou plus de 3
- 3 arguments mais le 3ème n’est pas --save
- 2 arguments mais un fichier lol.cub.c
- fichier .cub n’existe pas
- le .cub est un directory

## étape 2  : Comprendre la minilibx et imprimer des carrés et des triangles
## étape 3  : Créer la minimap pour apprendre à utiliser la Minilibx
## étape 4  : Savoir récupérer les keys et les utiliser dans la minimap
## étape 5  : Le raycasting sans textures dans la pratique
## étape 6  : La couleur du sol et du plafond
## étape 7  : Ajouter les textures
## étape 8  : Les Sprites
## étape 9  : --save
## étape 10 : Les derniers petits éléments
## étape 11 : Les leaks

# III - Les trucs utiles que j'ai appris
### 1. Techniques de débogage
### 2. VIM
### 3. Git
