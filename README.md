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
 - Rappels sur les pointeurs

# I - Qu'est ce que Cub3d ?
### Le sujet
### Le raycasting dans la théorie
J'ai commencé par regarder cette vidéo : https://www.youtube.com/watch?v=js7HW65MmNw&list=PL0H9-oZl_QOHM34HvD3DiGmwmj5X7GvTW

# II - Comment ai-je fait Cub3d ? 11 étapes
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
A chaque fois la fonction qui imprime la minimap dans :
  ```
mlx_loop_hook();
mlx_put_image_to_window
  ```

mlx_put_image_to_window : à mettre dans la fonction qui imprime la minimap qui loop !


## étape 4  : Les keys 
### A faire :
- Appuyer sur escape et que ca quitte proprement (pour que ca quitte proprement utiliser exit(0))
- Appuyer sur flèche de gauche : rotation gauche
- Appuyer sur flèche de droite : rotation droite
- Appuyer sur W : avance
- Appuyer sur S : recule
- Appuyer sur A : déplace à gauche
- Appuyer sur D : déplace à droite

### Fonction à utiliser :
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


# III - Les trucs utiles que j'ai appris

