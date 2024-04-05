/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:23:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/04 13:55:35 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_isnumws(char *str)
{
	int i;
	size_t num;
	size_t ws;

	i = 0;
	num = 0;
	ws = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == TRUE)
			num++;
		if (ft_isws(str[i]) == TRUE)
			ws++;
		i++;
	}
	if (num != 0 && (num + ws) == ft_strlen(str))
		return (TRUE);
	return (FALSE);
}


int ff_mapline(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
		if (ft_isnumws(data->map[i]) == TRUE)
			return (i);
		i++;
	}
	return (ERROR);
}

int has_letter(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strnstr(str, "NO", ft_strlen(str)) ||
			ft_strnstr(str, "SO", ft_strlen(str)) ||
			ft_strnstr(str, "WE", ft_strlen(str)) ||
			ft_strnstr(str, "EA", ft_strlen(str)) ||
			ft_strnstr(str, "F", ft_strlen(str)) ||
			ft_strnstr(str, "C", ft_strlen(str)))
				return (TRUE);
		i++;
	}
	return (ERROR);
}

int check_order(t_data *data)
{
	int i;
	int first_line;

	i = 0;
	first_line = ff_mapline(data);
	while (data->map[i])
	{
		if (has_letter(data->map[i]) == TRUE)
        {
			if (i > first_line)
				return (ERROR);
        }
		i++;
	}
	return (TRUE);
}
