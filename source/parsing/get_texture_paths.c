/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:26:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 13:33:32 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdlib.h>

int	ft_directioncmp(char *str)
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

int	check_perms(t_data *data)
{
	int	tmp_fd;
	int	i;

	i = 0;
	while (i < 4)
	{
		tmp_fd = open(data->texture_paths[i], O_RDONLY);
		if (tmp_fd == ERROR)
			return (ERROR);
		close(tmp_fd);
		if (ft_reversecmp(data->texture_paths[i], ".xpm") == ERROR)
			return (ERROR);
		i++;
	}
	return (TRUE);
}

int	get_texture_paths_loop(t_data *data, int *i, int *count)
{
	int	off;
	int	dir;

	off = ws_count(data->map[*i]);
	dir = ft_directioncmp(&data->map[*i][off]);
	if (dir != ERROR)
	{
		off += ws_count(&data->map[*i][off + 2]);
		if (data->texture_paths[dir])
			return (ERROR);
		data->texture_paths[dir] = ft_substr(data->map[*i], off + 2,
				ft_strlen(data->map[*i]) - 3);
		data->map = ft_delindex(data->map, *i);
		if (!data->map)
			close_and_exit(data);
		(*count)++;
		*i = 0;
	}
	else
		(*i)++;
	return (TRUE);
}

int	get_texture_paths(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	data->texture_paths = ft_calloc(5, sizeof(char *));
	if (!data->texture_paths)
		close_and_exit(data);
	while (data->map[i])
		if (get_texture_paths_loop(data, &i, &count) == ERROR)
			return (ERROR);
	if (count != 4 || check_perms(data) == ERROR)
		return (ERROR);
	return (TRUE);
}
