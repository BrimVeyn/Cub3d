/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:57:46 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 14:58:54 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_line_vars(t_line *line, t_data *data, t_ray *ray)
{
	line->lineheight = (int)(HEIGHT / ray->perpwalldist);
	line->y0 = (-line->lineheight / 2 + HEIGHT / 2) + data->walk_animation->offset;
	if (line->y0 < 0)
		line->y0 = 0;
	line->y1 = (line->lineheight / 2 + HEIGHT / 2) + data->walk_animation->offset;
	if (line->y1 >= HEIGHT)
		line->y1 = HEIGHT - 1;
	line->y = line->y1 - line->y0;
	line->x = ray->x;
	line->tex_x = (ray->wall_x * data->tex_size);
	line->span = data->tex_size;
	line->off = 0;
	if (ray->x == WIDTH * 0.5f && ray->hit == 2 && ray->perpwalldist < 1)
		ray->aiming_at_door = 1;
	else if (ray->aiming_at_door != -1 && ((ray->x == WIDTH * 0.5f && ray->hit == 1) || (ray->x == WIDTH * 0.5f && ray->hit == 2 && ray->perpwalldist > 1)))
		ray->aiming_at_door = 0;
	if (line->y >= HEIGHT - 1)
	{
		line->span = (((float)data->tex_size * 0.5f) + ((ray->perpwalldist * data->tex_size) * 0.5f)) - (((float)data->tex_size * 0.5f) - ((ray->perpwalldist * data->tex_size) * 0.5f));
		line->off = ((float)data->tex_size * 0.5f) - ((ray->perpwalldist * data->tex_size) * 0.5f);
	}
}

void init_ray_wall_x(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else if (ray->side == 1)
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
	if (ray->side == 1 && ray->stepy == -1)
		ray->side = 2;
	if (ray->side == 0 && ray->stepx == 1)
		ray->side = 3;
	if (ray->side == 0 || ray->side == 3)
		ray->wall_x = data->player->posy + ray->perpwalldist * ray->raydiry;
	else
		ray->wall_x = data->player->posx + ray->perpwalldist * ray->raydirx;
	ray->wall_x -= floor(ray->wall_x);
}

void init_ray_vars(t_ray *ray, t_data *data)
{
	ray->camerax = 2 * ray->x / (double) WIDTH - 1;
	ray->raydirx = data->player->dirx + data->player->planex * ray->camerax;
	ray->raydiry = data->player->diry + data->player->planey * ray->camerax;
	ray->mapx = (int) data->player->posx;
	ray->mapy = (int) data->player->posy;
	ray->deltadistx = fabs(1 / ray->raydirx);
	ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
}

void init_ray_dists(t_ray *ray, t_data *data)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (data->player->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - data->player->posx) * ray->deltadistx;
	}

	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (data->player->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - data->player->posy) * ray->deltadisty;
	}
}
