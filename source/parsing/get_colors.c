/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:29:34 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/23 11:39:09 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	numbers_check(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num++;
		while (ft_isdigit(str[i]))
			i++;
		if (str[i])
			i++;
	}
	return (num);
}

int	color_check(char *str)
{
	int	i;
	int	coma;

	i = 0;
	coma = 0;
	if (numbers_check(str) != 3)
		return (ERROR);
	while (str[i])
	{
		if (((str[i] < '0' || str[i] > '9') && str[i] != ',')
			&& ft_isws(str[i]) == ERROR)
			return (ERROR);
		if (str[i] == ',')
			coma++;
		i++;
	}
	if (coma != 2)
		return (ERROR);
	return (TRUE);
}

int	get_componants(t_data *data, int i, int c, int idx)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(&data->map[i][idx]);
	idx += ws_count(&data->map[i][idx]);
	idx += int_len(r);
	idx += ws_count(&data->map[i][idx]);
	idx++;
	g = ft_atoi(&data->map[i][idx]);
	idx += ws_count(&data->map[i][idx]);
	idx += int_len(g);
	idx += ws_count(&data->map[i][idx]);
	idx++;
	b = ft_atoi(&data->map[i][idx]);
	data->colors[c] = (r << 16) + (g << 8) + (b);
	if ((r > 255 || r < 0) || (g > 255 || g < 0) || (b > 255 || b < 0))
		return (ERROR);
	return (TRUE);
}

int	get_colors_loop(t_data *data, int *off, int *idx, int *x)
{
	*off = ws_count(data->map[x[0]]);
	*idx = ft_colorcmp(data->map[x[0]][*off]);
	if (*idx != ERROR)
	{
		if (color_check(&data->map[x[0]][*off + 2]) == ERROR
			|| get_componants(data, x[0], *idx, *off + 1) == ERROR)
			return (ERROR);
		data->map = ft_delindex(data->map, x[0]);
		if (!data->map)
			close_and_exit(data);
		x[1]++;
		x[0] = 0;
	}
	else
		(x[0])++;
	return (TRUE);
}

int	get_colors(t_data *data)
{
	int	x[2];
	int	off;
	int	idx;

	x[0] = 0;
	x[1] = 0;
	off = 0;
	idx = 0;
	data->colors[0] = 0;
	data->colors[1] = 0;
	while (data->map[x[0]])
	{
		if (get_colors_loop(data, &off, &idx, x) == ERROR)
			return (ERROR);
	}
	if (x[1] != 2)
		return (ERROR);
	return (TRUE);
}
