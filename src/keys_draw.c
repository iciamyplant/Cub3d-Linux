/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdit <ebourdit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/10/10 14:30:36 by ebourdit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_key_press(int keycode, t_recup *recup)
{
	if (keycode == FORWARD_W_Z)
		recup->data.forward = 1;
	else if (keycode == BACK_S_S)
		recup->data.back = 1;
	else if (keycode == LEFT_A_Q)
		recup->data.left = 1;
	else if (keycode == RIGHT_D_D)
		recup->data.right = 1;
	else if (keycode == ROTATE_LEFT)
		recup->data.rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		recup->data.rotate_right = 1;
	else if (keycode == 65307)
		ft_error(recup, "Non jrigole\n");
	return (1);
}

int		ft_key_release(int keycode, t_recup *recup)
{
	if (keycode == FORWARD_W_Z)
		recup->data.forward = 0;
	else if (keycode == BACK_S_S)
		recup->data.back = 0;
	else if (keycode == LEFT_A_Q)
		recup->data.left = 0;
	else if (keycode == RIGHT_D_D)
		recup->data.right = 0;
	else if (keycode == ROTATE_LEFT)
		recup->data.rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
		recup->data.rotate_right = 0;
	return (1);
}

int		ft_color_column(t_recup *recup)
{
	int j;
	int i;

	j = -1;
	recup->ray.drawend = recup->ry - recup->ray.drawstart;
	i = recup->ray.drawend;
	while (++j < recup->ray.drawstart)
		recup->data.addr[j * recup->data.line_length / 4 +
			recup->ray.x] = recup->c;
	if (j <= recup->ray.drawend)
		ft_draw_texture(recup, recup->ray.x, j);
	j = i;
	while (++j < recup->ry)
		recup->data.addr[j * recup->data.line_length / 4 +
			recup->ray.x] = recup->f;
	return (0);
}

void	ft_draw_texture(t_recup *recup, int x, int y)
{
	y = recup->ray.drawstart - 1;
	ft_init_texture(recup);
	recup->t.step = 1.0 * recup->texture[0].height / recup->ray.lineheight;
	recup->t.texx = (int)(recup->t.wallx * (double)recup->texture
			[recup->t.texdir].width);
	if (recup->ray.side == 0 && recup->ray.raydirx > 0)
		recup->t.texx = recup->texture[recup->t.texdir].width -
			recup->t.texx - 1;
	if (recup->ray.side == 1 && recup->ray.raydiry < 0)
		recup->t.texx = recup->texture[recup->t.texdir].width -
			recup->t.texx - 1;
	recup->t.texpos = (recup->ray.drawstart - recup->ry / 2 +
			recup->ray.lineheight / 2) * recup->t.step;
	while (++y <= recup->ray.drawend)
	{
		recup->t.texy = (int)recup->t.texpos &
			(recup->texture[recup->t.texdir].height - 1);
		recup->t.texpos += recup->t.step;
		if (y < recup->ry && x < recup->rx)
			recup->data.addr[y * recup->data.line_length / 4 + x] =
				recup->texture[recup->t.texdir].addr[recup->t.texy *
					recup->texture[recup->t.texdir].line_length /
					4 + recup->t.texx];
	}
}
