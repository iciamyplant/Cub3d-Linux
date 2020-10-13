/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <ebourdit@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:49:24 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/10 14:14:32 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ft_copy(char **line, char **buff)
{
	int		start;
	char	*temp;
	char	*line_temp;

	if ((start = ft_check(*buff)) >= 0)
	{
		temp = ft_substr(*buff, 0, start);
		line_temp = *line;
		*line = ft_strjoin(*line, temp);
		free(temp);
		free(line_temp);
		*buff = ft_subbuff(*buff, start + 1, (ft_strlen(*buff) - start));
		return (0);
	}
	else
	{
		temp = NULL;
		if (*line)
			temp = *line;
		*line = ft_strjoin(*line, *buff);
		if (temp)
			free(temp);
		return (1);
	}
	return (-1);
}

int		ft_eof(int ret, char **buff, char **line)
{
	if (ret == -1)
		return (-1);
	free(*buff);
	*buff = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}

int		ft_free_buff(char **buff, t_recup *recup)
{
	if (recup->erreur == 2 && *buff)
	{
		free(*buff);
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line, t_recup *recup)
{
	static char	*buff = NULL;
	int			ret;

	if (ft_free_buff(&buff, recup) == 1)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	ret = 1;
	if (buff)
		ret = ft_copy(line, &buff);
	if (ret == 0)
		return (1);
	if (!buff)
		if (!(buff = malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!ft_copy(line, &buff))
			return (1);
	}
	if (ret <= 0)
		return (ft_eof(ret, &buff, line));
	return (1);
}
