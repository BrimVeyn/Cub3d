/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_matrix_rotation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:31 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/11 15:56:51 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void draw_border(t_minimap *m, int x, int y)
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
				draw_border(m, x, y);
			y++;
		}
		x++;
	}
	return ;
}

void circle_matrix_rotation(t_data *data, double angle)
{
	t_minimap *m = data->minimap;
	double	sin_theta;
	double	cos_theta;
	int x;
	int y;

	x = 0;
	sin_theta = sin(angle);
	cos_theta = cos(angle);
	while (x < m->draw_size)
	{
		y = 0;
		while (y < m->draw_size)
		{
			if (m->circle_matrix[x][y] != 0)
			{
				int new_x = ((x - m->center_x) * cos_theta) - ((y - m->center_y) * sin_theta) + m->center_x;
				int new_y = ((x - m->center_x) * sin_theta) + ((y - m->center_y) * cos_theta) + m->center_y;
				m->rotated_matrix[m->draw_size - x -1][m->draw_size - y -1] = m->filled_circle_matrix[new_x][new_y]; 
			}
			else
				m->rotated_matrix[m->draw_size - x - 1][m->draw_size - y- 1] = 0;
			y++;
		}
		x++;
	}
	paint_minimap(data);
}
