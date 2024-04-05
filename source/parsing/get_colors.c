/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:29:34 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/04 14:07:00 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_colorcmp(char c)
{
	if (c == 'F')
		return (C_F);
	if (c == 'C')
		return (C_C);
	return (ERROR);
}

int color_check(char *str)
{
	int i;
	int coma;

	i = 0;
	coma = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == ',' || ft_isws(str[i]) == TRUE))
			return (ERROR);
		if (str[i] == ',')
			coma++;
		i++;
	}
	if (coma != 2)
		return (ERROR);
	return (TRUE);
}

int get_componants(t_data *data, int i, int c, int idx)
{
	int r;
	int	g;
	int b;

	r = ft_atoi(&data->map[i][idx]);
	idx += int_len(r) + 1;
	g = ft_atoi(&data->map[i][idx]);
	idx += int_len(g) + 1;
	b = ft_atoi(&data->map[i][idx]);
	data->colors[c] = (r << 16) + (g << 8) + (b << 1); 
	if (r > 255 || g > 255 || b > 255)
		return (ERROR);
	return (TRUE);
}

int get_colors(t_data *data)
{
	int i;
	int count;
	int idx;
	int off;

	i = 0;
	count = 0;
	data->colors[0] = 0;
	data->colors[1] = 0;
	while (data->map[i])
	{
		off = ws_count(data->map[i]);
		idx = ft_colorcmp(data->map[i][off]);
		if (idx != ERROR)
        {
			off += ws_count(&data->map[i][off + 1]) + 1;
			if (color_check(&data->map[i][off + 2]) == ERROR || get_componants(data, i, idx, off) == ERROR)
				return (ERROR);
			data->map = ft_delindex(data->map, i);
			count++;
			i = 0;
        }
		else
			i++;
	}
	if (count != 2)
		return (ERROR);
	return (TRUE);	
}
