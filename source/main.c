/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:28:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/03 10:53:31 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int ac, char **av)
{
	int map_fd;

	if (ac != 2)
		return (display_error("Error\n"));
	map_fd = check_map(av[1]);
	if (map_fd == ERROR)
		return (display_error("Error\n"));

	return (EXIT_SUCCESS);
}
