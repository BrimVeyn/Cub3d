/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:46:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/03 16:05:29 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char **del_nfirst(int n, char **map)
{
	char **new_map;
	int i;
	int j;
	int old_map_len;

	i = 0;
	j = n;
	old_map_len = ft_tablen(map);
	new_map = ft_calloc(old_map_len - n + 1, sizeof(char *));
	while (i < old_map_len - n)
	{
		new_map[i] = ft_strdup(map[j]);
		i++;
		j++;
	}
	free_tab(map);
	return (new_map);
	
}

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

char **del_blank(char **map)
{
	char **new_map;
	int i;
	int j;
	int n;
	int old_map_len;

	n = count_blank(map);
	i = 0;
	j = n;
	old_map_len = ft_tablen(map);
	new_map = ft_calloc(old_map_len - n + 1, sizeof(char *));
	while (i < old_map_len - n)
	{
		new_map[i] = ft_strdup(map[j]);
		i++;
		j++;
	}
	free_tab(map);
	return (new_map);
	
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
