/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:32:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/04 12:34:19 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void fill_new_map(char **new_map, char **map, int llength)
{
	int i;
	int j;
	int line_length;

	i = 0;
	while (map[i])
	{
		j = 0;
		line_length = ft_strlen(map[i]) - 1;
		while (j < llength)
		{
			if (j > line_length || (map[i][j] && map[i][j] == ' '))
				new_map[i][j] = '2';
			else
				new_map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}

char **fill_blank(char **map)
{
	int llength;
	char **new_map;
	int i;
	int len;

	i = 0;
	len = ft_tablen(map);
	llength = get_llength(map);
	new_map = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
		new_map[i++] = ft_calloc(llength + 1, sizeof(char));
	fill_new_map(new_map, map, llength);
	free_tab(map);
	return (new_map);
	
}

char	**ft_delindex(char **split, int i)
{
	char	**new;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new = ft_calloc(ft_tablen(split) + 2, sizeof(char *));
	while (split[j] && j != i)
	{
		new[k++] = ft_strdup(split[j]);
		j++;
	}
	j++;
	while (split[j])
	{
		new[k++] = ft_strdup(split[j]);
		j++;
	}
	if (!new[0])
		new[0] = ft_strdup("WRONG");
	free_tab(split);
	return (new);
}

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
