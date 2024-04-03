/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:28:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/03 17:35:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void display(char **map)
{
	for(int i = 0; map[i]; i++)
		printf("%s\n", map[i]);
}




int check_perms(t_data *data)
{
	int tmp_fd;
	int i;

	i = 0;
	while (i < 4)
	{
		tmp_fd = open(data->texture_paths[i], O_RDONLY);
		if (tmp_fd == ERROR || ft_reversecmp(data->texture_paths[i], ".xpm") == ERROR)
			return (ERROR);
		close(tmp_fd);
		i++;
	}
	return (TRUE);
}

int ws_count(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int ft_directioncmp(char *str)
{
	if (!ft_strncmp(str, "NO", 2))
		return (DIR_NO);
	if (!ft_strncmp(str, "SO", 2))
		return (DIR_SO);
	if (!ft_strncmp(str, "WE", 2))
		return (DIR_WE);
	if (!ft_strncmp(str, "EA", 2))
		return (DIR_EA);
	return (ERROR);
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

int get_texture_paths(t_data *data)
{
	int i;
	int off;
	int count;
	int dir;

	i = 0;
	count = 0;
	data->texture_paths = ft_calloc(5, sizeof(char *));
	while (data->map[i] && count < 4)
	{
		off = ws_count(data->map[i]);
		dir = ft_directioncmp(&data->map[i][off]);
		if (dir != ERROR)
        {
			off += ws_count(&data->map[i][off + 2]);
			data->texture_paths[dir] = ft_substr(data->map[i], off + 2, ft_strlen(data->map[i]) - 3);
			data->map = ft_delindex(data->map, i);
			count++;
			i = 0;
        }
		else
			i++;
	}
	if (count != 4 || check_perms(data) == ERROR)
		return (ERROR);
	return (TRUE);
}

int color_check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',')
			return (ERROR);
		i++;
	}
	return (TRUE);
}

int int_len(int n)
{
	int i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}


int get_componants(t_data *data, int i)
{
	int r;
	int	g;
	int b;
	int idx;

	idx = 2;
	r = ft_atoi(&data->map[i][idx]);
	idx += int_len(r) + 1;
	g = ft_atoi(&data->map[i][idx]);
	idx += int_len(g) + 1;
	b = ft_atoi(&data->map[i][idx]);
	idx += int_len(b) + 1;
	data->colors[i] = (r << 16) + (g << 8) + (b << 1); 
	if (r > 255 || g > 255 || b > 255)
		return (ERROR);
	return (TRUE);
}

int ft_colorcmp(char *str)
{
	if (!ft_strncmp(str, "F", 1))
		return (C_F);
	if (!ft_strncmp(str, "C", 1))
		return (C_C);
	return (ERROR);
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
		idx = ft_colorcmp(&data->map[i][off]);
		if (idx != ERROR)
        {
			off += ws_count(&data->map[i][off]);
			if (color_check(&data->map[i][off + 2]) == ERROR || get_componants(data, count) == ERROR)
				return (ERROR);
			count++;
			i = 0;
        }
		else
			i++;
	}
	if (count < 2)
		return (ERROR);
	return (TRUE);	
}

int get_llength(char **map)
{
	int i;
	int j;
	int count;
	
	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		while(map[i][j])
			j++;
		if (j > count)
			count = j;
		i++;
	}
	return (count);
}

void fill_new_map(char **new_map, char **map, int llength)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < llength)
		{
			if (!map[i][j] || (map[i][j] && map[i][j] == ' '))
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

int check_all_direction(char **map, int i, int j)
{
	if ((!map[i - 1][j - 1] || map[i - 1][j - 1] == '2') ||
		(!map[i - 1][j] || map[i - 1][j] == '2') ||
		(!map[i - 1][j + 1] || map[i - 1][j + 1] == '2') ||
		(!map[i][j - 1] || map[i][j - 1] == '2') ||
		(!map[i][j + 1] || map[i][j + 1] == '2') ||
		(!map[i + 1][j - 1] || map[i + 1][j - 1] == '2') ||
		(!map[i + 1][j] || map[i + 1][j] == '2') ||
		(!map[i + 1][j + 1] || map[i + 1][j + 1] == '2'))
			return (ERROR);
	return (TRUE);
}

int check_closed(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' || data->map[i][j] == 'N')
				if (check_all_direction(data->map, i, j) == ERROR)
					return (ERROR);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int parse_map(int map_fd, t_data *data)
{
	get_raw_map(map_fd, data);
	if (get_texture_paths(data) == ERROR)
		return (ERROR);
	data->map = del_blank(data->map);
	if (get_colors(data) == ERROR)
		return (ERROR);
	data->map = del_blank(data->map);
	data->map = fill_blank(data->map);
	if (check_closed(data) == ERROR)
		return (ERROR);
	display(data->map);
	display(data->texture_paths);
	printf("F = %zu\n", data->colors[0]);
	printf("C = %zu\n", data->colors[1]);
	return (TRUE);
}


int main(int ac, char **av)
{
	int		map_fd;
	t_data	data;

	ft_bzero((void *) &data, sizeof(t_data));
	if (ac != 2)
		return (display_error("Error\n", &data));
	map_fd = check_map(av[1]);
	if (map_fd == ERROR)
		return (display_error("Error\n", &data));
	if (parse_map(map_fd, &data) == ERROR)
		return (display_error("Error\n", &data));
	free_data(&data);

	return (EXIT_SUCCESS);
}
