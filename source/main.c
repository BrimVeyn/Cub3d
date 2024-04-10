/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:57:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/10 12:57:04 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "minilibx/mlx.h"
#include <X11/X.h>

void draw_crosshair(t_data *data, int color, int r);
void animation(t_animation *walk);

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


void fill_player_position(t_data *data)
{
	int i;
	int j;

	i = 0;
	display(data->map);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
			|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->player->posx = i;
				data->player->posy = j;
				return ;
			}
			j++;
		}
		i++;
	}
}


void init_ray(t_data *data)
{
	data->ray->camerax = 0;
	data->ray->raydirx = 0;
	data->ray->raydiry = 0;
	data->ray->deltadistx = 0;
	data->ray->deltadisty = 0;
	data->ray->sidedistx = 0;
	data->ray->sidedisty = 0;
	data->ray->perpwalldist = 0;
	data->ray->mapy = 0;
	data->ray->mapx = 0;
	data->ray->stepx = 0;
	data->ray->stepy = 0;
	return ;
}



void init_data(t_data *data)
{
	fill_player_position(data);
	if (data->map[(int)data->player->posx][(int)data->player->posy] == 'N')
    {
		data->player->dirx = 0;
		data->player->diry = 1;
		data->player->planex = 0.66;
		data->player->planey = 0;
    }
	else if (data->map[(int)data->player->posx][(int)data->player->posy] == 'S')
    {
		data->player->dirx = 0;
		data->player->diry = -1;
		data->player->planex = 0;
		data->player->planey = -0.66;
    }
	else if (data->map[(int)data->player->posx][(int)data->player->posy] == 'E')
    {
		data->player->dirx = 1;
		data->player->diry = 0;
		data->player->planex = 0;
		data->player->planey = 0.66;
    }
	else if (data->map[(int)data->player->posx][(int)data->player->posy] == 'W')
    {
		data->player->dirx = -1;
		data->player->diry = 0;
		data->player->planex = -0.66;
		data->player->planey = 0;
    }
}


void ray_cast(t_data *data)
{
	int x;
	int hit;
	
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

		hit = 0;

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

		while (hit == 0)
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
			if (data->map[ray->mapx][ray->mapy] == '1')
            {
				// printf("rayx = %d, rayy = %d\n", ray->mapx, ray->mapy);
				hit = 1;
            }
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

		// if (ray->side == EAST || ray->side == WEST)
		// 	wall_x = data->player->posy + ray->perpwalldist * ray->raydiry;
		// else
		// 	wall_x = data->player->posx + ray->perpwalldist * ray->raydirx;
		//
		if (ray->side == 0 || ray->side == 3)
			wall_x = data->player->posy + ray->perpwalldist * ray->raydiry;
		else
			wall_x = data->player->posx + ray->perpwalldist * ray->raydirx;
		wall_x -= floor(wall_x);


		// printf("wall_x = %f\n", wall_x);
		(void) line;



		

		int lineheight = (int)(HEIGHT / ray->perpwalldist);

		int drawstart = (-lineheight / 2 + HEIGHT / 2) + data->walk_animation.offset;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = (lineheight / 2 + HEIGHT / 2) + data->walk_animation.offset;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;
		int drawceilingstart = 0;
		int drawceilingend = drawstart;
		int drawfloorstart = drawend;
		int drawfloorend = HEIGHT;

		int color = data->colors[0];
		int floorcolor = 0xFAF3DD;
		int ceilingcolor = 0xAED9E0;
		
		if (ray->side == 1)
			color = color / 2;
		
		// for (int i = drawstart; i < drawend; i++)
		// 	my_mlx_pixel_put(data, x, i, color);

		line->y0 = drawstart;
		line->y1 = drawend;
		line->y = drawend - drawstart;
		line->x = x;
		line->tex_x = (wall_x * data->tex_size);
			
		for (int y = line->y0; y < line->y1; y++)
        {
			line->tex_y = ((((float)y - (float)line->y0) / ((float)line->y1 - (float)line->y0)) * data->tex_size);
			int tex_color = data->textures[ray->side][line->tex_y * data->tex_size + line->tex_x];
			my_mlx_pixel_put(data, x, y, tex_color);
        }

		for (int i = drawfloorstart; i < drawfloorend; i++)
			my_mlx_pixel_put(data, x, i, floorcolor);
		for (int i = drawceilingstart; i < drawceilingend; i++)
			my_mlx_pixel_put(data, x, i, ceilingcolor);
		x++;
	}
}

void view_changed(t_data *data)
{
	t_player *p;
	double tmp_x;
	double rotspeed;
	
	p = data->player;
	tmp_x = p->dirx;
	// printf("OLD dirx = %f\n", p->dirx);
	// printf("OLD diry = %f\n", p->diry);
	if (p->camera_moved_x)
	{
		rotspeed = ROTSPEED * 1;
		// p->camera_moved_x = 0;
	}
	if (p->camera_moved_y)
	{
		rotspeed = ROTSPEED * -1;
		// p->camera_moved_y = 0;
	}
	p->dirx = p->dirx * cos(rotspeed) - p->diry * sin(rotspeed);
	p->diry = tmp_x * sin(rotspeed) + p->diry * cos(rotspeed);
	tmp_x = p->planex;
	p->planex = p->planex * cos(rotspeed) - p->planey * sin(rotspeed);
	p->planey = tmp_x * sin(rotspeed) + p->planey * cos(rotspeed);
	
	return ;
}


void player_pos_changed(t_data *data)
{
	t_player *p;

	p = data->player;
	if (p->has_moved_y == 1)
	{
		animation(&data->walk_animation);
		p->posx = p->posx + p->dirx * MOVESPEED;
		p->posy = p->posy + p->diry * MOVESPEED;
	}
	if (p->has_moved_y == -1)
	{
		animation(&data->walk_animation);
		p->posx = p->posx - p->dirx * MOVESPEED;
		p->posy = p->posy - p->diry * MOVESPEED;

	}
	if (p->has_moved_x == 1)
	{
		animation(&data->walk_animation);
		p->posx = p->posx + p->diry * MOVESPEED;
		p->posy = p->posy - p->dirx * MOVESPEED;
	}
	if (p->has_moved_x == -1)
	{
		animation(&data->walk_animation);
		p->posx = p->posx - p->diry * MOVESPEED;
		p->posy = p->posy + p->dirx * MOVESPEED;
	}
	return ;
}


void reset_screen(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			my_mlx_pixel_put(data, i, j, 0x000000);
			j++;
		}
		i++;
	}
}


int get_map_width(t_data *data)
{
	int  i;

	i = 0;
	while (data->map[0][i])
		i++;
	return (i);
}

int get_map_height(t_data *data)
{
	int i;

	i = 0;
	while(data->map[i])
		i++;
	return (i);
}


void	paint_minimap(t_data *data)
{
	t_minimap *m;
	int offset_x;
	int offset_y;
	int minimap_colors[5] = {0x221712, 0x930000, 0x6d00fe, 0x19d043, 0xFFFFFF};
	////////////////////////  4			8			16			32		64
	///////////////////////   0			1			-1			30		c2
	int i;
	int j;

	offset_x = 40;
	offset_y = 40;
	m = data->minimap;
	i = 0;
	while (i < m->draw_size)
	{
		j = 0;
		while (j < m->draw_size)
		{
			if (m->rotated_matrix[i][j] == 4)
				my_mlx_pixel_put(data, i + offset_x, j + offset_y, minimap_colors[0]);
			else if (m->rotated_matrix[i][j] == 8)
				my_mlx_pixel_put(data, i + offset_x, j + offset_y, minimap_colors[1]);
			else if (m->rotated_matrix[i][j] == 16)
				my_mlx_pixel_put(data, i + offset_x, j + offset_y, minimap_colors[2]);
			else if (m->rotated_matrix[i][j] == 32)
				my_mlx_pixel_put(data, i + offset_x, j + offset_y, minimap_colors[3]);
			else if (m->rotated_matrix[i][j] == 64)
				my_mlx_pixel_put(data, i + offset_x, j + offset_y, minimap_colors[4]);
			j++;
		}
		i++;
	}
}




void circle_matrix_rotation(t_data *data, double angle)
{
	t_minimap *m = data->minimap;
	double sin_theta = sin(angle);
	double cos_theta = cos(angle);
	int x = 0;
	int y;

	while (x < m->draw_size)
	{
		y = 0;
		while (y < m->draw_size)
		{
			if (m->circle_matrix[x][y] != 0)
			{
				int new_x = ((x - m->center_x) * cos_theta) - ((y - m->center_y) * sin_theta) + m->center_x;
				int new_y = ((x - m->center_x) * sin_theta) + ((y - m->center_y) * cos_theta) + m->center_y;
				// printf("x = %d, y = %d\n", new_x, new_y);
				m->rotated_matrix[new_x][new_y] = m->filled_circle_matrix[x][y]; 
			}
			else
				m->rotated_matrix[x][y] = 0;
			y++;
		}
		x++;
	}
	// for(int i = 0; i < m->draw_size; i++)
	// {
	// 	for(int k = 0; k < m->draw_size; k++)
	// 		printf("[%d]", m->rotated_matrix[i][k]);
	// 	printf("\n");
	// }
	paint_minimap(data);
	// exit(0);

}


void render_minimap(t_data *data)
{
	t_minimap *minimap = data->minimap;
	int offset_x;
	int offset_y;
	// int minimap_colors[5] = {0x221712, 0x930000, 0x6d00fe, 0x19d043, 0xFFFFFF};
	////////////////////////  4			8			16			32		64
	///////////////////////   0			1			-1			30		c2
	int i;
	int j;

	offset_x = 40;
	offset_y = 40;
	i = 0;
	while (i < minimap->draw_size)
	{
		j = 0;
		while (j < minimap->draw_size)
		{
			if (minimap->coord_matrix[i][j] == 0 && minimap->circle_matrix[i][j] == 1)
            {
				// minimap->circle_matrix[i][j] = 4; 
				minimap->filled_circle_matrix[i][j] = 4;
            }
			else if (minimap->coord_matrix[i][j] == 1 && minimap->circle_matrix[i][j] == 1)
            {
				// minimap->circle_matrix[i][j] = 8;
				minimap->filled_circle_matrix[i][j] = 8;
            }
			else if (minimap->coord_matrix[i][j] == -1 && minimap->circle_matrix[i][j] == 1)
            {
				// minimap->circle_matrix[i][j] = 16;
				minimap->filled_circle_matrix[i][j] = 16;
            }
			else if (minimap->coord_matrix[i][j] == 30 && minimap->circle_matrix[i][j] == 1)
            {
				// minimap->circle_matrix[i][j] = 32;
				minimap->filled_circle_matrix[i][j] = 32;
            }
			else if (minimap->circle_matrix[i][j] == 2)
				minimap->filled_circle_matrix[i][j] = 64;
			else
				minimap->filled_circle_matrix[i][j] = 16;
			j++;
		}
		i++;
	}
	double angle = -atan2(data->player->dirx, data->player->diry) + M_PI;
	// for(int i = 0; i < minimap->draw_size; i++)
	// {
	// 	for(int k = 0; k < minimap->draw_size; k++)
	// 		printf("[%d]", minimap->coord_matrix[i][k]);
	// 	printf("\n");
	// }
	// printf("\n\n\n\n\n\n\n");
	circle_matrix_rotation(data, angle);
	return ;
}

void display_minimap(t_data *data)
{
	t_player *p;
	t_minimap *m;

	char **map = data->map;
	int area = data->minimap->minimap_size - 1;

	p = data->player;
	m = data->minimap;

	int i = 0;
	int j;
	int curr_pos_y;
	int curr_pos_x;
	int map_width = get_map_width(data);
	int map_height = get_map_height(data);

	while (i < m->draw_size)
	{
		j = 0;
		curr_pos_x = (int) p->posx + (((m->draw_size - i) / m->minimap_scale) - (area / 2));
		if (curr_pos_x < 0 || curr_pos_x > map_height - 1)
		{
			while (j < m->minimap_size * m->minimap_scale)
				m->coord_matrix[i][j++] = -1;
		}
		else
		{
			while (j < m->draw_size)
			{
				curr_pos_y = (int) p->posy + ((j / m->minimap_scale) - (area / 2));
				if (curr_pos_y > map_width - 2 || curr_pos_y < 0 || map[curr_pos_x][curr_pos_y] == '2')
					m->coord_matrix[i][j] = -1;
				if ((map[curr_pos_x][curr_pos_y] == 'N' || map[curr_pos_x][curr_pos_y] == 'S' || map[curr_pos_x][curr_pos_y] == 'W' || map[curr_pos_x][curr_pos_y] == 'E') && ((int) p->posx != curr_pos_x || (int) p->posy != curr_pos_y))
					m->coord_matrix[i][j] = 0;
				else if ((int) p->posx == curr_pos_x && (int) p->posy == curr_pos_y)
					m->coord_matrix[i][j] = 30;
				else
					m->coord_matrix[i][j] = map[curr_pos_x][curr_pos_y] - 48;
				j++;
			}
		}
		i++;
	}

	// for(int i = 0; i < m->draw_size; i++)
	// {
	// 	for(int k = 0; k < m->draw_size; k++)
	// 		printf("[%d]", m->coord_matrix[i][k]);
	// 	printf("\n");
	// }
	render_minimap(data);
}

#include <sys/time.h>

int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf(" Error getting time ");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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
	// if (BONUS == 1)
	display_minimap(data);
	draw_crosshair(data, 0xFFFFFF, 5);
	draw_crosshair(data, 0xFFFFFF, 4);
	mlx_put_image_to_window(data->mlx, data->window, data->imgs->img, 0, 0);
	mlx_set_font(data->mlx, data->window, "8x16");
	mlx_string_put(data->mlx, data->window, 930, 20, 0xFFFFFF, ft_sprintf("fps: %d", (1000 / (get_time() - data->old_time))));
	data->old_time = get_time();
	return (TRUE);
}

int *xpm_to_tab(t_data *data, int idx)
{
	t_img_data tmp;
	int		*buffer;
	int x;
	int y;

	tmp.img = mlx_xpm_file_to_image(data->mlx, data->texture_paths[idx], &data->tex_size, &data->tex_size);
	if (!tmp.img)
		display_error("Error, couldn't load texture.\n", data);
	tmp.addr_int = (int *)mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_lengh, &tmp.endian);
	buffer = ft_calloc(1, sizeof * buffer * data->tex_size * data->tex_size);
	if (!buffer)
		display_error("Cub3d: Error allocating buffer\n", data);
	y = 0;
	while (y < data->tex_size)
	{
		x = 0;
		while (x < data->tex_size)
		{
			buffer[y * data->tex_size + x] = tmp.addr_int[y * data->tex_size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void init_imgs(t_data *data)
{
    data->textures = ft_calloc(5, sizeof(int *));
    if (!data->textures)
        display_error("Cub3d: Error allocating textures buffer\n", data);
    data->textures[NORTH] = xpm_to_tab(data, NORTH);
    data->textures[SOUTH] = xpm_to_tab(data, SOUTH);
    data->textures[EAST] = xpm_to_tab(data, EAST);
    data->textures[WEST] = xpm_to_tab(data, WEST);
}


void fill_circle_matrix(t_data *data)
{
	t_minimap *m;
	int			x;
	int			y;

	m = data->minimap;
	x = 0;
	while (x < m->draw_size)
	{
		y = 0;
		while (y < m->draw_size)
		{
			if (m->circle_matrix[x][y] == 1 && m->circle_matrix[x][y + 1] == 0 && y < m->draw_size / 2)
			{
				y++;
				while (m->circle_matrix[x][y] == 0)
				{
					m->circle_matrix[x][y] = 1;
					y++;
				}
				break;
			}
			y++;
		}
		x++;
	}
}

void add_circle_border(t_data *data)
{
	t_minimap *m;
	int x;
	int y;

	m = data->minimap;
	x = 0;
	while (x < m->draw_size)
	{
		y = 0;
		while (y < m->draw_size - 1)
		{
			if (m->circle_matrix[x][y] == 1)
			{
				if (x - 1 > 0 && m->circle_matrix[x - 1][y] == 0)
					m->circle_matrix[x - 1][y] = 2;
				if (x - 2 > 0 && m->circle_matrix[x - 2][y] == 0)
					m->circle_matrix[x - 2][y] = 2;
				if (y - 1 > 0 && m->circle_matrix[x][y - 1] == 0)
					m->circle_matrix[x][y - 1] = 2;
				if (y - 2 > 0 && m->circle_matrix[x][y - 2] == 0)
					m->circle_matrix[x][y - 2] = 2;
				if (y + 1 < m->draw_size - 1 && m->circle_matrix[x][y + 1] == 0)
					m->circle_matrix[x][y + 1] = 2;
				if (y + 1 < m->draw_size - 1 && m->circle_matrix[x][y + 2] == 0)
					m->circle_matrix[x][y + 2] = 2;
				if (x + 1 > m->draw_size / 2 && m->circle_matrix[x + 1][y] == 0)
					m->circle_matrix[x + 1][y] = 2;
				if (x + 2 > m->draw_size / 2 && m->circle_matrix[x + 2][y] == 0)
					m->circle_matrix[x + 2][y] = 2;
			}
			y++;
		}
		x++;
	}
	return ;
}


void init_minimap_circle(t_data *data)
{
	t_minimap *m;
	int			idx;

	m = data->minimap;
	m->minimap_scale = MINIMAP_SCALE;
	m->minimap_size = MINIMAP_SIZE;
	m->draw_size = MINIMAP_SCALE * MINIMAP_SIZE;
	m->center_x = m->draw_size / 2;
	m->center_y = m->draw_size / 2;
	m->circle_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1, sizeof(int *));
	m->coord_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1, sizeof(int *));
	m->rotated_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1, sizeof(int *));
	m->filled_circle_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1, sizeof(int *));
	idx = 0;
	while (idx < m->minimap_scale * m->minimap_size)
    {
		m->circle_matrix[idx] = ft_calloc(m->minimap_scale * m->minimap_size + 1, sizeof(int));
		m->rotated_matrix[idx] = ft_calloc(m->minimap_scale * m->minimap_size + 1, sizeof(int));
		m->filled_circle_matrix[idx] = ft_calloc(m->minimap_scale * m->minimap_size + 1, sizeof(int));
		m->coord_matrix[idx++] = ft_calloc(m->minimap_scale * m->minimap_size + 1, sizeof(int));
    }
	draw_circle_matrix(data);
	fill_circle_matrix(data);
	add_circle_border(data);

}

int handle_mouse(int x, int y, t_data *data)
{
	(void)y;
	double rotspeed;
	t_player *p = data->player;
	double tmp_x = p->dirx;
	
	if (x > 500)
		rotspeed = (ROTSPEED * (0.01 * (WIDTH / 2 - x)) / 4);
	else if (x < 500)
		rotspeed = -ROTSPEED * (0.01 * (x - (WIDTH / 2))) / 4;
	else
		return (0);
	// printf("x = %d y = %d |\n", x, y);
	p->dirx = p->dirx * cos(rotspeed) - p->diry * sin(rotspeed);
	p->diry = tmp_x * sin(rotspeed) + p->diry * cos(rotspeed);
	tmp_x = p->planex;
	p->planex = p->planex * cos(rotspeed) - p->planey * sin(rotspeed);
	p->planey = tmp_x * sin(rotspeed) + p->planey * cos(rotspeed);
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	// usleep(10);
	return (0);
}

void draw_crosshair(t_data *data, int color, int r) {
    int cx = WIDTH / 2;
    int cy = HEIGHT / 2;
    double angle = 0.0;

    while (angle < 2 * PI) {
        int x = cx + (int)(r * cos(angle));
        int y = cy + (int)(r * sin(angle));
        my_mlx_pixel_put(data, x, y, color);

        angle += 0.01;
    }
}

void animation(t_animation *walk)
{
	if (walk->offset == 8)
		walk->trigger_offset = 1;
	if (walk->offset == -8)
		walk->trigger_offset = 0;
	if (walk->trigger_offset == 0)
		walk->offset += 2;
	else
		walk->offset -= 2;
	// printf("hello\n");
}

void	run_map(t_data *data)
{
	data->walk_animation.trigger_offset = 0;
	data->walk_animation.offset = 0;
	data->imgs = ft_calloc(2, sizeof(t_img_data));
	data->ray = ft_calloc(2, sizeof(t_ray));
	data->player = ft_calloc(2, sizeof(t_player));
	data->minimap = ft_calloc(2, sizeof(t_minimap));
	data->line = ft_calloc(2, sizeof(t_line));
	init_data(data);
	init_minimap_circle(data);
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->imgs->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->imgs->addr = mlx_get_data_addr(data->imgs->img, &data->imgs->bpp, &data->imgs->line_lengh, &data->imgs->endian);
	
	init_imgs(data);

	// mlx_key_hook(data->window, ft_hook, (void *)data);
	mlx_hook(data->window, 17, 0, close_window, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_handler, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, key_release_handler, data);

	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_hook(data->window, handle_mouse, data);
	mlx_hook(data->window, MotionNotify, PointerMotionMask, handle_mouse, data);
	

	mlx_loop_hook(data->mlx, &ray_loop, (void *)data);
	// mlx_string_put(data->mlx, data->window, 100, 300, 0x00FF00, "salope");
	// center_mouse_in_window(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	int		map_fd;
	t_data	data;

	ft_bzero((void *) &data, sizeof(t_data));
	data.old_time = get_time();
	if (ac != 2)
		display_error("Cub3d: Usage: ./cub3d <path_to_map>\n", &data);
	map_fd = check_map(av[1]);
	if (map_fd == ERROR)
		display_error("Cub3d: Wrong path or not a .cub file\n", &data);
	parse_map(map_fd, &data);
	run_map(&data);
	free_data(&data);

	return (EXIT_SUCCESS);
}
