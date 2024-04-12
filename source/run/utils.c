/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:57:13 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 15:38:32 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_map_width(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[0][i])
		i++;
	return (i);
}

int	get_map_height(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		i++;
	return (i);
}

void	mm(t_data *data, int i, int j, int color)
{
	my_mlx_pixel_put(data, i, j, color);
}


