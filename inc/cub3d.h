/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <ebourdit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/10 14:29:22 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363
# define FORWARD_W_Z	119
# define BACK_S_S		115
# define RIGHT_D_D		100
# define LEFT_A_Q		97
# define BUFFER_SIZE	4096

typedef struct		s_sprxy
{
	double			x;
	double			y;
}					t_sprxy;

typedef struct		s_sprite
{
	int				nbspr;
	int				*order;
	double			*dist;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstartx;
	int				drawstarty;
	int				drawendy;
	int				drawendx;
	int				spritewidth;
	double			*zbuffer;
}					t_sprite;

typedef struct		s_texture
{
	int				texdir;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}					t_texture;

typedef struct		s_ray
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			camerax;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;

	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			movespeed;
	double			rotspeed;
	int				x;
	int				texture;
}					t_ray;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				minimapechelle;
	int				width;
	int				height;
	void			*img2;
	int				*addr2;
}					t_data;

typedef struct		s_recup
{
	int				rx;
	int				ry;
	int				i;
	int				f;
	int				c;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
	int				nblines;
	int				sizeline;
	char			**map;
	char			depart;
	int				dx;
	int				dy;
	int				indicateur;
	int				indicateur2;
	int				indicateur3;
	int				save;
	int				screenx;
	int				screeny;
	int				erreur;
	int				multijoueurs;
	int				lignevide;
	int				insidemap;
	int				count;
	int				count2;
	int				sum;
	int				wrongcharmap;
	t_data			texture[5];
	t_data			data;
	t_ray			ray;
	t_texture		t;
	t_sprite		s;
	t_sprxy			*sxy;
}					t_recup;

int					ft_cub(char *str, t_recup *recup);
void				ft_parsing(char *fichier, t_recup *recup);
int					ft_parsing_map(char *fichier, t_recup *recup);
void				ft_imprime_map(t_recup *recup);
int					ft_strlen2(char *str);
int					ft_charinstr(char *str, char c);
int					ft_murs_util(char *str);
int					ft_depart(char c, t_recup *recup, int i, int j);
void				ft_color_resolution(char **str, t_recup *recup);
int					ft_atoi2(const char *str, t_recup *recup);
int					ft_atoi3(const char *str, t_recup *recup);
void				ft_texture(char *str, t_recup *recup);
int					ft_path_texture(char *str, char **texture,
						t_recup *recup, int j);
void				ft_initialisation(t_recup *recup);
int					ft_murs(t_recup *recup);
int					ft_is_map(char *str, t_recup *recup);
void				ft_map(char *str, t_recup *recup);
int					ft_copy_map(char *str, t_recup *recup);
void				ft_init_sprite(t_recup *recup);
int					ft_raycasting(t_recup *recup);
int					ft_mlx(t_recup *recup);
int					ft_key_press(int keycode, t_recup *recup);
int					ft_key_release(int keycode, t_recup *recup);
int					ft_color_column(t_recup *recup);
void				ft_draw_texture(t_recup *recup, int x, int y);
void				ft_initialisation2(t_recup *recup);
void				ft_initialisation3(t_recup *recup);
void				ft_init_texture(t_recup *recup);
void				ft_init_sprite2(t_recup *recup, int i, int j, int v);
void				ft_stepsidedist(t_recup *recup);
void				ft_incrementray(t_recup *recup);
void				ft_drawstartend(t_recup *recup);
void				ft_swap(t_recup *recup);
void				ft_forward_back(t_recup *recup);
void				ft_left_right(t_recup *recup);
void				ft_rotate_right_left(t_recup *recup);
void				ft_error(t_recup *recup, char *str);
int					ft_exit(t_recup *recup);
void				ft_verify_errors(t_recup *recup);
void				ft_header(t_recup *recup, int fd);
void				ft_save(t_recup *recup);
void				ft_sprite(t_recup *recup);
int					ft_minimap(t_recup *recup);
void				my_color_cube(t_data *data, int x, int y, int color);
void				my_color_perso(t_data *data, int x, int y, int color);
void				ft_hitpoints(t_recup *recup);
void				ft_init_more(t_recup *recup);
int					get_next_line(int fd, char **line, t_recup *recup);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_subbuff(char *buff, int start, int len);
void				ft_init_dir(t_recup *recup);
void				ft_init_more3(t_recup *recup);
void				ft_rotate_left(t_recup *recup, double olddirx);
void				ft_atoi3_check(const char *str, t_recup *recup);
int					ft_lignevide(char *str);
int					ft_check_save(char *str);
int					ft_nb_virgule(const char *str);

#endif
