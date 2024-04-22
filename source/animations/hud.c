/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:53:29 by nbardavi          #+#    #+#             */
/*   Updated: 2024/04/22 10:22:26 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	gun_animation(t_data *data)
{
	t_img_data	*fr;

	fr = data->hud->frames;
	if (data->hud->animation_frame >= 1 && data->hud->animation_frame < 4
		&& data->hud->animation_frame++)
		put_to_windows_without(data, fr[SHOOT00], WIDTH - fr[SHOOT00].width
			- 50, HEIGHT - fr[SHOOT00].height);
	else if (data->hud->animation_frame >= 4 && data->hud->animation_frame < 8
		&& data->hud->animation_frame++)
		put_to_windows_without(data, fr[SHOOT01], WIDTH - fr[SHOOT01].width
			- 50, HEIGHT - fr[SHOOT01].height);
	else if (data->hud->animation_frame >= 8 && data->hud->animation_frame < 12
		&& data->hud->animation_frame++)
		put_to_windows_without(data, fr[SHOOT02], WIDTH - fr[SHOOT02].width
			- 50, HEIGHT - fr[SHOOT02].height);
	else
	{
		data->hud->animation_frame = 0;
		put_to_windows_without(data, fr[IDLE], WIDTH - fr[IDLE].width - 50,
			HEIGHT - fr[IDLE].height);
	}
}

void	calcul_hud(t_data *data)
{
	int	w;
	int	h;
	int	i;

	i = 0;
	w = 0;
	h = 0;
	data->hud->frames[IDLE].addr_int = xpm_to_tab(data, &w, &h,
			"./textures/gun_sprites/gun_idle.xpm");
	data->hud->frames[SHOOT00].addr_int = xpm_to_tab(data, &w, &h,
			"./textures/gun_sprites/gun_shoot00.xpm");
	data->hud->frames[SHOOT01].addr_int = xpm_to_tab(data, &w, &h,
			"./textures/gun_sprites/gun_shoot01.xpm");
	data->hud->frames[SHOOT02].addr_int = xpm_to_tab(data, &w, &h,
			"./textures/gun_sprites/gun_shoot02.xpm");
	while (i < 4)
	{
		data->hud->frames[i].width = 512;
		data->hud->frames[i].height = 512;
		data->hud->frames[i++].o_color = -16777216;
	}
}

void	put_to_windows_without(t_data *data, t_img_data img, int offsetx,
		int offsety)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img.height)
	{
		j = 0;
		while (j < img.width)
		{
			if (img.addr_int[i * img.width + j] != img.o_color)
				my_mlx_pixel_put(data, offsetx + j, offsety + i, img.addr_int[i
					* img.width + j]);
			j++;
		}
		i++;
	}
}
