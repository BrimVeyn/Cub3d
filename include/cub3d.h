/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:27:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/04 12:38:42 by bvan-pae         ###   ########.fr       */
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

enum
{
	DIR_NO,
	DIR_SO,
	DIR_WE,
	DIR_EA,
};

enum
{
	C_F,
	C_C,
};


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
int ft_isnumws(char *str);
int ff_mapline(t_data *data);
int has_letter(char *str);
int check_order(t_data *data);
int ft_directioncmp(char *str);
int check_perms(t_data *data);
int get_texture_paths(t_data *data);
int	ft_isws(char c);
int int_len(int n);
int ft_colorcmp(char c);
int color_check(char *str);
int get_componants(t_data *data, int i, int c, int idx);
int get_colors(t_data *data);
void fill_new_map(char **new_map, char **map, int llength);
char **fill_blank(char **map);
void fill_new_map(char **new_map, char **map, int llength);
char **fill_blank(char **map);
char	**ft_delindex(char **split, int i);
int ws_count(char *str);
int check_all_direction(char **map, int i, int j);
int ft_isdir(char c);
int check_closed(t_data *data);
int	check_onedir(t_data *data);
int check_multimap(t_data *data);
int get_llength(char **map);
int count_blank(char **map);

//-------------------------------------------------

#endif

