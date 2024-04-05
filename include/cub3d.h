/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:27:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/05 15:11:51 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERROR -1
# define TRUE 1
# define FALSE 0

# define WIDTH 1000
# define HEIGHT 1000


# define ROTSPEED 0.09
# define MOVESPEED 0.15

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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


enum
{
	PLUS = 61,
	MINUS = 45,
	WHEEL_DOWN = 5,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	P_KEY = 112,
	ARROW_LEFT = 65361,
	ARROW_UP = 65362,
	ARROW_RIGHT = 65363,
	ARROW_DOWN = 65364,
	LEFT = 1,
	UP = 2,
	RIGHT = 3,
	DOWN = 4,
	X = 0,
	Y = 1,
	ESCAPE = 65307,
	PLEFT = 91,
	PRIGHT = 93,
};

//--------------------STRUCT-----------------------

typedef struct s_img_data
{
	void			*img;
	void			*addr;
	int				bpp;
	int				line_lengh;
	int				endian;
	void			*next;

}					t_img_data;

typedef struct s_line
{
	int	x;
	int	y;
	int	y0;
	int	y1;
	int	tex_x;
	int	tex_y;
}				t_line;


typedef struct s_player
{
	int has_moved_x;
	int has_moved_y;
	int camera_moved_x;
	int camera_moved_y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	posx;
	double	posy;
}				t_player;


typedef struct	s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	double	perpwalldist;
	int		mapy;
	int		mapx;
	int		stepx;
	int		stepy;

}				t_ray;

typedef struct s_data
{

	char	**map;
	char	**texture_paths;
	size_t	colors[2];
	void		*mlx;
	void		*window;
	t_img_data	*imgs;
	t_player	*player;
	t_ray		*ray;
	t_line	line;

}				t_data;


//---------------------PARSING---------------------

void	get_raw_map(int map_fd, t_data* data);
void	free_tab(char **tab);
void	free_data(t_data *data);
void	fill_new_map(char **new_map, char **map, int llength);
void	fill_new_map(char **new_map, char **map, int llength);
char	*ft_realloc(char *ptr, size_t size);
char	**fill_blank(char **map);
char	**del_nfirst(int n, char **map);
char	**del_blank(char **map);
char	**fill_blank(char **map);
char	**ft_delindex(char **split, int i);
int		ft_reversecmp(char *str, char *cmp);
int		check_map(char *map);
int		display_error(char *error, t_data *data);
int		ft_tablen(char **tab);
int		ft_isnumws(char *str);
int		ff_mapline(t_data *data);
int		has_letter(char *str);
int		check_order(t_data *data);
int		ft_directioncmp(char *str);
int		check_perms(t_data *data);
int		get_texture_paths(t_data *data);
int		ft_isws(char c);
int		int_len(int n);
int		ft_colorcmp(char c);
int		color_check(char *str);
int		get_componants(t_data *data, int i, int c, int idx);
int		get_colors(t_data *data);
int		ws_count(char *str);
int		check_all_direction(char **map, int i, int j);
int		ft_isdir(char c);
int		check_closed(t_data *data);
int		check_onedir(t_data *data);
int		check_multimap(t_data *data);
int		get_llength(char **map);
int		count_blank(char **map);

//-------------------------------------------------


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_hook(int keycode, void *param);
int	close_window(t_data *data);
int key_handler(int key, t_data *data);


#endif

