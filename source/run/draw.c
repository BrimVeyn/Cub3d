/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:17:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/11 09:25:37 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && y < HEIGHT && y > 0 && x > 0)
	{
		dst = data->imgs->addr + (y * data->imgs->line_lengh + x * (data->imgs->bpp / 8));
		*(unsigned int *)dst = color;
	}
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
