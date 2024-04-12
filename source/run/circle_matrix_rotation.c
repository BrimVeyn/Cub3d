/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_matrix_rotation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:31 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 14:54:54 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_border(t_minimap *m, int x, int y)
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

void	add_circle_border(t_data *data)
{
	t_minimap	*m;
	int			x;
	int			y;

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

void	circle_matrix_rotation(t_data *data, double angle)
{
	t_minimap	*m;
	double		cs[2];
	int			x[2];
	int			new[2];

	m = data->minimap;
	x[0] = -1;
	cs[1] = sin(angle);
	cs[0] = cos(angle);
	while (++x[0] < m->draw_size)
	{
		x[1] = -1;
		while (++x[1] < m->draw_size)
		{
			if (m->circle_matrix[x[0]][x[1]] != 0)
			{
				new[0] = ((x[0] - m->center_x) * cs[0]) - ((x[1] - m->center_y) * cs[1]) + m->center_x;
				new[1] = ((x[0] - m->center_x) * cs[1]) + ((x[1] - m->center_y) * cs[0]) + m->center_y;
				m->rotated_matrix[m->draw_size - x[0] - 1][m->draw_size - x[1] - 1] = m->filled_circle_matrix[new[0]][new[1]];
			}
			else
				m->rotated_matrix[m->draw_size - x[0] - 1][m->draw_size - x[1] - 1] = 0;
		}
	}
	paint_minimap(data);
}
