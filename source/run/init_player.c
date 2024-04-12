/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:56:41 by nbardavi          #+#    #+#             */
/*   Updated: 2024/04/12 13:57:52 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_n(t_data *data)
{
	data->player->dirx = -1;
	data->player->diry = 0;
	data->player->planex = 0;
	data->player->planey = 0.66;
}

void	init_s(t_data *data)
{
	data->player->dirx = 1;
	data->player->diry = 0;
	data->player->planex = 0;
	data->player->planey = -0.66;
}

void	init_w(t_data *data)
{
	data->player->dirx = 0;
	data->player->diry = -1;
	data->player->planex = -0.66;
	data->player->planey = 0;
}

void	init_e(t_data *data)
{
	data->player->dirx = 0;
	data->player->diry = 1;
	data->player->planex = 0.66;
	data->player->planey = 0;
}
