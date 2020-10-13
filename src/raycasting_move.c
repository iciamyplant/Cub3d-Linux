/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <ebourdit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/10 14:40:51 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_forward_back(t_recup *recup)
{
	if (recup->data.forward == 1)
	{
		if (recup->map[(int)(recup->ray.posx + (recup->ray.dirx * recup->
						ray.movespeed * 2))][(int)recup->ray.posy] == '0')
			recup->ray.posx += recup->ray.dirx * recup->ray.movespeed;
		if (recup->map[(int)(recup->ray.posx)][(int)(recup->ray.posy +
					(recup->ray.diry * recup->ray.movespeed * 2))] == '0')
			recup->ray.posy += recup->ray.diry * recup->ray.movespeed;
	}
	if (recup->data.back == 1)
	{
		if (recup->map[(int)(recup->ray.posx - (recup->ray.dirx * recup->
						ray.movespeed * 2))][(int)(recup->ray.posy)] == '0')
			recup->ray.posx -= recup->ray.dirx * recup->ray.movespeed;
		if (recup->map[(int)(recup->ray.posx)][(int)(recup->ray.posy -
					(recup->ray.diry * recup->ray.movespeed * 2))] == '0')
			recup->ray.posy -= recup->ray.diry * recup->ray.movespeed;
	}
}

void	ft_left_right(t_recup *recup)
{
	if (recup->data.right == 1)
	{
		if (recup->map[(int)(recup->ray.posx + recup->ray.diry *
					(recup->ray.movespeed * 2))][(int)recup->ray.posy] == '0')
			recup->ray.posx += recup->ray.diry * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posx][(int)(recup->ray.posy -
					recup->ray.dirx *
					(recup->ray.movespeed * 2))] == '0')
			recup->ray.posy -= recup->ray.dirx * recup->ray.movespeed;
	}
	if (recup->data.left == 1)
	{
		if (recup->map[(int)(recup->ray.posx - recup->ray.diry *
					(recup->ray.movespeed * 2))][(int)recup->ray.posy] == '0')
			recup->ray.posx -= recup->ray.diry * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posx][(int)(recup->ray.posy +
					recup->ray.dirx *
					(recup->ray.movespeed * 2))] == '0')
			recup->ray.posy += recup->ray.dirx * recup->ray.movespeed;
	}
}

void	ft_rotate_right_left(t_recup *recup)
{
	double oldplanx;
	double olddirx;

	oldplanx = recup->ray.planx;
	olddirx = recup->ray.dirx;
	if (recup->data.rotate_right == 1)
	{
		recup->ray.dirx = recup->ray.dirx * cos(-recup->ray.rotspeed / 2) -
			recup->ray.diry * sin(-recup->ray.rotspeed / 2);
		recup->ray.diry = olddirx * sin(-recup->ray.rotspeed / 2) +
			recup->ray.diry * cos(-recup->ray.rotspeed / 2);
		recup->ray.planx = recup->ray.planx * cos(-recup->ray.rotspeed / 2)
			- recup->ray.plany * sin(-recup->ray.rotspeed / 2);
		recup->ray.plany = oldplanx * sin(-recup->ray.rotspeed / 2) +
			recup->ray.plany * cos(-recup->ray.rotspeed / 2);
	}
	ft_rotate_left(recup, olddirx);
}

void	ft_rotate_left(t_recup *recup, double olddirx)
{
	double oldplanex;

	if (recup->data.rotate_left == 1)
	{
		olddirx = recup->ray.dirx;
		oldplanex = recup->ray.planx;
		recup->ray.dirx = recup->ray.dirx * cos(recup->ray.rotspeed / 2) -
			recup->ray.diry * sin(recup->ray.rotspeed / 2);
		recup->ray.diry = olddirx * sin(recup->ray.rotspeed / 2) + recup->
			ray.diry * cos(recup->ray.rotspeed / 2);
		recup->ray.planx = recup->ray.planx * cos(recup->ray.rotspeed / 2) -
			recup->ray.plany * sin(recup->ray.rotspeed / 2);
		recup->ray.plany = oldplanex * sin(recup->ray.rotspeed / 2) +
			recup->ray.plany * cos(recup->ray.rotspeed / 2);
	}
}
