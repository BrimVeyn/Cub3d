/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:28:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/04 12:36:46 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void display(char **map)
{
	for(int i = 0; map[i]; i++)
		printf("%s\n", map[i]);
}

int parse_map(int map_fd, t_data *data)
{
	get_raw_map(map_fd, data);
	if (check_order(data) == ERROR)
		return (ERROR);
	if (get_texture_paths(data) == ERROR)
		return (ERROR);
	if (get_colors(data) == ERROR)
		return (ERROR);
	data->map = del_blank(data->map);
	data->map = fill_blank(data->map);
	if (check_closed(data) == ERROR)
		return (ERROR);
	if (check_onedir(data) == ERROR)
		return (ERROR);
	if (check_multimap(data) == ERROR)
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
