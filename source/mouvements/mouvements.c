/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:04:48 by nbardavi          #+#    #+#             */
/*   Updated: 2024/04/12 12:58:43 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_y_plus(t_data *data, double speed_ajustement)
{
	t_player	*p;

	p = data->player;
	if (p->has_moved_y == 1 && data->map[(int)(p->posx + p->dirx
			* speed_ajustement)][(int)(p->posy + p->diry
			* speed_ajustement)] != '1' && (BONUS == 0
			|| (data->map[(int)(p->posx + p->dirx
					* speed_ajustement)][(int)(p->posy + p->diry
					* speed_ajustement)]) != 'D'))
	{
		animation(data->walk_animation);
		p->posx = p->posx + p->dirx * speed_ajustement;
		p->posy = p->posy + p->diry * speed_ajustement;
	}
}

void	move_y_minus(t_data *data, double speed_ajustement)
{
	t_player	*p;

	p = data->player;
	if (p->has_moved_y == -1 && data->map[(int)(p->posx - p->dirx
			* speed_ajustement)][(int)(p->posy - p->diry
			* speed_ajustement)] != '1' && (BONUS == 0
			|| data->map[(int)(p->posx - p->dirx
				* speed_ajustement)][(int)(p->posy - p->diry
				* speed_ajustement)] != 'D'))
	{
		animation(data->walk_animation);
		p->posx = p->posx - p->dirx * speed_ajustement;
		p->posy = p->posy - p->diry * speed_ajustement;
	}
}

void	move_x_plus(t_data *data, double speed_ajustement)
{
	t_player	*p;

	p = data->player;
	if (p->has_moved_x == 1 && data->map[(int)(p->posx + p->diry
			* speed_ajustement)][(int)(p->posy - p->dirx
			* speed_ajustement)] != '1' && (BONUS == 0
			|| data->map[(int)(p->posx + p->diry
				* speed_ajustement)][(int)(p->posy - p->dirx
				* speed_ajustement)] != 'D'))
	{
		animation(data->walk_animation);
		p->posx = p->posx + p->diry * speed_ajustement;
		p->posy = p->posy - p->dirx * speed_ajustement;
	}
}

void	move_x_minus(t_data *data, double speed_ajustement)
{
	t_player	*p;

	p = data->player;
	if (p->has_moved_x == -1 && data->map[(int)(p->posx - p->diry
			* speed_ajustement)][(int)(p->posy + p->dirx
			* speed_ajustement)] != '1' && (BONUS == 0
			|| data->map[(int)(p->posx - p->diry
				* speed_ajustement)][(int)(p->posy + p->dirx
				* speed_ajustement)] != 'D'))
	{
		animation(data->walk_animation);
		p->posx = p->posx - p->diry * speed_ajustement;
		p->posy = p->posy + p->dirx * speed_ajustement;
	}
}

void	player_pos_changed(t_data *data)
{
	t_player	*p;
	double		speed_ajustement;

	p = data->player;
	if (p->has_moved_x != 0 && p->has_moved_y != 0)
	{
		speed_ajustement = (MOVESPEED * (60 / data->fps->fps_number)) / 2;
		data->walk_animation->animation_speed = 1;
	}
	else
	{
		data->walk_animation->animation_speed = 2;
		speed_ajustement = MOVESPEED * (60 / data->fps->fps_number);
	}
	move_y_plus(data, speed_ajustement);
	move_y_minus(data, speed_ajustement);
	move_x_plus(data, speed_ajustement);
	move_x_minus(data, speed_ajustement);
	return ;
}
