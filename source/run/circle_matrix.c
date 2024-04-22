/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 10:05:02 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	compute_octants(t_minimap *m, int *x, int *y)
{
	if (m->center_x + *x < m->draw_size && m->center_y + *y < m->draw_size)
		m->circle_matrix[m->center_x + *x][m->center_y + *y] = 1;
	if (m->center_x + *y < m->draw_size && m->center_y + *x < m->draw_size)
		m->circle_matrix[m->center_x + *y][m->center_y + *x] = 1;
	if (m->center_x - *y >= 0 && m->center_y + *x < m->draw_size)
		m->circle_matrix[m->center_x - *y][m->center_y + *x] = 1;
	if (m->center_x - *x >= 0 && m->center_y + *y < m->draw_size)
		m->circle_matrix[m->center_x - *x][m->center_y + *y] = 1;
	if (m->center_x - *x >= 0 && m->center_y - *y >= 0)
		m->circle_matrix[m->center_x - *x][m->center_y - *y] = 1;
	if (m->center_x - *y >= 0 && m->center_y - *x >= 0)
		m->circle_matrix[m->center_x - *y][m->center_y - *x] = 1;
	if (m->center_x + *y < m->draw_size && m->center_y - *x >= 0)
		m->circle_matrix[m->center_x + *y][m->center_y - *x] = 1;
	if (m->center_x + *x < m->draw_size && m->center_y - *y >= 0)
		m->circle_matrix[m->center_x + *x][m->center_y - *y] = 1;
}

void	init_xy(t_minimap *m, int *x, int *y)
{
	*x = (m->draw_size / 2) - 5;
	*y = 0;
}

void	draw_circle_matrix(t_minimap *m)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	err;

	init_xy(m, &x, &y);
	dx = 1;
	dy = 1;
	err = dx - (m->draw_size / 2 << 1);
	while (compute_octants(m, &x, &y), x >= y)
	{
		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{
			x--;
			dx += 2;
			err += dx - (m->draw_size / 2 << 1);
		}
	}
}

void	fill_circle_matrix(t_data *data)
{
	t_minimap	*m;
	int			x;
	int			y;

	m = data->minimap;
	x = 0;
	while (x < m->draw_size)
	{
		y = 0;
		while (y < m->draw_size)
		{
			if (m->circle_matrix[x][y] == 1 && m->circle_matrix[x][y + 1] == 0
				&& y < m->draw_size / 2)
			{
				y++;
				while (m->circle_matrix[x][y] == 0)
					m->circle_matrix[x][y++] = 1;
				break ;
			}
			y++;
		}
		x++;
	}
}
