
#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"

# define MOVE_SPEED	0.007
# define ROT_SPEED	0.003

// handle window
# define IMG_WIDTH	640
# define IMG_HEIGHT	640
# define TEX_WIDTH	128
# define TEX_HEIGHT	128
# define EXIT		17
# define KEY_ESC	65307

//keys
# define UP		65362
# define DOWN	65364
# define RIGHT	65363
# define LEFT	65361

# define UP_W		119
# define DOWN_S		115
# define RIGHT_D	100
# define LEFT_A		97

# define SPRINT		65505

typedef float	t_color	__attribute__((vector_size (16)));
typedef float	t_v2f	__attribute__((vector_size (8)));
// typedef enum e_xyz {x, y}	t_xy;

enum e_parse
{
	NORTH = 1,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	OUT,
	PLAYER,
	MAP,
};

/* Image info for the MLX */
typedef struct s_img_info
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_img_info;

typedef	struct	s_control
{
	bool		w;
	bool		s;
	bool		a;
	bool		d;
}	t_control;

/* General structure */
typedef struct s_data
{
	// Window
	void		*win;
	void		*mlx;
	t_img_info	img;
	t_img_info	north;
	t_img_info	south;
	t_img_info	west;
	t_img_info	east;
	t_img_info	floor;
	t_img_info	ceiling;

	t_color		floor_color;
	t_color		ceiling_color;

	int			nb_side_parsed;

	int			img_width;
	int			img_height;

	// Game
	char 		**map;
	int			width;
	int			height;
	t_control	controls;

	// Raycasting
	t_v2f		plane;
	t_v2f		player_pos;
	t_v2f		camera_dir;

	//	Draw
	float		tex_pos;
	float		step_all;
	int			tex_x;
	int			side;

}	t_data;

/* Checkup_map */
bool	check_left_wall(char **map);
bool	check_right_wall(char **map);
int		nb_player(char **map);
bool	is_many_map(char **map);
bool	checkup_map(char **map);

/* Check_up_map_utils */
int		count_char_in_map(char c, char **map);
bool	is_char_in_map_are_normal(char **map);
bool	is_char_valid_in_map(char c);
bool	is_a_zero_next_to_wrong(char **map);

/* Fill_world */
bool	fill_north(t_data *data, char *line);
bool	fill_south(t_data *data, char *line);
bool	fill_west(t_data *data, char *line);
bool	fill_east(t_data *data, char *line);
bool	fill_map(t_data *data, char **line, int fd);
bool	fill_ceiling(t_data *data, char *line);
bool	fill_floor(t_data *data, char *line);

/* Mlx_handling */
void	ft_handle_key_arrow(int key, t_data *data);
int		key_event(int keycode, t_data *data);
void	ft_my_put_pixel(t_data *data, int x, int y, int color);
//void	put_col(t_data *data, int col, int start, int end, int color);

/* Parsing_utils */
void	free_strs(char ***strs);
void	put_strs(char **strs);
bool	is_a_white_space(char c);
int		identify_line(char *str);
void	put_v2f(t_v2f vecteur);
int		count_char_in_str(char c, char *str);
float	abs_value(float x);

/* Render */
t_v2f	get_ray(t_data *data, int x);
void	next_cube(t_data *data, t_v2f ray, int x);
void	render(t_data *data);

/* Setup_mlx */
int		data_clear(t_data *data);
bool	setup_mlx(t_data *data);

/* Setup_player */
bool	find_player(t_data *data);

/* Setup_world */
bool	fill_new_line(t_data *data, char **line, int fd);
bool	setup_world(t_data *data, char *map);

/* Minimap */
void	draw_minimap(t_data *data);
void	draw_ray(t_data *data);

void	draw_slice(t_data *data, int x, int start, int end);
bool	atocolor(char *str, t_color *color);
void	move(t_data *data);
int		key_release(int key, t_data *data);


#endif
