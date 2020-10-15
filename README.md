### Plan :
#### I - Qu'est ce que Cub3d ?
 - Le sujet
 - Le raycasting dans la théorie
#### II - Comment ai-je fait Cub3d ? 11 étapes
 - étape 1  : Parser le fichier .cub
 - étape 2  : Comprendre la minilibx et imprimer des carrés et des triangles
 - étape 3  : Créer la minimap pour apprendre à utiliser la Minilibx
 - étape 4  : Savoir récupérer les keys et les utiliser dans la minimap
 - étape 5  : Le raycasting sans textures dans la pratique
 - étape 6  : La couleur du sol et du plafond
 - étape 7  : Ajouter les textures
 - étape 8  : Les Sprites
 - étape 9  : --save
 - étape 10 : Les derniers petits éléments
 - étape 11 : Les leaks
#### III - Les trucs utiles que j'ai appris
 - Techniques de débogage
 - VIM
 - Git

# I - Qu'est ce que Cub3d ?
### Le sujet
### Le raycasting dans la théorie

# II - Comment ai-je fait Cub3d ? 11 étapes
## étape 1  : Le parsing
#### A faire :
- Parser dans un tableau de char à double entrée (il est également possible de parser dans un tableau de int, mais j’ai préféré la solution des chars).
- Checker que la map soit entourée de murs
- A chaque fois faire passer par la fonction qui vérifie que les caractères de la map sont bien des 0,1,2 
- A chaque fois faire passer par la fonction qui vérifie s'il y a bien le joueur dans la map (donc si y a N,S,E ou W) et si le joueur est là remplacer par 0 et retenir dans une variable la position et la direction du joueur
- Faire un tableau de chaînes de caractères
- J'ai ajouté des 1 avant ou après pour que toutes les lignes soit de la taille de la ligne la plus grande
- Pour le malloc de map** je read une première fois pour trouver la taille de la chaîne la plus longue de la map + le nombre de chaînes qu’il y a dans la map
- Malloquer le tableau avec le nombre de char * qu’il y a dedans
- Malloquer ensuite chaine de caractère par chaîne de caractères dans le tableau
- Remplacer tous les espaces par des murs + ajouter des murs au bout pour que la taille de la chaîne soit suffisamment grande

### Rappel du malloc d'un tableau de chaînes de caractères :
  ```
  char **liste;
  char *ptr
  liste = malloc(sizeof(char*) * nbrdechaines)
  liste[i] = malloc(sizeof(char) * ft_strlen(str))
  ```
### Tous les trucs tricky auxquels il faut penser pour le parsing de tout sauf la map :
- [x] : Il manque qqe chose (R, NO, SO, S…)
- Deux fois la même chose (deux R, deux NO..)
- Résolution avec des int plus grands que int max
résolution avec une virgule ou un autre caractère dedans
résolution avec 3 chiffres, ou un seul, ou un 0
F ou C avec un chiffre qui manque, ou un chiffre en trop
F ou C avec une virgule en moins ou une virgule en trop 
F ou C avec un int supérieur à int max : doit renvoyer une erreur
F ou C avec un chiffre supérieur à 255
un identifiant mauvais genre (X au lieu de R, ou E au lieu de EA)

tous les trucs tricky auxquels il faut penser pour le parsing de la map :
une ligne vide dans la map : “Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s)”.
un caractère incorrect dans la map, genre un 4
une map ouverte
“Les espaces sont une partie valable de la carte, c’est à vous de les gérer correctement” : pour moi les espaces vides sont des murs.
la map est avant un autre élément 
il n’y a pas de map
pas de joueur ou plusieurs joueurs

Tous les trucs tricky auxquels il faut penser à propos des arguments :
nombre d’arguments invalide : moins de 2 arguments ou plus de 3
3 arguments mais le 3ème n’est pas --save
2 arguments mais un fichier lol.cub.c
fichier .cub n’existe pas
le .cub est un directory



## étape 2  : Comprendre la minilibx et imprimer des carrés et des triangles
# III - Les trucs utiles que j'ai appris
