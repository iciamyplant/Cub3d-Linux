### Lancement :
  ```
make && ./Cub3d map.cub
  ```

### Plan :
#### I - Qu'est ce que Cub3d ?
 - Le sujet
 - Appréhender le projet
#### II - Comment ai-je fait Cub3d ? 10 étapes
 - étape 1  : Parser le fichier .cub
 - étape 2  : Comprendre la minilibx et imprimer des carrés et des triangles
 - étape 3  : Créer la minimap pour apprendre à utiliser la Minilibx
 - étape 4  : Savoir récupérer les keys et les utiliser dans la minimap
 - étape 5  : Le raycasting sans textures dans la pratique
 - étape 6  : Ajouter les textures
 - étape 7  : Les Sprites
 - étape 8  : --save
 - étape 9 : Les derniers petits éléments
 - étape 10 : Les leaks
#### III - Les trucs utiles que j'ai appris
 - Techniques de débogage
 - VIM
 - Git
 - Rappels sur les pointeurs

# I - Qu'est ce que Cub3d ?
### Le sujet
Ce projet est inspiré du jeu Wolfenstein 3D. Mondialement connu, Wolfenstein 3D est considéré comme le premier FPS (c'est à dire un jeu de tire à la première personne) jamais développé. 

- L'objectif est de faire une vue dynamique (qui s'adapte au cours du temps selon les mouvements du joueur)
- et subjective (on voit du point de vue des yeux du personnage)
- au sein d’un labyrinthe ayant une représentation graphique 3D "réalistique", dans lequel on doit trouver son chemin. 

Ce projet permet d'explorer la technique du ray-casting. (Le lancer de rayons est une technique de rendu capable de créer une perspective tridimensionnelle à partir d'une carte bidimensionnelle).

### Appréhender le projet
J'ai commencé par regarder cette vidéo pour avoir une petite idée du principe : [video](https://www.youtube.com/watch?v=js7HW65MmNw&list=PL0H9-oZl_QOHM34HvD3DiGmwmj5X7GvTW) 

# II - Comment ai-je fait Cub3d ? 10 étapes
## étape 1  : Le parsing
### A faire :
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
### Tous les trucs tricky auxquels il faut penser à propos des arguments :
- [x] : Nombre d’arguments invalide : moins de 2 arguments ou plus de 3
- [x] : 3 arguments mais le 3ème n’est pas --save
- [x] : 2 arguments mais un fichier lol.cub.c
- [x] : Fichier .cub n’existe pas
- [x] : Le .cub est un directory

### Tous les trucs tricky auxquels il faut penser pour le parsing de tout sauf la map :
- [x] : Il manque qqe chose (R, NO, SO, S…)
- [x] : Deux fois la même chose (deux R, deux NO..)
- [x] : Résolution avec des int plus grands que int max
- [x] : Résolution avec une virgule ou un autre caractère dedans
- [x] : Résolution avec 3 chiffres, ou un seul, ou un 0
- [x] : F ou C avec un chiffre qui manque, ou un chiffre en trop
- [x] : F ou C avec une virgule en moins ou une virgule en trop 
- [x] : F ou C avec un int supérieur à int max : doit renvoyer une erreur
- [x] : F ou C avec un chiffre supérieur à 255
- [x] : Un identifiant mauvais genre (X au lieu de R, ou E au lieu de EA)

### Tous les trucs tricky auxquels il faut penser pour le parsing de la map :
- [x] : Une ligne vide dans la map : “Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s)"
- [x] : Un caractère incorrect dans la map, genre un 4
- [x] : Une map ouverte
- [x] : “Les espaces sont une partie valable de la carte, c’est à vous de les gérer correctement” : pour moi les espaces vides sont des murs
- [x] : La map est avant un autre élément 
- [x] : Il n’y a pas de map
- [x] : Pas de joueur ou plusieurs joueurs

## étape 2  : La Minilibx
### Installer la Minilibx :
 - prendre le fichier .xvf sur l’intra
 - faire tar -xvf le fichier
 - copier le libmlx.dylib au niveau des fichiers
 - gcc les .c avec libmlx.dylib
 - faire ./a.out

### Ecrire les premiers pixels : 
J'ai utilisé cette documentation au début : https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

Toutes la doc des fonctions sont ici : https://github.com/qst0/ft_libgfx

D'abord tu commence par mlx_init. Ensuite tu vas créer une fenêtre avec mlx_new_window. Enfin tu mets mlx_loop pour lancer le rendu de la fenêtre.
  ```
mlx = mlx_init();
mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
mlx_loop(mlx);
  ```
- [x] : Tu verras une fenêtre qui s'appelle Hello World

Ensuite on va écrire nos premiers pixels directement dans la fenêtre avec une fonction qu'on va crée que j'appelle my_mlx_pixel_put. C'est la fonction utilisée dans la doc42 citée plus haut. La fonction my_mlx_pixel_put est un peu cheum mais c'est juste pour imprimer les premiers pixels, on verra après le pourquoi du comment.
  ```
typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
  ```
- [x] : Tu verras des pixels dans ta fenêtre Hello World

### Utiliser les images :
Mais imprimer pixel par pixel dans la fenêtre c'est beaucoup trop long, donc on va utiliser des images.
D'abord on crée notre image :
  ```
mlx_new_image(mlx, 1920, 1080);
  ```
Comment écrire exactement les pixels dans cette image ? On va récupérer l'adresse mémoire sur laquelle mettre nos pixels avec mlx_get_data_addr. Pour comprendre comment écrire des pixels dans une image je te conseille très fortement d'aller voir : https://github.com/keuhdall/images_example/blob/master/README.md. Ensuite tu vas pouvoir mettre tes pixels dans l'image. 
- Formule pour char *addr :  X position * 4 + 4 * Line size * Y position. (Merci à grezette)
- Formule pour int *addr : Y * ligne_length / 4 + X. (Solution que j'ai choisi)
```
typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;
 
data.addr = (int *)mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
data.addr[y * recup->data.line_length / 4 + x] = color;
```

### Les événements (= quand on clique sur une touche par exemple) :
Documentation sur les hook : https://gist.github.com/KokaKiwi/4052375

--> La Minilibx dispose en fait d'une fonction nommée "mlx_hook" permettant d'ajouter une fonction de gestion d'évènement à son code. Tous les hooks de MiniLibX ne sont rien de plus qu'une fonction qui est appelée chaque fois qu'un événement est déclenché.
  ```
int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
  ```
--> ici mlx_hook appelle une fonction lorsque l'événement x_event au masque x_mask se déroule.
 - x_event : le code de l'événement qu’on veut gérer (par exemple, 02: Appuyez sur la touche)
 - x_mask : Le "masque" de l'évènement que l'on veut gérer, je vous laisse lire le manuel de X pour en savoir plus (par exemple, 1L<<0 c’est le KeyPressMask
 - param: Un paramètre divers que vous pouvez passer à la fonction qui gère l'événement.
 - funct : la fonction qu’on lance quand l'évènement se passe. Il y a différents types de fonctions (selon si c’est un mouvement de la souris, un keypress etc.) 

### La fonction mlx_loop_hook et mlx_put_image_to_window
"The syntax for the mlx_loop_hook () function is identical to mlx_hook, but the given function will be called when no event occurs."
C'est à dire que la fonction qu'on appelle dans mlx_loop_hook se lance en continu. Penser à mettre mlx_put_image_to_window dans la fonction que vous mettez dans loop_hook, sinon l'image ne s'imprime pas.
  ```
int mlx_loop_hook ( void *mlx_ptr, int (*funct_ptr)(), void *param );
int mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y );
  ```

## étape 3  : La Minimap
### A faire :
- Utiliser le parsing que j’ai fait dans mon char** map pour créer une minimap avec les 0, les 1 et les 2 chacun d'une couleur
- Faire un pixel = 10 pixels pour qu’on voit correctement la minimap
- Pouvoir faire bouger mon personnage avec les flèches dans la minimap (voir les keys à l'étape 4)
- Checker si le case sur laquelle je vais me déplacer est un mur ou pas (si == ‘0’) : si oui je peux me déplacer dessus, sinon non

### Comment faire ça avec les fonctions vues précédemment ? :
- Il faut mlx_init, mlx_new_window, et mlx_loop bien sur
- Il faut mlx_hook qui tourne pour les key_press et les key_release qui permet de récupérer si une touche est appuyée ou non (voir étape 4)
- Il faut mlx_get_data_addr pour récupérer l'adresse de l'image et écrire des pixels dedans
- Il faut mlx_loop_hook avec à l'intérieur ta fonction qui imprime la minimap pour que dès qu'il y a une key press la minimap s'adapte
- Il faut mlx_put_image_to_window

## étape 4  : Les keys 
### A faire :
- Appuyer sur escape et que ca quitte proprement (pour que ca quitte proprement utiliser exit(0))
- Appuyer sur flèche de gauche : rotation gauche
- Appuyer sur flèche de droite : rotation droite
- Appuyer sur W : avance
- Appuyer sur S : recule
- Appuyer sur A : déplace à gauche
- Appuyer sur D : déplace à droite

### A utiliser :
Tous les evenements ou masques sont dispo ici : https://harm-smits.github.io/42docs/libs/minilibx/events.html
  ```
int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
  ```
### Keycodes :
Linux qwerty :
- define ROTATE_LEFT	65361
- define ROTATE_RIGHT	65363
- define FORWARD_W_Z	119
- define BACK_S_S		115
- define RIGHT_D_D		100
- define LEFT_A_Q		97

Linux azerty :
- define ROTATE_LEFT	65361
- define ROTATE_RIGHT	65363
- define FORWARD_W_Z	122
- define BACK_S_S		115
- define RIGHT_D_D		100
- define LEFT_A_Q		113

Mac qwerty :
- define ROTATE_LEFT		123
- define ROTATE_RIGHT		124
- define FORWARD_W_Z		13
- define BACK_S_S			1
- define RIGHT_D_D			2
- define LEFT_A_Q			0

## étape 5  : Le raycasting
### La théorie :
Je ne sais pas si c'est la meilleure technique mais j'ai commencé par suivre des tutos en javascript//tuto plus dispo . Ca prend du temps, mais ça s'est avéré utile par la suite. Ces tutos font des rappels de maths et expliquent de façon claire ce qu'on va faire. 

le principe de base est le suivant :
- j’envoie des rayon de gauche à droite depuis la position du joueur. Sachant que au lieu de lancer un rayon pour chaque pixel nous allons lancer un rayon par colonne. On lance autant de rayons que rx (résolution x).
- plus le rayon met du temps à atteindre le mur, plus il est loin. Les tutos sont très bien pour comprendre comment on vérifie que le rayon a atteint un mur, et donc comment on calcule la distance du joueur au mur pour chaque rayon.
- plus la distance au mur est grande plus la colonne de pixels est petite.

### La pratique :
Je suis ensuite passée sur la doc de Lodev : https://lodev.org/cgtutor/raycasting.html. Après les tutos en javascript et les tentatives de faire le raycasting seule j'ai pu bien comprendre la doc de Lodev. Avant de commencer Lodev, je te conseille de regarder cette vidéo sur les vecteurs : https://www.youtube.com/watch?v=gID_FKfncZI.

##### 1. Rôle des variables utilisées par Lodev :
```
typedef struct	s_ray
{
	double		posx; //position x du joueur
	double		posy; //position y du joueur
	double		dirx; //vecteur de direction (commence à -1 pour N, 1 pour S, 0 sinon)
	double		diry; //vecteur de direction (commence à -1 pour W, 1 pour E, 0 sinon)
	double		planx; //vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
	double		plany; //vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
	double		raydirx; //calcul de direction x du rayon
	double		raydiry; //calcul de direction y du rayon
	double		camerax; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
	int		mapx; // coordonée x du carré dans lequel est pos
	int		mapy; // coordonnée y du carré dans lequel est pos
	double		sidedistx; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
	double		sidedisty; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
	double		deltadistx; //distance que rayon parcours entre chaque point d'intersection vertical
	double		deltadisty; //distance que le rayon parcours entre chaque point d'intersection horizontal
	int		stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int		stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int		hit; // 1 si un mur a ete touche, 0 sinon
	int		side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	double		perpwalldist; // distance du joueur au mur
	int		lineheight; //hauteur de la ligne a dessiner
	int		drawstart; //position de debut ou il faut dessiner
	int		drawend; //position de fin ou il faut dessiner
	int		x; //permet de parcourir tous les rayons
}					t_ray;
```
##### 2. Calculs
Pour chaque rayon ray.x on va :
- Calculer stepx, stepy, sidedistx et sidedisty
- Incrémenter tant qu'on a pas touche un mur : on passe au carre suivant soit dans la direction x soit direction y
Ici il faut savoir que l'on va d'abord jusqu'au premier point d'intersection en parcourant une distance sidedistx et sidedisty. Puis on incrémente toujours de la même valeur : deltadistx et deltadisty
- On calcule perpwalldist pour avoir lineheight, puis drawstart et drawend

abs = valeur absolue d’un nombre cad sans prendre en compte son signe.
sqrt = racine d’un nombre, racine de 9 = 3, car 3 au carré est égal à 9.

##### 3. Imprimer la colonne de pixels

##### 4. Adapter posx et posy aux mouvements droite gauche, avancer reculer
- ft_forward_back(recup);
- ft_left_right(recup);

##### 5. Adapter dirx, diry et planx, plany aux rotations droite et gauche
- ft_rotate_right_left(recup);

##### 6. Si ca lagge, swapper entre deux images
C'est à dire swapper data.img et data.img2, data.addr et data.addr2

## étape 6  : Les textures
### Principe :
L'idée est ici de récuperer la texture dans une image texture[0].img. Puis de récupérer la couleur d'un pixel à (texx;texy) dans cette image afin de mettre la même couleur dans notre image de base data.img. 

Les textures doivent être au format xpm. Celles-ci seront récupérées grâce à la fonction mlx_xpm_file_to_image. 
Penser à protéger sa fonction si le xpm est mauvais !
```
if (!(recup->texture[0].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
	recup->no, &(recup->texture[0].width), &(recup->texture[0].height))))
	ft_error(recup, "Texture SO\n");
```
L'objectif est de récupérer la couleur du pixel à (texx;texy) de la texture pour imprimer la même couleur dans notre image à (x;y). Il faudra récupérer l'adresse de cette image dans le pointeur texture[0].addr avec mlx_get_data_address, calculer texx et texy. 

```
texture[0].addr = (int *)mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].line_length, &texture[0].endian);
data.addr[y * recup->data.line_length / 4 + x] = texture[0].addr[texy * texture[0].line_length / 4 + texx];
```
### Rôle de mes variables :
```
	int		texdir; //direction NO, S, EA, WE de la texture
	double		wallx; // valeur où le mur a été touché : coordonnée y si side == 0, coordonnée x si side == 1
	int		texx; // coordonnée x de la texture
	int		texy; // coordonée y de la texture
	double		step; // indique de combien augmenter les coordonnées de la texture pour chaque pixel
	double		texpos; // coordonnée de départ
```

## étape 7  : Les Sprites
## étape 8  : --save
https://www.commentcamarche.net/contents/1200-bmp-format-bmp

  ```
 void	ft_header(t_recup *recup, int fd)
{
	int	tmp;

	write(fd, "BM", 2); //La signature (sur 2 octets), indiquant qu'il s'agit d'un fichier BMP à l'aide des deux caractères. 
			    // BM, 424D en hexadécimal, indique qu'il s'agit d'un Bitmap Windows.
	tmp = 14 + 40 + 4 * recup->rx * recup->ry; //La taille totale du fichier en octets (codée sur 4 octets)
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2); 
	write(fd, &tmp, 2); 
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &recup->rx, 4); //La largeur de l'image (sur 4 octets), c'est-à-dire le nombre de pixels horizontalement (en anglais width)
	write(fd, &recup->ry, 4); //La hauteur de l'image (sur 4 octets), c'est-à-dire le nombre de pixels verticalement (en anglais height)
	tmp = 1;
	write(fd, &tmp, 2); //Le nombre de plans (sur 2 octets). Cette valeur vaut toujours 1
	write(fd, &recup->data.bits_per_pixel, 2); //La profondeur de codage de la couleur(sur 2 octets), c'est-à-dire le nombre de bits utilisés 
			    		           //pour coder la couleur. Cette valeur peut-être égale à 1, 4, 8, 16, 24 ou 32
	tmp = 0;
	write(fd, &tmp, 4); //La méthode de compression (sur 4 octets). Cette valeur vaut 0 lorsque l'image n'est pas compressée
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}
  ```
 Attention : pour que le --save fonctionne il faut qu'il passe dans les fonctions du raycasting mais qu'il exit directement après avoir la première vue.

## étape 9  : Derniers petits éléments
- quitter le programme proprement quand j’appuie sur la croix
  ```
  mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
  ```
- si la taille de la fenêtre est supérieure à celle de l'écran, la taille de la fenêtre doit être celle de l'écran : fonction spéciale mlx_get_sreen_size sur Linux.
  ```
  mlx_get_screen_size(recup->data.mlx_ptr, &recup->screenx, &recup->screeny);
  recup->rx = (recup->rx > recup->screenx) ? recup->screenx : recup->rx;
  recup->ry = (recup->ry > recup->screeny) ? recup->screeny : recup->ry;
  ```

## étape 10  : Les leaks
### Outils :
- Les leaks : utiliser -fsanitize=leak, et valgrind
- Pour utiliser valgrind : valgrind ./executable map.cub
- Sache que le definitely lost doit etre a 0. Still reachable doit être à environ 100 blocks. Pourquoi still reachable ? Car la minilibx crée des leaks. Pour voir si le leak est chez toi ou dans la minilibx : **valgrind --leak-check=full --show-leak-kinds=all ./executable description.cub**. Le petite technique c’est de rajouter 2> leak.log pour que tous les leaks soient dans un fichier, pour plus de lisibilité **valgrind --leak-check=full --show-leak-kinds=all ./executable description.cub 2> leak.log** (Merci à alienard et ljurdant)
- Pour free quelque chose, utiliser la condition if(str) existe, donc pour cela il faut initialiser les variables que l’on free
- JAMAIS valgrind + fsanitize

### Les erreurs que j’ai pu avoir
- Free deux fois
- Free sans malloquer
- Free sans initialiser
- Ecrire des pixels en dehors de l’image

### Tout malloc doit etre free meme lorsque :
- Il y a une erreur
- Il y a le --save
- Si y a une erreur de malloc dans une ligne de la map : il faut pouvoir free les autres lignes


# III - Les trucs utiles que j'ai appris
### Techniques de débogage
- Debugger un bus error : **lldb ./executable** (attention, j’ai eu plusieurs fois bus error alors que c'était un segfault (Merci à lothieve)
- Les segfaults : utiliser **-fsanitize=address** après tes flags dans ton Makefile. Si fsanitize n’affiche rien, tu n’as pas d’erreur.

### Utils vim et terminal
- vimrc
- dd puis p pour coller
- yy puis p
- ctrl L pour clear
- trouver tous mes mallocs ou tous les endroits ou apparaissent une fonction : grep malloc src/* (merci alouis)
- commande shift g pour quand le finder s’ouvre et que tu cherches un fichier 

### Git
- git branch = liste les branches qui existent http://www.letuyau.net/2012/08/git-pusher-une-branche-sur-un-repository-distant/?fbclid=IwAR1xznNq8ni4ik_GNm316yw-S1_W-zIJ6PsBbbgLsBICtnX8ez0XZNmoz6A
- git push origin *nom branche*
- git checkout *nombranche* = basculer sur une branche déjà existante

### Rappels sur les pointeurs
Super doc sur les pointeurs : https://www.rocq.inria.fr/secret/Anne.Canteaut/COURS_C/chapitre3.html

- int *p;
- int i;
- p = &i;

--> ici si on écrit *p = 0; on change la valeur de i


|          | addr  |  valeur  |
|----------|-------|----------|
| i        | 48310 | 3        | 
| p        | 48308 | 48310    |
| p*       | 48310 | 3        |

- int *p1;
- int *p2;
- int i = 3;
- int j = 6;
- p1 = &i;
- p2 = &j;
- *p1 = *p2;


|          | addr  |  valeur  |
|----------|-------|----------|
| i        | 48310 | 6        | 
| j        | 48312 | 6        |
| p1       | 48308 | 48310    |
| p2       | 48305 | 48312    |

- int *p1;
- int *p2;
- int i = 3;
- int j = 6;
- p1 = &i;
- p2 = &j;
- p1 = p2;


|          | addr  |  valeur  |
|----------|-------|----------|
| i        | 48310 | 3        | 
| j        | 48312 | 6        |
| p1       | 48308 | 48312    |
| p2       | 48305 | 48312    |

- int *p;
- p = malloc(sizeof(int));


|          | addr  |  valeur  |
|----------|-------|----------|
| i        | 48310 | 3        | 
| p        | 48308 | 5368     |
| *p       | 53608 | ?int     |

