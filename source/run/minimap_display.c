/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:55:58 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 15:38:34 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	if (m->coord_matrix[x[0]][x[1]] == 0 && m->circle_matrix[x[0]][x[1]] == 1)
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

void fill_coord_matrix(t_minimap *m, char **map, t_player *p)
{
	while (m->y < m->draw_size)
	{
		m->curr_pos_y = (int)p->posy + ((m->y / m->minimap_scale) - (m->area
					/ 2));
		if (m->curr_pos_y > m->map_width - 2 || m->curr_pos_y < 0
			|| map[m->curr_pos_x][m->curr_pos_y] == '2')
			m->coord_matrix[m->x][m->y] = -1;
		if ((map[m->curr_pos_x][m->curr_pos_y] == 'N'
				|| map[m->curr_pos_x][m->curr_pos_y] == 'S'
				|| map[m->curr_pos_x][m->curr_pos_y] == 'W'
				|| map[m->curr_pos_x][m->curr_pos_y] == 'E')
			&& ((int)p->posx != m->curr_pos_x
				|| (int)p->posy != m->curr_pos_y))
			m->coord_matrix[m->x][m->y] = 0;
		else if ((int)p->posx == m->curr_pos_x
			&& (int)p->posy == m->curr_pos_y)
			m->coord_matrix[m->x][m->y] = 30;
		else
			m->coord_matrix[m->x][m->y] = map[m->curr_pos_x][m->curr_pos_y] - 48;
		m->y++;
	}

}

void	display_minimap(t_data *data)
{
	t_player	*p;
	t_minimap	*m;
	char		**map;

	m = data->minimap;
	map = data->map;
	m->area = data->minimap->minimap_size - 1;
	m->map_width = get_map_width(data);
	m->map_height = get_map_height(data);
	p = data->player;
	m = data->minimap;
	m->x = 0;
	while (m->x < m->draw_size)
	{
		m->y = 0;
		m->curr_pos_x = (int)p->posx + (((m->draw_size - m->x) / m->minimap_scale)
				- (m->area / 2));
		if (m->curr_pos_x < 0 || m->curr_pos_x > m->map_height - 1)
			while (m->y < m->minimap_size * m->minimap_scale)
				m->coord_matrix[m->x][m->y++] = -1;
		else
			fill_coord_matrix(m, map, p);
		m->x++;
	}
	render_minimap(data);
}
