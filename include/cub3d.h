/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:57:43 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/12 14:41:39 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define ERROR -1
#define TRUE 1
#define FALSE 0

#define WIDTH 1000
#define HEIGHT 1000

#define PI 3.14159265358979323846

#define ROTSPEED 0.06
#define MOVESPEED 0.08
#define MINIMAP_SIZE 9
#define MINIMAP_SCALE 20

#define OFFSET_X 40
#define OFFSET_Y 40

#define DOOR_PATH "./textures/blackstone.xpm"

#ifndef BONUS
#define BONUS 0
#endif

#include "../libftprintf/header/ft_printf.h"
#include "../source/minilibx/mlx.h"
#include "../source/minilibx/mlx_int.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {
	DIR_NO,
	DIR_SO,
	DIR_WE,
	DIR_EA,
};

enum {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR,
};

enum
{
	IDLE,
	SHOOT00,
	SHOOT01,
	SHOOT02,
};

enum {
	C_F,
	C_C,
};

enum {
	FLOOR,
	CEILING,
};

enum {
	PLUS = 61,
	MINUS = 45,
	WHEEL_DOWN = 5,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	P_KEY = 112,
	E_KEY = 101, 
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

typedef struct s_minimap {
	int **coord_matrix;
	int **circle_matrix;
	int **filled_circle_matrix;
	int **rotated_matrix;
	int *colors;
	int minimap_scale;
	int minimap_size;
	int draw_size;
	int circle_radius;
	int center_x;
	int center_y;
	double angle;

} t_minimap;

typedef struct s_img_data {
	void *img;
	void *addr;
	int *addr_int;
	int bpp;
	int line_lengh;
	int endian;
	int width;
	int height;
	int o_color;

} t_img_data;

typedef struct s_line {
	int x;
	int y;
	int y0;
	int y1;
	int tex_x;
	int tex_y;
	int span;
	int off;
} t_line;

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

typedef struct	s_animation
{
	int	offset;
	int animation_speed;
	int trigger_offset;
}				t_animation;

typedef struct	s_fps
{
	int	old_time;
	float fps_number;
}				t_fps;

typedef struct s_hud
{
	t_img_data	*frames;
	int			animation_frame;
}				t_hud;

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
	int		side;
	int		hit;
	int		aiming_at_door;
	int		door_coord_x;
	int		door_coord_y;

}				t_ray;

typedef struct s_data
{

	char		**map;
	char		**texture_paths;
	int			**textures;
	int			tex_size;
	size_t		colors[2];
	void		*mlx;
	void		*window;
	t_img_data	*imgs;
	t_player	*player;
	t_ray		*ray;
	t_minimap	*minimap;	
	t_img_data *minimap_img;
	t_line		*line;
	t_animation	*walk_animation;
	t_fps		*fps;
	t_hud		*hud;
}				t_data;

//---------------------PARSING---------------------

void get_raw_map(int map_fd, t_data *data);
void free_tab(char **tab);
void free_data(t_data *data);
void fill_new_map(char **new_map, char **map, int llength);
void fill_new_map(char **new_map, char **map, int llength);
char *ft_realloc(char *ptr, size_t size);
char **fill_blank(char **map);
char **del_nfirst(int n, char **map);
char **del_blank(char **map);
char **fill_blank(char **map);
char **ft_delindex(char **split, int i);
int ft_reversecmp(char *str, char *cmp);
int check_map(char *map);
void display_error(char *error, t_data *data);
int ft_tablen(char **tab);
int ft_isnumws(char *str);
int ff_mapline(t_data *data);
int has_letter(char *str);
int check_order(t_data *data);
int ft_directioncmp(char *str);
int check_perms(t_data *data);
int get_texture_paths(t_data *data);
int ft_isws(char c);
int int_len(int n);
int ft_colorcmp(char c);
int color_check(char *str);
int get_componants(t_data *data, int i, int c, int idx);
int get_colors(t_data *data);
int ws_count(char *str);
int check_all_direction(char **map, int i, int j);
int ft_isdir(char c);
int check_closed(t_data *data);
int check_onedir(t_data *data);
int check_multimap(t_data *data);
int get_llength(char **map);
int count_blank(char **map);
void init_n(t_data *data);
void init_s(t_data *data);
void init_w(t_data *data);
void init_e(t_data *data);
//-------------------------------------------------

void display(char **map); // fonction utilitaire a supprimer
void calcul_hud (t_data *data);

int *init_minimap_colors(t_data *data);
void init_data(t_data *data);
void init_imgs(t_data *data);
void init_ray(t_data *data);
void fill_player_position(t_data *data);
void reset_screen(t_data *data);

void display_minimap(t_data *data);
void render_minimap(t_data *data);
void paint_minimap(t_data *data);

void init_minimap_circle(t_data *data);
void draw_circle_matrix(t_minimap *m);
void fill_circle_matrix(t_data *data);
void add_circle_border(t_data *data);
void circle_matrix_rotation(t_data *data, double angle);
void render_minimap(t_data *data);
void paint_minimap(t_data *data);

int get_map_width(t_data *data);
int get_map_height(t_data *data);

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int ft_hook(int keycode, void *param);
int close_window(t_data *data);
int key_handler(int key, t_data *data);
int key_release_handler(int keycode, t_data *data);
int *xpm_to_tab( t_data *data, int *width, int *height, char *path);

void put_to_windows_without(t_data *data, t_img_data img, int offsetx, int offsety);
void calcul_hud (t_data *data);
void gun_animation(t_data *data);

int	get_time(void);
void draw_crosshair(t_data *data, int color, int r);
void animation(t_animation *walk);
void player_pos_changed(t_data *data);
void init_animations(t_data *data);
void view_changed(t_data *data);
int handle_mouvement(int x, int y, t_data *data);
int handle_mouse(int keycode, int x, int y, t_data *data);
int	key_handler(int keycode, t_data *data);
int	key_release_handler(int keycode, t_data *data);
void	door_handler(t_data *data);
void	close_and_exit(t_data *data);
#endif
