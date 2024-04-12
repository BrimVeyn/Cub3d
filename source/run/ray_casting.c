/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 15:00:08 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void update_door_vars(t_ray *ray, t_data *data)
{
	if (data->map[ray->mapx][ray->mapy] == 'O' && ray->x == WIDTH * 0.5f && data->map[(int) data->player->posx][(int) data->player->posy] != 'O')
	{
		if (ray->side == 0)
			ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
		else if (ray->side == 1)
			ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
		if (ray->perpwalldist < 1.0f)
			ray->aiming_at_open_door = 1;
	}
	if (BONUS && (data->map[ray->mapx][ray->mapy] == 'D' || data->map[ray->mapx][ray->mapy] == 'O'))
	{
		ray->door_coord_x = ray->mapx;
		ray->door_coord_y = ray->mapy;
	}
}

void ray_perform_dda(t_ray *ray, t_data *data)
{
	if (ray->sidedistx < ray->sidedisty)
	{
		ray->sidedistx += ray->deltadistx;
		ray->mapx += ray->stepx;
		ray->side = 0;
	}
	else
	{
		ray->sidedisty += ray->deltadisty;
		ray->mapy += ray->stepy;
		ray->side = 1;
	}
	if (BONUS)
		update_door_vars(ray, data);
	if (data->map[ray->mapx][ray->mapy] == '1')
		ray->hit = 1;
	else if (BONUS && data->map[ray->mapx][ray->mapy] == 'D')
		ray->hit = 2;
}

void draw_texture_line(t_data *data, t_ray *ray, t_line *line)
{
	int y;

	y = line->y0;
	while (y < line->y1)
	{
		line->tex_y = ((((float)y - (float)line->y0) / ((float)line->y1 - (float)line->y0)) * line->span + line->off);
		line->tex_color = data->textures[ray->side][line->tex_y * data->tex_size + line->tex_x];
		if (BONUS && ray->hit == 2)
			line->tex_color = data->textures[DOOR][line->tex_y * data->tex_size + line->tex_x];
		my_mlx_pixel_put(data, ray->x, y, line->tex_color);
		y++;
	}
}

void draw_f_and_c_line(t_data *data, t_ray *ray, t_line *line)
{
	int i;
	
	i = 0;
	while (line->y1 < HEIGHT)
		my_mlx_pixel_put(data, ray->x, line->y1++, data->colors[FLOOR]);
	while (i < line->y0)
		my_mlx_pixel_put(data, ray->x, i++, data->colors[CEILING]);
}

void ray_cast(t_data *data)
{
	t_ray *ray;
	t_line *line;

	ray = data->ray;
	line = data->line;
	ray->aiming_at_open_door = 0;
	ray->x = 0;
	while (ray->x < WIDTH)
	{
		init_ray_vars(ray, data);
		init_ray_dists(ray, data);
		while (ray->hit == 0)
			ray_perform_dda(ray, data);
		init_ray_wall_x(ray, data);
		init_line_vars(line, data, ray);
		draw_texture_line(data, ray, line);
		draw_f_and_c_line(data, ray, line);
		ray->x++;
	}
	if (ray->aiming_at_open_door || ray->aiming_at_door)
		printf("do\n"); //LARBIN
}
