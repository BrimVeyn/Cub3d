/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:25:16 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 10:39:39 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_texture(char **texture)
{
	int	i;

	if (!texture)
		return ;
	i = 0;
	while (i < 4)
	{
		free(texture[i]);
		i++;
	}
	free(texture);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_data(t_data *data)
{
	if (data->window)
    {
		mlx_mouse_show(data->mlx, data->window);
		mlx_clear_window(data->mlx, data->window);
		mlx_destroy_image(data->mlx, data->imgs->img);
		mlx_destroy_image(data->mlx, data->minimap_img->img);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		free_int_tab(data->textures, 4 + BONUS);
		free_int_tab(data->minimap->coord_matrix, data->minimap->draw_size);
		free_int_tab(data->minimap->circle_matrix, data->minimap->draw_size);
		free_int_tab(data->minimap->rotated_matrix, data->minimap->draw_size);
		free_int_tab(data->minimap->filled_circle_matrix, data->minimap->draw_size);
		free(data->mlx);
		free(data->hud->frames[0].addr_int);
		free(data->hud->frames[1].addr_int);
		free(data->hud->frames[2].addr_int);
		free(data->hud->frames[3].addr_int);
		free(data->hud->frames);
		free(data->minimap->colors);
    }
	free(data->hud);
	free(data->minimap);
	free(data->walk_animation);
	free(data->fps);
	free(data->line);
	free(data->imgs);
	free(data->player);
	free(data->ray);
	free(data->minimap_img);
	free_tab(data->map);
	free_texture(data->texture_paths);
	free(data);
}
