/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:34:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 13:34:16 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "minilibx/mlx.h"
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	display(char **map);
void	print_strings(t_data *data);

int	parse_map(int map_fd, t_data *data)
{
	get_raw_map(map_fd, data);
	if (check_order(data) == ERROR)
		display_error("Cub3d: Wrong order\n", data);
	if (get_texture_paths(data) == ERROR)
		display_error("Cub3d: Wrong texture path\n", data);
	if (get_colors(data) == ERROR)
		display_error("Cub3d: Error colors\n", data);
	if (check_onedir(data) == ERROR)
		display_error("Cub3d: Only one player is allowed", data);
	data->map = del_blank(data->map);
	if (!data->map)
		close_and_exit(data);
	data->map = fill_blank(data->map);
	if (!data->map)
		close_and_exit(data);
	if (check_closed(data) == ERROR)
		display_error("Cube3d: Map is not closed\n", data);
	if (check_multimap(data) == ERROR)
		display_error("Cub3d: Multimap detected\n", data);
	return (TRUE);
}

int	ray_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	view_changed(data);
	player_pos_changed(data);
	reset_screen(data);
	init_ray(data);
	ray_cast(data);
	if (BONUS)
	{
		display_minimap(data);
		draw_crosshair(data, 0xFFFFFF, 5);
		draw_crosshair(data, 0xFFFFFF, 4);
		gun_animation(data);
	}
	mlx_put_image_to_window(data->mlx, data->window, data->imgs->img, 0, 0);
	print_strings(data);
	return (TRUE);
}

int	*xpm_to_tab(t_data *data, int *width, int *height, char *path)
{
	t_img_data	tmp;
	int			*buffer;
	int			x;
	int			y;

	tmp.img = mlx_xpm_file_to_image(data->mlx, path, width, height);
	if (!tmp.img)
		display_error("Error, couldn't load texture.\n", data);
	tmp.addr_int = (int *)mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_lengh,
			&tmp.endian);
	buffer = ft_calloc(1, sizeof * buffer * *width * *height);
	if (!buffer)
		display_error("Cub3d: Error allocating buffer\n", data);
	y = -1;
	while (++y < *height)
	{
		x = 0;
		while (x < *width)
		{
			buffer[y * *width + x] = tmp.addr_int[y * *width + x];
			++x;
		}
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	run_map(t_data *data)
{
	init_data(data);
	init_minimap_circle(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		close_and_exit(data);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->imgs->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->imgs->addr = mlx_get_data_addr(data->imgs->img, &data->imgs->bpp,
			&data->imgs->line_lengh, &data->imgs->endian);
	init_animations(data);
	init_imgs(data);
	mlx_hook(data->window, 17, 0, close_window, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, key_handler, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, key_release_handler,
		data);
	// mlx_mouse_hide(data->mlx, data->window);
	mlx_hook(data->window, MotionNotify, PointerMotionMask, handle_mouvement,
		data);
	mlx_mouse_hook(data->window, handle_mouse, data);
	mlx_loop_hook(data->mlx, &ray_loop, (void *)data);
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	int		map_fd;
	t_data	*data;

	data = ft_calloc(2, sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->fps = ft_calloc(2, sizeof(t_fps));
	if (!data->fps)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	data->fps->old_time = get_time();
	if (ac != 2)
		display_error("Cub3d: Usage: ./cub3d <path_to_map>\n", data);
	map_fd = check_map(av[1]);
	if (map_fd == ERROR)
		display_error("Cub3d: Wrong path or not a .cub file\n", data);
	parse_map(map_fd, data);
	run_map(data);
	free_data(data);
	return (EXIT_SUCCESS);
}
