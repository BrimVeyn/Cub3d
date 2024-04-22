/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:36:30 by nbardavi          #+#    #+#             */
/*   Updated: 2024/04/22 10:03:50 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	display(char **map)
{
	for (int i = 0; map[i]; i++)
		printf("%s\n", map[i]);
}

void	print_strings(t_data *data)
{
	char	*fps;

	if (BONUS)
		mlx_put_image_to_window(data->mlx, data->window, data->minimap_img->img,
			30 + data->minimap->draw_size / 2, 30 + data->minimap->draw_size
			/ 2);
	mlx_set_font(data->mlx, data->window, "8x16");
	data->fps->fps_number = 1000.0 / (get_time() - data->fps->old_time);
	fps = ft_sprintf("fps: %d", (int)data->fps->fps_number);
	mlx_string_put(data->mlx, data->window, 930, 20, 0xFFFFFF, fps);
	free(fps);
	if (BONUS && data->ray->t_txt_door)
		mlx_string_put(data->mlx, data->window, 410, 600, 0xFFFFFF,
			"press [E] to open/close");
	data->fps->old_time = get_time();
}
