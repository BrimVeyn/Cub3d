/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:22:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/11 16:12:58 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_ray(t_data *data)
{
	data->ray->camerax = 0;
	data->ray->raydirx = 0;
	data->ray->raydiry = 0;
	data->ray->deltadistx = 0;
	data->ray->deltadisty = 0;
	data->ray->sidedistx = 0;
	data->ray->sidedisty = 0;
	data->ray->perpwalldist = 0;
	data->ray->mapy = 0;
	data->ray->mapx = 0;
	data->ray->stepx = 0;
	data->ray->stepy = 0;
	return ;
}

void init_data(t_data *data)
{
	fill_player_position(data);
	if (data->map[(int)data->player->posx][(int)data->player->posy] == 'N')
    {
		data->player->dirx = -1; //1
		data->player->diry = 0; //0
		data->player->planex = 0; //0
		data->player->planey = 0.66; //-0.66
    }
	else if (data->map[(int)data->player->posx][(int)data->player->posy] == 'S')
    {
		data->player->dirx = 1;
		data->player->diry = 0;
		data->player->planex = 0;
		data->player->planey = -0.66;
    }
	else if (data->map[(int)data->player->posx][(int)data->player->posy] == 'E')
    {
		data->player->dirx = 0;
		data->player->diry = 1;
		data->player->planex = 0.66;
		data->player->planey = 0;
    }
	else if (data->map[(int)data->player->posx][(int)data->player->posy] == 'W')
    {
		data->player->dirx = 0;
		data->player->diry = -1;
		data->player->planex = -0.66;
		data->player->planey = 0;
    }
}

void fill_player_position(t_data *data)
{
	int i;
	int j;

	i = 0;
	display(data->map);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
			|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->player->posx = i + 0.5;
				data->player->posy = j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void init_imgs(t_data *data)
{

	data->minimap_img = ft_calloc(2, sizeof(t_img_data));
	data->minimap_img->img = mlx_xpm_file_to_image(data->mlx, "./textures/head.xpm", &data->tex_size, &data->tex_size);
	data->textures = ft_calloc(5, sizeof(int *));
    if (!data->textures)
        display_error("Cub3d: Error allocating textures buffer\n", data);
    data->textures[NORTH] = xpm_to_tab(data, &data->tex_size, &data->tex_size, data->texture_paths[NORTH]);
    data->textures[SOUTH] = xpm_to_tab(data, &data->tex_size, &data->tex_size, data->texture_paths[SOUTH]);
    data->textures[EAST] = xpm_to_tab(data, &data->tex_size, &data->tex_size, data->texture_paths[EAST]);
    data->textures[WEST] = xpm_to_tab(data, &data->tex_size, &data->tex_size, data->texture_paths[WEST]);
	calcul_hud(data);
}

int *init_minimap_colors(t_data *data)
{
	int *colors;

	colors = ft_calloc(6, sizeof(int));
	if (!colors)
		display_error("Couldn't allocate minimap colors buffer\n", data);
	colors[0] = 0xFAF3DD; //0
	colors[1] = 0xad6a44; //1
	colors[2] = 0x2f3038; //-1
	colors[3] = 0x19d043; //30
	colors[4] = 0xffffff; //border
	return (colors);
}
