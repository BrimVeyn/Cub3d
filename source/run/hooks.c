/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:45:32 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 11:23:27 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void free_int_tab(int **tab, int size)
{
	int i;
	
	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

void close_and_exit(t_data *data)
{
	mlx_mouse_show(data->mlx, data->window);
	mlx_clear_window(data->mlx, data->window);
	mlx_destroy_image(data->mlx, data->imgs->img);
	mlx_destroy_image(data->mlx, data->minimap_img->img);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free_int_tab(data->textures, 4);
	free(data->mlx);
	free_int_tab(data->minimap->coord_matrix, data->minimap->draw_size);
	free_int_tab(data->minimap->circle_matrix, data->minimap->draw_size);
	free_int_tab(data->minimap->rotated_matrix, data->minimap->draw_size);
	free_int_tab(data->minimap->filled_circle_matrix, data->minimap->draw_size);
	free(data->minimap->colors);
	free(data->minimap);
	free(data->walk_animation);
	free(data->fps);
	free(data->line);
	free(data->imgs);
	free(data->player);
	free(data->ray);
	free(data->minimap_img);
	free_data(data);
	free(data);
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

void door_handler(t_data *data)
{
	if (data->ray->aiming_at_door && data->map[data->ray->door_coord_x][data->ray->door_coord_y] == 'D')
	{
		data->map[data->ray->door_coord_x][data->ray->door_coord_y] = 'O';
	}
	if (data->ray->aiming_at_door == -1 && data->map[data->ray->door_coord_x][data->ray->door_coord_y] == 'O')
	{
		data->map[data->ray->door_coord_x][data->ray->door_coord_y] = 'D';
	}
	printf("is_aiming = %d\n", data->ray->aiming_at_door);
	printf("is_aiming at = %c\n", data->map[data->ray->door_coord_x][data->ray->door_coord_y]);
}

int key_handler(int keycode, t_data *data)
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

int key_release_handler (int keycode, t_data *data)
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
