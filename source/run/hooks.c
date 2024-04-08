/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:45:32 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/08 10:09:18 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


void close_and_exit(t_data *data)
{
	mlx_clear_window(data->mlx, data->window);
	mlx_destroy_image(data->mlx, data->imgs->img);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->imgs);
	free(data->player);
	free(data->ray);
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	ft_hook(int keycode, void *param)
{
	t_data *data;

	data = (t_data *) param;
	if (keycode == ESCAPE)
		close_and_exit(data);
	return (0);
}

int	close_window(t_data *data)
{
	close_and_exit(data);
	return (0);
}

int key_handler(int keycode, t_data *data)
{
	if (keycode == ARROW_LEFT)
		data->player->camera_moved_x = 1;
	if (keycode == ARROW_RIGHT)
		data->player->camera_moved_y = 1;
	if (keycode == W_KEY)
		data->player->has_moved_y = 1;
	if (keycode == S_KEY)
		data->player->has_moved_y = -1;
	if (keycode == D_KEY)
		data->player->has_moved_x = 1;
	if (keycode == A_KEY)
		data->player->has_moved_x = -1;
	if (keycode == ESCAPE)
		close_and_exit(data);
	return (0);
}

int key_release_handler (int keycode, t_data *data)
{
	if (keycode == ARROW_LEFT)
		data->player->camera_moved_x = 0;
	if (keycode == ARROW_RIGHT)
		data->player->camera_moved_y = 0;
	if (keycode == W_KEY)
		data->player->has_moved_y = 0;
	if (keycode == S_KEY)
		data->player->has_moved_y = 0;
	if (keycode == D_KEY)
		data->player->has_moved_x = 0;
	if (keycode == A_KEY)
		data->player->has_moved_x = 0;
	return (0);
}
