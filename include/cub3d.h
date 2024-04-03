/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:27:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/03 10:53:13 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERROR -1
# define TRUE 1
# define FALSE 0

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "../libftprintf/header/ft_printf.h"
#include "../source/minilibx/mlx.h"
#include "../source/minilibx/mlx_int.h"


//---------------------PARSING---------------------

int ft_reversecmp(char *str, char *cmp);
int check_map(char *map);
int display_error(char *error);

//-------------------------------------------------

#endif

