/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <ebourdit@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/10 14:30:57 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_parsing_map(char *fichier, t_recup *recup)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(fichier, O_RDONLY);
	if (!(recup->map = malloc(sizeof(char*) * recup->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, recup);
		if (recup->insidemap == 1 && ft_lignevide(str) == 0 &&
				recup->count < recup->nblines)
			recup->lignevide = 1;
		if ((recup->insidemap = ft_is_map(str, recup)) == 1)
		{
			recup->count++;
			ft_copy_map(str, recup);
		}
		free(str);
	}
	close(fd);
	ft_init_sprite(recup);
	return (0);
}

void	ft_parsing(char *fichier, t_recup *recup)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if ((fd = open(fichier, O_DIRECTORY)) != -1)
		ft_error(recup, "Invalide : is a directory\n");
	if ((fd = open(fichier, O_RDONLY)) == -1)
		ft_error(recup, "Fichier .cub invalide\n");
	recup->erreur = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, recup);
		if (recup->erreur == 2)
			ft_error(recup, "La partie parsing detecte une erreur\n");
		ft_color_resolution(&str, recup);
		ft_texture(str, recup);
		ft_map(str, recup);
		free(str);
	}
	close(fd);
	if (recup->sizeline == 0 || recup->nblines == 0)
		ft_error(recup, "Map absente\n");
	ft_parsing_map(fichier, recup);
}

int		ft_cub(char *str, t_recup *recup)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error(recup, "Nom de la map invalide\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, recup);
	else
		ft_error(recup, "Nom de la map invalide\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_recup recup;

	recup.save = 0;
	ft_initialisation(&recup);
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			recup.save = 1;
		ft_cub(argv[1], &recup);
	}
	else
		write(1, "Error\nArguments invalides\n", 30);
}
