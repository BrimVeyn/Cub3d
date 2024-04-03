/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:27:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/03 16:05:37 by bvan-pae         ###   ########.fr       */
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


//--------------------STRUCT-----------------------

typedef struct s_data
{

	char	**map;
	char	**texture_paths;
	size_t	colors[2];

}				t_data;


//---------------------PARSING---------------------

int ft_reversecmp(char *str, char *cmp);
int check_map(char *map);
int display_error(char *error, t_data *data);
char	*ft_realloc(char *ptr, size_t size);
void	get_raw_map(int map_fd, t_data* data);
void free_tab(char **tab);
void free_data(t_data *data);
char **del_nfirst(int n, char **map);
int	ft_tablen(char **tab);
char **del_blank(char **map);

//-------------------------------------------------

#endif

