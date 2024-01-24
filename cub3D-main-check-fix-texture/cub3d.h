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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

# define PI 3.14159265359
# define P2 PI/2
# define P3 3*PI/2
//# define DR 0.0174533

typedef enum {
    NORTH,
    SOUTH,
    WEST,
    EAST,
    NONE  // Utilisé lorsqu'aucun mur n'est touché
} WallDirection;

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

typedef struct s_struture_map
{
	char	*map;
	char	*buff;
	char	**temp_list;
	int		i;
	int		j;
	int		temp;
	int		mapX;
	int		mapY;
	int		mapS;
}	t_structure_map;

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
	void	*img_player;
	void	*img_wall;
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
	void	*pedro_wall;
	void *north_texture;
    void *south_texture;
    void *west_texture;
    void *east_texture;
    int texture_width;
    int texture_height;
}	t_structure_img;

typedef struct s_struture_windows
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_structure_windows;

typedef struct s_structure_main
{
	int					fd;
    struct timeval start_time;
    struct timeval end_time;
    int frame_count;
	t_structure_windows	s_win;
	t_structure_img		s_img;
	t_structure_map		s_map;
	t_structure_player	s_player;
}	t_structure_main;



//ft_utils_split.c 5 / 5
char	**ft_split(char const *s, char c);

//ft_utils_gnl.c 4 / 5
char	*get_next_line(int fd);

//ft_utils_str_1.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *left_str, char *buff);
char	*ft_strchr(const char *s, int c);

//ft_key.c 3/5
int		*kill_prog(t_structure_main *w);
void	move(int key, t_structure_main *w);
int		deal_key(int key, t_structure_main *w);

//ft_utils_convert.c 1/5
char	*ft_itoa(int nb);

//parsing
char* read_map(const char* filename, int* length);
int is_map_closed(char* map, int width, int height);
bool parse_map(const char* filename, t_structure_map *map_info);
void drawRay(t_structure_main *w, int r, float rx, float ry, float disT, WallDirection wallDir, int numRays, int color);
//wall texturesv
void exit_error(t_structure_main *w);
void load_wall_textures(t_structure_main *w);
//transparence
int blendColor(int color1, int color2, float alpha);
void drawTransparentSquare(t_structure_main *w, int x, int y, int color, float alpha);
//2D map
void draw_square(t_structure_main *w, int x, int y, int color);
void draw_map(t_structure_main *w);

#endif
