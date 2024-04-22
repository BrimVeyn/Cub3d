/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:03:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/22 13:24:25 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdlib.h>

int	ft_reversecmp(char *str, char *cmp)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(cmp) - 1;
	while (str[i] && cmp[j] && j >= 0)
	{
		if (str[i] != cmp[j])
			return (ERROR);
		j--;
		i--;
	}
	return (TRUE);
}

int	check_map(char *map)
{
	int	fd;

	fd = 0;
	if (ft_reversecmp(map, ".cub") == ERROR)
		return (ERROR);
	fd = open(map, O_RDONLY);
	return (fd);
}

void	display_error(char *error, t_data *data)
{
	fd_printf(2, "%fs", error);
	free_data(data);
	exit(EXIT_FAILURE);
}

int	ft_isws(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (TRUE);
	return (ERROR);
}

int	int_len(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
