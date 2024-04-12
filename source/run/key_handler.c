/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:37:26 by nbardavi          #+#    #+#             */
/*   Updated: 2024/04/12 14:41:41 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == E_KEY)
		door_handler(data);
	if (keycode == ARROW_LEFT)
		data->player->camera_moved_x = 1;
	if (keycode == ARROW_RIGHT)
		data->player->camera_moved_y = 1;
	if (keycode == W_KEY)
		data->player->has_moved_y++;
	if (keycode == S_KEY)
		data->player->has_moved_y--;
	if (keycode == D_KEY)
		data->player->has_moved_x++;
	if (keycode == A_KEY)
		data->player->has_moved_x--;
	if (keycode == ESCAPE)
		close_and_exit(data);
	return (0);
}

int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == ARROW_LEFT)
		data->player->camera_moved_x = 0;
	if (keycode == ARROW_RIGHT)
		data->player->camera_moved_y = 0;
	if (keycode == W_KEY)
		data->player->has_moved_y--;
	if (keycode == S_KEY)
		data->player->has_moved_y++;
	if (keycode == D_KEY)
		data->player->has_moved_x--;
	if (keycode == A_KEY)
		data->player->has_moved_x++;
	return (0);
}
