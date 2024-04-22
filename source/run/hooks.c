/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:05:13 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 13:24:20 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_int_tab(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

void	close_and_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	ft_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESCAPE)
		close_and_exit(data);
	return (0);
}

int	close_window(t_data *data)
{
	close_and_exit(data);
	return (0);
}

void	door_handler(t_data *data)
{
	if (data->ray->aiming_at_door
		&& data->map[data->ray->door_coord_x][data->ray->door_coord_y] == 'D')
	{
		data->map[data->ray->door_coord_x][data->ray->door_coord_y] = 'O';
	}
	if (data->ray->aiming_at_open_door == 1
		&& data->map[data->ray->door_coord_x][data->ray->door_coord_y] == 'O')
	{
		data->map[data->ray->door_coord_x][data->ray->door_coord_y] = 'D';
	}
}
