/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:55:58 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 15:01:45 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void mm(t_data *data, int i, int j, int color)
{
	my_mlx_pixel_put(data, i, j, color);
}

void	paint_minimap(t_data *data)
{
	t_minimap	*m;
	int			i;
	int			j;

	i = 0;
	m = data->minimap;
	while (i < m->draw_size)
	{
		j = 0;
		while (j < m->draw_size)
		{
			if (m->rotated_matrix[i][j] == 4)
				mm(data, i + OFFSET_X, j + OFFSET_Y, m->colors[0]);
			else if (m->rotated_matrix[i][j] == 8)
				mm(data, i + OFFSET_X, j + OFFSET_Y, m->colors[1]);
			else if (m->rotated_matrix[i][j] == 16)
				mm(data, i + OFFSET_X, j + OFFSET_Y, m->colors[2]);
			else if (m->rotated_matrix[i][j] == 32)
				mm(data, i + OFFSET_X, j + OFFSET_Y, m->colors[3]);
			else if (m->rotated_matrix[i][j] == 64)
				mm(data, i + OFFSET_X, j + OFFSET_Y, m->colors[4]);
			j++;
		}
		i++;
	}
}

void	render_helper(t_data *data, int x[2])
{
	t_minimap	*m;

	m = data->minimap;
	if (m->coord_matrix[x[0]][x[1]] == 0
		&& m->circle_matrix[x[0]][x[1]] == 1)
		m->filled_circle_matrix[x[0]][x[1]] = 4;
	else if (m->coord_matrix[x[0]][x[1]] == 1
		&& m->circle_matrix[x[0]][x[1]] == 1)
		m->filled_circle_matrix[x[0]][x[1]] = 8;
	else if (m->coord_matrix[x[0]][x[1]] == 30
		&& m->circle_matrix[x[0]][x[1]] == 1)
		m->filled_circle_matrix[x[0]][x[1]] = 4;
	else if (m->circle_matrix[x[0]][x[1]] == 2)
		m->filled_circle_matrix[x[0]][x[1]] = 64;
	else
		m->filled_circle_matrix[x[0]][x[1]] = 16;
}

void	render_minimap(t_data *data)
{
	t_minimap	*m;
	int			x[2];

	m = data->minimap;
	x[0] = 0;
	while (x[0] < m->draw_size)
	{
		x[1] = 0;
		while (x[1] < m->draw_size)
		{
			render_helper(data, x);
			x[1]++;
		}
		x[0]++;
	}
	m->angle = atan2(data->player->dirx, data->player->diry);
	circle_matrix_rotation(data, m->angle);
}

void	display_minimap(t_data *data)
{
	t_player	*p;
	t_minimap	*m;
	char		**map;
	int			area;
	int			i;
	int			j;
	int			curr_pos_y;
	int			curr_pos_x;
	int			map_width;
	int			map_height;

	i = 0;
	map_width = get_map_width(data);
	map_height = get_map_height(data);
	map = data->map;
	area = data->minimap->minimap_size - 1;
	p = data->player;
	m = data->minimap;
	while (i < m->draw_size)
	{
		j = 0;
		curr_pos_x = (int)p->posx + (((m->draw_size - i) / m->minimap_scale)
				- (area / 2));
		if (curr_pos_x < 0 || curr_pos_x > map_height - 1)
			while (j < m->minimap_size * m->minimap_scale)
				m->coord_matrix[i][j++] = -1;
		else
		{
			while (j < m->draw_size)
			{
				curr_pos_y = (int)p->posy + ((j / m->minimap_scale) - (area
							/ 2));
				if (curr_pos_y > map_width - 2 || curr_pos_y < 0
					|| map[curr_pos_x][curr_pos_y] == '2')
					m->coord_matrix[i][j] = -1;
				if ((map[curr_pos_x][curr_pos_y] == 'N'
						|| map[curr_pos_x][curr_pos_y] == 'S'
						|| map[curr_pos_x][curr_pos_y] == 'W'
						|| map[curr_pos_x][curr_pos_y] == 'E')
					&& ((int)p->posx != curr_pos_x
						|| (int)p->posy != curr_pos_y))
					m->coord_matrix[i][j] = 0;
				else if ((int)p->posx == curr_pos_x
					&& (int)p->posy == curr_pos_y)
					m->coord_matrix[i][j] = 30;
				else
					m->coord_matrix[i][j] = map[curr_pos_x][curr_pos_y] - 48;
				j++;
			}
		}
		i++;
	}
	render_minimap(data);
}
