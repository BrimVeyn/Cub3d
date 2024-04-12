/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:59:17 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 13:23:39 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "minilibx/mlx.h"
#include <X11/X.h>
#include <stdio.h>

void display(char **map)
{
	for(int i = 0; map[i]; i++)
		printf("%s\n", map[i]);
}

int parse_map(int map_fd, t_data *data)
{
	get_raw_map(map_fd, data);
	if (check_order(data) == ERROR)
		display_error("Cub3d: Wrong order\n", data);
	if (get_texture_paths(data) == ERROR)
		display_error("Cub3d: Wrong texture path\n", data);
	if (get_colors(data) == ERROR)
		display_error("Cub3d: Error colors\n", data);
	if (check_onedir(data) == ERROR)
		display_error("Cub3d: Only one player is allowed" , data);
	data->map = del_blank(data->map);
	data->map = fill_blank(data->map);
	if (check_closed(data) == ERROR)
		display_error("Cube3d: Map is not closed\n", data);
	if (check_multimap(data) == ERROR)
		display_error("Cub3d: Multimap detected\n", data);
	display(data->map);
	display(data->texture_paths);
	printf("F = %zu\n", data->colors[0]);
	printf("C = %zu\n", data->colors[1]);
	return (TRUE);
}

void ray_cast(t_data *data)
{
	int x;

	x = 0;
	t_ray *ray = data->ray;
	t_line *line = data->line;
	while (x < WIDTH)
	{
		ray->camerax = 2 * x / (double) WIDTH - 1;
		ray->raydirx = data->player->dirx + data->player->planex * ray->camerax;
		ray->raydiry = data->player->diry + data->player->planey * ray->camerax;

		ray->mapx = (int) data->player->posx;
		ray->mapy = (int) data->player->posy;

		ray->deltadistx = fabs(1 / ray->raydirx);
		ray->deltadisty = fabs(1 / ray->raydiry);

		ray->hit = 0;

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

		while (ray->hit == 0)
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
			if (data->map[ray->mapx][ray->mapy] == 'O' && x == WIDTH * 0.5f)
				ray->aiming_at_door = -1;
			if (data->map[ray->mapx][ray->mapy] == '1')
				ray->hit = 1;
			else if (BONUS && data->map[ray->mapx][ray->mapy] == 'D')
				ray->hit = 2;
		}

		if (ray->side == 0)
			ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
		else if (ray->side == 1)
			ray->perpwalldist = (ray->sidedisty - ray->deltadisty);

		double	wall_x;

		if (ray->side == 1 && ray->stepy == -1)
			ray->side = 2;
		if (ray->side == 0 && ray->stepx == 1)
			ray->side = 3;
		if (ray->side == 0 || ray->side == 3)
			wall_x = data->player->posy + ray->perpwalldist * ray->raydiry;
		else
			wall_x = data->player->posx + ray->perpwalldist * ray->raydirx;
		wall_x -= floor(wall_x);


		int lineheight = (int)(HEIGHT / ray->perpwalldist);

		int drawstart = (-lineheight / 2 + HEIGHT / 2) + data->walk_animation->offset;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = (lineheight / 2 + HEIGHT / 2) + data->walk_animation->offset;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;
		int drawceilingstart = 0;
		int drawceilingend = drawstart;
		int drawfloorstart = drawend;
		int drawfloorend = HEIGHT;
		int color = data->colors[0];
		
		if (ray->side == 1)
			color = color / 2;
		
		line->y0 = drawstart;
		line->y1 = drawend;
		line->y = drawend - drawstart;
		line->x = x;
		line->tex_x = (wall_x * data->tex_size);
		line->span = data->tex_size;
		line->off = 0;
		if (x == WIDTH * 0.5f && ray->hit == 2 && ray->perpwalldist < 1)
        {
			ray->aiming_at_door = 1;
			ray->door_coord_x = ray->mapx;
			ray->door_coord_y = ray->mapy;
        }
		else if (ray->aiming_at_door != -1 && ((x == WIDTH * 0.5f && ray->hit == 1) || (x == WIDTH * 0.5f && ray->hit == 2 && ray->perpwalldist > 1)))
			ray->aiming_at_door = 0;
		if (line->y >= HEIGHT - 1)
		{
			line->y0 = ((float)data->tex_size * 0.5f) - ((ray->perpwalldist * data->tex_size) * 0.5f);
			line->y1 = ((float)data->tex_size * 0.5f) + ((ray->perpwalldist * data->tex_size) * 0.5f);
			line->span = line->y1 - line->y0;
			line->off = line->y0;
			line->y0 = drawstart;
			line->y1 = drawend;
		}
		for (int y = line->y0; y < line->y1; y++)
        {
			line->tex_y = ((((float)y - (float)line->y0) / ((float)line->y1 - (float)line->y0)) * line->span + line->off);
			int tex_color = data->textures[ray->side][line->tex_y * data->tex_size + line->tex_x];
			if (BONUS && ray->hit == 2)
				tex_color = data->textures[DOOR][line->tex_y * data->tex_size + line->tex_x];
			my_mlx_pixel_put(data, x, y, tex_color);
        }

		for (int i = drawfloorstart; i < drawfloorend; i++)
			my_mlx_pixel_put(data, x, i, data->colors[FLOOR]);
		for (int i = drawceilingstart; i < drawceilingend; i++)
			my_mlx_pixel_put(data, x, i, data->colors[CEILING]);
		x++;
	}
}

int ray_loop(void *param)
{
	t_data *data;
	
	data = (t_data *) param;
	view_changed(data);
	player_pos_changed(data);
	reset_screen(data);
	init_ray(data);
	ray_cast(data);
	if (BONUS)
    {
		display_minimap(data);
		draw_crosshair(data, 0xFFFFFF, 5);
		draw_crosshair(data, 0xFFFFFF, 4);
		gun_animation(data);
    }
	mlx_put_image_to_window(data->mlx, data->window, data->imgs->img, 0, 0);
	if (BONUS)
		mlx_put_image_to_window(data->mlx, data->window, data->minimap_img->img, 30 + data->minimap->draw_size / 2, 30 + data->minimap->draw_size / 2);
	mlx_set_font(data->mlx, data->window, "8x16");
	data->fps->fps_number = 1000.0 / (get_time() - data->fps->old_time);
	char *fps = ft_sprintf("fps: %d", (int)data->fps->fps_number);
	mlx_string_put(data->mlx, data->window, 930, 20, 0xFFFFFF, fps);
	free(fps);
	data->fps->old_time = get_time();
	
	
	return (TRUE);
}

int *xpm_to_tab( t_data *data, int *width, int *height, char *path)
{
	t_img_data tmp;
	int		*buffer;
	int x;
	int y;

	tmp.img = mlx_xpm_file_to_image(data->mlx, path, width, height);
	if (!tmp.img)
		display_error("Error, couldn't load texture.\n", data);
	tmp.addr_int = (int *)mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_lengh, &tmp.endian);
	buffer = ft_calloc(1, sizeof * buffer * *width * *height);
	if (!buffer)
		display_error("Cub3d: Error allocating buffer\n", data);
	y = 0;
	while (y < *height)
	{
		x = 0;
		while (x < *width)
		{
			buffer[y * *width + x] = tmp.addr_int[y * *width + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	run_map(t_data *data)
{
	data->imgs = ft_calloc(2, sizeof(t_img_data));
	data->ray = ft_calloc(2, sizeof(t_ray));
	data->player = ft_calloc(2, sizeof(t_player));
	data->minimap = ft_calloc(2, sizeof(t_minimap));
	data->line = ft_calloc(2, sizeof(t_line));
	data->minimap_img = ft_calloc(2, sizeof(t_img_data));
	init_data(data);
	init_minimap_circle(data);
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->imgs->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->imgs->addr = mlx_get_data_addr(data->imgs->img, &data->imgs->bpp, &data->imgs->line_lengh, &data->imgs->endian);

	init_animations(data);
	
	init_imgs(data);

	// mlx_key_hook(data->window, ft_hook, (void *)data);
	mlx_hook(data->window, 17, 0, close_window, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_handler, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, key_release_handler, data);

	mlx_mouse_hide(data->mlx, data->window);
	mlx_hook(data->window,MotionNotify,PointerMotionMask,handle_mouvement, data);
	mlx_mouse_hook(data->window, handle_mouse, data);
	// mlx_hook(data->window, MotionNotify, PointerMotionMask, handle_mouse, data);
	

	mlx_mouse_hide(data->mlx, data->window);
	mlx_loop_hook(data->mlx, &ray_loop, (void *)data);
	// mlx_string_put(data->mlx, data->window, 100, 300, 0x00FF00, "salope");
	// center_mouse_in_window(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	int		map_fd;
	t_data *data;

	data = ft_calloc(2, sizeof(t_data));
	data->fps = ft_calloc(2, sizeof(t_fps));
	data->fps->old_time = get_time();
	if (ac != 2)
		display_error("Cub3d: Usage: ./cub3d <path_to_map>\n", data);
	map_fd = check_map(av[1]);
	if (map_fd == ERROR)
		display_error("Cub3d: Wrong path or not a .cub file\n", data);
	parse_map(map_fd, data);
	run_map(data);
	free_data(data);

	return (EXIT_SUCCESS);
}
