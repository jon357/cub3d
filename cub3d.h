/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:56:52 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/30 16:44:11 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <assert.h>
# include "include/mlx.h"

# define BUFFER_SIZE 100000
# define PI 3.14159265359
# define P2 1.57079632679
# define P3 4.71238898038
# define COLBUF 1
# define NUMRAY 1280
# define FOVIEW 60
# define DISRAY 1000000
# define DOF 120
# define WIDTH 1680
# define HEIGHT 720
# define BOV 400
# define MAX_LINE_LENGTH 100000
# define DX_LENGTH 8

typedef enum s_WallDirection
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	NONE
}	t_WallDirection;

typedef struct s_img
{
	int		height;
	int		width;
	int		ground_width;
	void	*i;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_struture_player
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
}	t_structure_player;

typedef struct s_struture_img
{
	void	*buffer;
	char	*addr;
	int		bpp;
	int		endian;
	int		ground_height;
	int		ground_width;
	void	*ground;
	int		line_len;
	int		bpp_bis;
	int		endian_bis;
	int		line_len_bis;
	void	*test[27];
	void	*roomadslam[10];
	void	*tgsway[20];
	void	*north_texture;
	void	*south_texture;
	void	*west_texture;
	void	*east_texture;
	void	*door_texture;
	void	*open_door_texture;
	int		texture_width;
	int		texture_height;
}	t_structure_img;

typedef struct s_struture_windows
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_structure_windows;

typedef struct s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*door;
	char			*door_open;
	unsigned int	floor_color;
	unsigned int	ceil_color;
}	t_texture;

typedef struct s_struture_map
{
	char				*map;
	char				*buff;
	char				**temp_list;
	int					i;
	int					j;
	int					temp;
	int					map_x;
	int					map_y;
	int					map_s;
	float				player_x;
	float				player_y;
	char				player_direction;
	t_structure_windows	s_win;
}	t_structure_map;

typedef struct s_sprite
{
	void	*frames[3];
	int		width;
	int		height;
	int		current_frame;
	float	world_x;
	float	world_y;
	float	distance;
}	t_sprite;

typedef struct s_structure_main
{
	int					fd;
	t_structure_windows	s_win;
	t_structure_img		s_img;
	t_structure_map		s_map;
	t_structure_player	s_player;
	t_texture			*t;
	char				current_wall_type;
	t_sprite			sprite;
	int					error;
}	t_structure_main;

typedef struct s_res_params
{
	char	*original_data;
	void	*rescaled_img;
	char	*rescaled_data;
	float	x_ratio;
	float	y_ratio;
	int		original_x;
	int		original_y;
	int		pixel_pos_rescaled;
	int		pixel_pos_original;
}	t_res_params;

typedef struct s_rescale_params
{
	void			*original_img;
	int				original_width;
	int				original_height;
	int				new_width;
	int				new_height;
	int				px;
	int				py;
	t_res_params	*res;
}	t_rescale_params;

typedef struct s_position_params
{
	int		*future_px;
	int		*future_py;
	int		pdx;
	int		pdy;
	int		collision_buffer;
	int		px;
	int		py;
	double	pa;
	char	direction;
}	t_position_params;

typedef struct s_map_params
{
	t_structure_map	*map_info;
	const char		*buffer;
	int				length;
	int				*max_width;
	int				*height;
	int				*current_width;
	int				*is_new_line;
}	t_map_params;

typedef struct s_square_params
{
	t_structure_main	*w;
	int					x;
	int					y;
	int					xo;
	int					yo;
	int					color;
}	t_square_params;

typedef struct s_sky_ground_params
{
	t_structure_main	*w;
	int					start_height;
	int					end_height;
	int					color;
	int					background_off_setx;
}	t_sky_ground_params;

typedef struct s_line_params
{
	t_structure_main	*w;
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					color;
}	t_line_params;

typedef struct s_line_deltas
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	t_line_params	*params;
}	t_line_deltas;

typedef struct s_texture_params
{
	t_structure_main	*w;
	int					start_x;
	int					end_x;
	float				line_off;
	float				line_h;
	t_WallDirection		wall_dir;
	float				rx;
	float				ry;
	float				dis_t;
}	t_texture_params;

typedef struct s_ray_params
{
	t_structure_main	*w;
	t_square_params		sq;
	t_texture_params	texture;
	int					r;
	int					tile_size;
	float				rx;
	float				ry;
	float				dis_t;
	t_WallDirection		wall_dir;
	int					num_rays;
	int					color;
	int					start3d_height;
	int					max3d_height;
	float				line_h;
	float				line_off;
	int					background_off_setx;
	int					raywidth;
}	t_ray_params;

typedef struct s_ray_calc_params
{
	t_structure_main	*w;
	float				ra;
	float				*dis_ray;
	float				*rx;
	float				*ry;
	t_WallDirection		*wall_dir;
	float				xo;
	float				yo;
	int					dof;
}	t_ray_calc_params;

typedef struct s_texture_data
{
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture_data;

typedef struct s_init_params
{
	t_structure_main	*w;
	int					tilesize;
	int					numrays;
	float				fo_v;
	float				d_r;
}	t_init_params;

typedef struct s_ray_properties
{
	float			dis_h;
	float			dis_v;
	t_WallDirection	hwalldir;
	t_WallDirection	vwalldir;
	float			hx;
	float			hy;
	float			vx;
	float			vy;
}	t_ray_properties;

typedef struct s_base_params
{
	int		tilesize;
	int		numrays;
	float	fo_v;
	float	d_r;
	float	ra;
}	t_base_params;

typedef struct s_ray_state
{
	float			dis_h;
	float			dis_v;
	float			dis_t;
	float			hx;
	float			hy;
	float			vx;
	float			vy;
	t_WallDirection	hwalldir;
	t_WallDirection	vwalldir;
}	t_ray_state;

typedef struct s_ray_calc
{
	t_structure_main	*w;
	int					r;
	int					color;
}	t_ray_calc;

typedef struct s_drawrays2d_params
{
	t_base_params		base_params;
	t_ray_state			ray_state;
	t_ray_calc			ray_calc;
	t_ray_params		rayparams;
	t_ray_calc_params	hrayparams;
	t_ray_calc_params	vrayparams;
}	t_drawrays2d_params;

typedef struct s_state
{
	int	jkl;
	int	yui;
}	t_state;

typedef struct s_global_struct
{
	t_structure_main	*w;
	t_state				state;
}	t_global_struct;

typedef struct s_draw_params
{
	int		texturewidth;
	int		textureheight;
	int		texturex;
	int		texture_y;
	int		a;
	int		b;
	int		c;
	double	step;
	int		x;
	int		i;
}	t_draw_params;

typedef struct s_collision_params
{
	int	dx[DX_LENGTH];
	int	dy[DX_LENGTH];
}	t_collision_params;

typedef struct s_player_info
{
	bool			*found_player;
	t_structure_map	*map;
	int				line_number;
	int				column_number;
}	t_player_info;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map_check
{
	char	*map;
	int		max_width;
	int		height;
}	t_map_check;

char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int		*kill_prog(t_structure_main *w);
void	move(int key, t_structure_main *w);
int		deal_key(int key, t_structure_main *w);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *left_str, char *buff);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		can_move_to(t_structure_main *w, double future_x, double future_y);
char	*ft_itoa(int nb);
void	draw_black_ground(t_ray_params *params, t_texture_params tparams);
int		is_map_closed(char *map, int width, int height);
bool	parse_map(const char *map_content,
			int length, t_structure_map *map_info);
int		check_borders(char *map, int maxWidth, int height);
int		check_interior(char *map, int maxWidth, int height);
void	exit_error(t_structure_main *w);
void	update_max_dimensions(t_map_params *params);
void	process_character(t_map_params *params, int *i);
void	get_map_dimensions(t_map_params *params);
void	fill_map_space(t_structure_map *map_info, int maxWidth, int height);
void	copy_map_data(t_map_params *params);
bool	load_cub_file(const char *filename,
			t_texture *textures, t_structure_map *map_info);
bool	parse_texture_line(const char *line, t_texture *textures);
bool	handle_map(int fd, char **map_buffer, int *map_length);
bool	parse_color_line(const char *line, unsigned int *color);
bool	parse_number_from_str(const char **str, int *number);
bool	is_valid_texture(const char *line);
bool	handle_textures(int fd, t_texture *textures);
bool	find_player(const char *map_content,
			int length, t_structure_map *map);
void	calculate_map(t_structure_map *map_info);
void	load_wall_textures(t_structure_main *w);
void	draw_texture(t_texture_params *tex_params);
int		get_texture_color(t_structure_main *w,
			t_WallDirection wallDir, int textureX, int textureY);
void	draw_yolo(t_ray_params *rparams, t_texture_params *tparams, int deca);
void	drawray(t_ray_params *ray_params);
void	draw_background(t_structure_main *w);
float	correctFisheye(float distance, float ra, float playerAngle);
void	rescale_image(t_rescale_params *params, t_structure_main *w);
void	draw_square(t_structure_main *w, int x, int y, int color);
void	draw_map(t_structure_main *w);
void	put_pixel_img(t_structure_main *w, int x, int y, int color);
void	draw_square_raw(t_square_params *params);
void	draw_line(t_line_params *params);
void	drawrays2d(t_structure_main *w);
void	calculateverticalray(t_ray_calc_params *params);
void	handle_ra_vertical(t_ray_calc_params *params, float nTan, int tileSize);
void	calculatehorizontalray(t_ray_calc_params *params);
void	handle_ra_not_equal_pi(t_ray_calc_params *params,
			float atan, int tilesize);
float	dist(float ax, float ay, float bx, float by);
void	init_windows(t_structure_main *w);
void	init_player(t_structure_main *w);
void	init_mlx_and_window(t_structure_main *w);
void	sleep_mouse(t_global_struct *global_struct);
void	init_line_params(t_line_params *lineparams, t_ray_params *rayParams);
void	init_texture_params(t_texture_params *textureparams,
			t_ray_params *rayParams);
void	initialize_variables(int *i, int *line_number,
			int *column_number, bool *found_player);
bool	check_for_player(char current_char, bool *found_player);
void	update_player_info(t_structure_map *map_info,
			int line_number, int column_number, char player_direction);
void	update_position(char current_char,
			int *line_number, int *column_number);
bool	check_for_multiple_players(bool found_player);
int		check_boundaries(t_point p, t_map_check *map_check);
int		is_space_surrounded_by_walls(t_map_check *map_check, t_point p);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t newsize, size_t oldsize);

#endif
