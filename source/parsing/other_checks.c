/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:35:13 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 13:37:35 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_all_direction(char **map, int i, int j)
{
	if ((!map[i - 1][j - 1] || map[i - 1][j - 1] == '2') || (!map[i - 1][j]
			|| map[i - 1][j] == '2') || (!map[i - 1][j + 1] || map[i - 1][j
			+ 1] == '2') || (!map[i][j - 1] || map[i][j - 1] == '2')
		|| (!map[i][j + 1] || map[i][j + 1] == '2') || (!map[i + 1][j - 1]
			|| map[i + 1][j - 1] == '2') || (!map[i + 1][j] || map[i
			+ 1][j] == '2') || (!map[i + 1][j + 1] || map[i + 1][j + 1] == '2'))
		return (ERROR);
	return (TRUE);
}

int	wrong_char(char c)
{
	if (c == 'D' && BONUS == 1)
		return (TRUE);
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '1' && c != '2'
		&& c != '0')
		return (ERROR);
	return (TRUE);
}

int	check_closed(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (wrong_char(data->map[i][j]) == ERROR)
				return (ERROR);
			if (data->map[i][j] == '0' || ft_isdir(data->map[i][j]) == TRUE)
				if (check_all_direction(data->map, i, j) == ERROR)
					return (ERROR);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_onedir(t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (ft_isdir(data->map[i][j]) == TRUE)
				count++;
			if (data->map[i][j] != '0' && data->map[i][j] != '1'
				&& data->map[i][j] != 'N' && data->map[i][j] != 'S'
				&& data->map[i][j] != 'E' && data->map[i][j] != 'W'
				&& data->map[i][j] != ' ' && data->map[i][j] != 'D')
				return (ERROR);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ERROR);
	return (TRUE);
}

int	check_multimap(t_data *data)
{
	int	i;
	int	j;
	int	len;
	int	two_count;

	i = 0;
	len = ft_strlen(data->map[i]);
	while (data->map[i])
	{
		two_count = 0;
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '2')
				two_count++;
			j++;
		}
		if (two_count == len)
			return (ERROR);
		i++;
	}
	return (TRUE);
}
