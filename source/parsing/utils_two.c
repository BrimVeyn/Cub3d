/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:46:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/04 12:36:33 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int is_ws(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < 9 || str[i] > 13) && str[i] != 32)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

int count_blank(char **map)
{
	int i;
	
	i = 0;
	while (is_ws(map[i]) == TRUE)
		i++;
	return (i);
}

int ws_count(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int get_llength(char **map)
{
	int i;
	int j;
	int count;
	
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
			j++;
		if (j > count)
			count = j;
		i++;
	}
	return (count);
}
