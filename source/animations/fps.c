/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:59:35 by nbardavi          #+#    #+#             */
/*   Updated: 2024/04/22 11:28:58 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/time.h>

int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf(" Error getting time ");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	draw_crosshair(t_data *data, int color, int r)
{
	int		cx;
	int		cy;
	double	angle;
	int		x;
	int		y;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	angle = 0.0;
	while (angle < 2 * PI)
	{
		x = cx + (int)(r * cos(angle));
		y = cy + (int)(r * sin(angle));
		my_mlx_pixel_put(data, x, y, color);
		angle += 0.01;
	}
}

void	animation(t_animation *walk)
{
	if (walk->offset >= 8)
		walk->trigger_offset = 1;
	if (walk->offset <= -8)
		walk->trigger_offset = 0;
	if (walk->trigger_offset == 0)
		walk->offset += walk->animation_speed;
	else
		walk->offset -= walk->animation_speed;
}

void	init_animations(t_data *data)
{
	data->walk_animation = ft_calloc(2, sizeof(t_animation));
	data->walk_animation->trigger_offset = 0;
	data->walk_animation->offset = 0;
	data->walk_animation->animation_speed = 2;
	data->hud = ft_calloc(2, sizeof(t_hud));
	data->hud->frames = ft_calloc(5, sizeof(t_img_data));
	data->hud->animation_frame = 0;
}
