/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:19:27 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 13:28:38 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_helper(t_data *data)
{
	t_minimap	*m;

	m = data->minimap;
	m->minimap_scale = MINIMAP_SCALE;
	m->minimap_size = MINIMAP_SIZE;
	m->draw_size = MINIMAP_SCALE * MINIMAP_SIZE;
	m->center_x = m->draw_size / 2;
	m->center_y = m->draw_size / 2;
	m->circle_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1,
			sizeof(int *));
	m->coord_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1,
			sizeof(int *));
	m->rotated_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1,
			sizeof(int *));
	m->filled_circle_matrix = ft_calloc(m->minimap_size * m->minimap_scale + 1,
			sizeof(int *));
	m->colors = init_minimap_colors(data);
	if (!m->circle_matrix || !m->coord_matrix || !m->rotated_matrix
		|| !m->filled_circle_matrix || !m->colors)
		close_and_exit(data);
}

void	init_minimap_circle(t_data *data)
{
	t_minimap	*m;
	int			idx;

	m = data->minimap;
	init_helper(data);
	idx = 0;
	while (idx < m->minimap_scale * m->minimap_size)
	{
		m->circle_matrix[idx] = ft_calloc(m->minimap_scale * m->minimap_size
				+ 1, sizeof(int));
		m->rotated_matrix[idx] = ft_calloc(m->minimap_scale * m->minimap_size
				+ 1, sizeof(int));
		m->filled_circle_matrix[idx] = ft_calloc(m->minimap_scale
				* m->minimap_size + 1, sizeof(int));
		m->coord_matrix[idx] = ft_calloc(m->minimap_scale * m->minimap_size + 1,
				sizeof(int));
		if (!m->circle_matrix[idx] || !m->rotated_matrix[idx]
			|| !m->filled_circle_matrix[idx] || !m->coord_matrix[idx])
			close_and_exit(data);
		idx++;
	}
	draw_circle_matrix(data->minimap);
	fill_circle_matrix(data);
	add_circle_border(data);
}
