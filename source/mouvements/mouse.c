/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:22:52 by nbardavi          #+#    #+#             */
/*   Updated: 2024/04/12 13:24:11 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	view_changed(t_data *data)
{
	t_player	*p;
	double		tmp_x;
	double		rotspeed;

	rotspeed = 0.0f;
	p = data->player;
	tmp_x = p->dirx;
	if (p->camera_moved_x)
		rotspeed = ROTSPEED * 1;
	if (p->camera_moved_y)
		rotspeed = ROTSPEED * -1;
	p->dirx = p->dirx * cos(rotspeed) - p->diry * sin(rotspeed);
	p->diry = tmp_x * sin(rotspeed) + p->diry * cos(rotspeed);
	tmp_x = p->planex;
	p->planex = p->planex * cos(rotspeed) - p->planey * sin(rotspeed);
	p->planey = tmp_x * sin(rotspeed) + p->planey * cos(rotspeed);
	return ;
}

int	handle_mouvement(int x, int y, t_data *data)
{
	double		rotspeed;
	t_player	*p;
	double		tmp_x;

	p = data->player;
	tmp_x = p->dirx;
	(void)y;
	if (x > 500)
		rotspeed = (ROTSPEED * (0.01 * ((float)WIDTH / 2 - x)) / 4);
	else if (x < 500)
		rotspeed = -ROTSPEED * (0.01 * (x - ((float)WIDTH / 2))) / 4;
	else
		return (0);
	p->dirx = p->dirx * cos(rotspeed) - p->diry * sin(rotspeed);
	p->diry = tmp_x * sin(rotspeed) + p->diry * cos(rotspeed);
	tmp_x = p->planex;
	p->planex = p->planex * cos(rotspeed) - p->planey * sin(rotspeed);
	p->planey = tmp_x * sin(rotspeed) + p->planey * cos(rotspeed);
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	handle_mouse(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		data->hud->animation_frame = 1;
	return (0);
}
