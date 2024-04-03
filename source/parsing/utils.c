/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:51:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/03 10:52:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_reversecmp(char *str, char *cmp)
{
	int i;
	int j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(cmp) - 1;
	while (str[i] && cmp[j])
	{
		if (str[i] != cmp[j])
			return (ERROR);
		j--;
		i--;
	}
	return (TRUE);
}


int check_map(char *map)
{
	int fd;

	fd = 0;
	if (ft_reversecmp(map, ".cub") == ERROR)
		return (ERROR);
	fd = open(map, O_RDONLY);
	return (fd);
}

int display_error(char *error)
{
	fd_printf(2, "%fs", error);
	return (ERROR);
}

