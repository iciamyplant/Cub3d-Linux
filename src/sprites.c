/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <ebourdit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/10 14:25:45 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_dist_order2(t_recup *recup)
{
	int i;

	i = -1;
	while (++i < recup->s.nbspr)
	{
		recup->s.order[i] = i;
		recup->s.dist[i] = ((recup->ray.posx - recup->sxy[i].x) *
				(recup->ray.posx - recup->sxy[i].x) + (recup->ray.posy -
					recup->sxy[i].y) * (recup->ray.posy - recup->sxy[i].y));
	}
}

void	ft_dist_order(t_recup *recup)
{
	int		i;
	int		j;
	double	tmp;

	ft_dist_order2(recup);
	i = -1;
	while (++i < recup->s.nbspr)
	{
		j = -1;
		while (++j < recup->s.nbspr - 1)
		{
			if (recup->s.dist[j] < recup->s.dist[j + 1])
			{
				tmp = recup->s.dist[j];
				recup->s.dist[j] = recup->s.dist[j + 1];
				recup->s.dist[j + 1] = tmp;
				tmp = recup->s.order[j];
				recup->s.order[j] = recup->s.order[j + 1];
				recup->s.order[j + 1] = (int)tmp;
			}
		}
	}
}

void	ft_calculs(t_recup *recup, int i)
{
	recup->s.spritex = recup->sxy[recup->s.order[i]].x - recup->ray.posx;
	recup->s.spritey = recup->sxy[recup->s.order[i]].y - recup->ray.posy;
	recup->s.invdet = 1.0 / (recup->ray.planx * recup->ray.diry -
			recup->ray.dirx * recup->ray.plany);
	recup->s.transformx = recup->s.invdet * (recup->ray.diry *
			recup->s.spritex - recup->ray.dirx * recup->s.spritey);
	recup->s.transformy = recup->s.invdet * (-recup->ray.plany *
			recup->s.spritex + recup->ray.planx * recup->s.spritey);
	recup->s.spritescreenx = (int)((recup->rx / 2) * (1 + recup->s.transformx
				/ recup->s.transformy));
	recup->s.spriteheight = abs((int)(recup->ry / (recup->s.transformy)));
	recup->s.drawstarty = -recup->s.spriteheight / 2 + recup->ry / 2;
	if (recup->s.drawstarty < 0)
		recup->s.drawstarty = 0;
	recup->s.drawendy = recup->s.spriteheight / 2 + recup->ry / 2;
	if (recup->s.drawendy >= recup->ry)
		recup->s.drawendy = recup->ry;
	recup->s.spritewidth = abs((int)(recup->ry / (recup->s.transformy)));
	recup->s.drawstartx = -recup->s.spritewidth / 2 + recup->s.spritescreenx;
	if (recup->s.drawstartx < 0)
		recup->s.drawstartx = 0;
	recup->s.drawendx = recup->s.spritewidth / 2 + recup->s.spritescreenx;
	if (recup->s.drawendx >= recup->rx)
		recup->s.drawendx = recup->rx;
}

void	ft_draw_spr(t_recup *recup, int y, int texx, int stripe)
{
	int		d;
	int		texy;

	while (y < recup->s.drawendy)
	{
		d = (y) * 256 - recup->ry * 128 + recup->s.spriteheight * 128;
		texy = ((d * recup->texture[4].height) / recup->s.spriteheight) / 256;
		if (recup->texture[4].addr[texy * recup->texture[4].line_length / 4 +
				texx] != -16777216)
		{
			recup->data.addr[y * recup->data.line_length / 4 + stripe] =
				recup->texture[4].addr[texy * recup->texture[4].line_length /
				4 + texx];
		}
		y++;
	}
}

void	ft_sprite(t_recup *recup)
{
	int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	ft_dist_order(recup);
	while (++i < recup->s.nbspr)
	{
		ft_calculs(recup, i);
		stripe = recup->s.drawstartx;
		while (stripe < recup->s.drawendx)
		{
			texx = (int)(256 * (stripe - (-recup->s.spritewidth / 2 +
							recup->s.spritescreenx)) * recup->texture[4].width
					/ recup->s.spritewidth) / 256;
			if (recup->s.transformy > 0 && stripe >= 0 && stripe < recup->rx
					&& recup->s.transformy < recup->s.zbuffer[stripe])
			{
				y = recup->s.drawstarty;
				ft_draw_spr(recup, y, texx, stripe);
			}
			stripe++;
		}
	}
}
