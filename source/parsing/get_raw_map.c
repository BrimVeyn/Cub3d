/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:36:36 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 11:13:49 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdlib.h>

char	*ft_realloc(char *ptr, size_t size)
{
	char	*self;

	free(ptr);
	self = ft_calloc((size + 1), sizeof(char));
	if (!self)
		exit(EXIT_FAILURE);
	return (self);
}

int	count_line(char *map)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			count++;
		i++;
	}
	return (count + 1);
}

void	fill_map(char **splitted_map, char *map)
{
	int	s;
	int	e;
	int	i;
	int	k;

	i = 0;
	s = 0;
	k = 0;
	e = 0;
	while (map[i])
	{
		if (map[i] == '\n')
		{
			e = i;
			splitted_map[k] = ft_substr(map, s, e - s);
			k++;
			s = i + 1;
		}
		i++;
	}
}

char	**cub_split(char *map)
{
	char	**splitted_map;

	splitted_map = ft_calloc(count_line(map), sizeof(char *));
	if (!splitted_map)
	{
		exit(EXIT_FAILURE);
	}
	fill_map(splitted_map, map);
	return (splitted_map);
}

void	get_raw_map(int map_fd, t_data *data)
{
	int		bytes_read;
	int		read_size;
	char	*raw_map;

	bytes_read = 1;
	read_size = 2048;
	raw_map = ft_calloc(read_size, sizeof(char));
	if (!raw_map)
		exit(EXIT_FAILURE);
	while (1)
	{
		bytes_read = read(map_fd, raw_map, read_size);
		if (bytes_read < read_size)
			break ;
		read_size <<= 1;
		raw_map = ft_realloc(raw_map, read_size);
		close(map_fd);
	}
	data->map = cub_split(raw_map);
	if (!data->map)
		close_and_exit(data);
	close(map_fd);
	free(raw_map);
}
