/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:58:33 by kquerel           #+#    #+#             */
/*   Updated: 2024/01/17 15:45:25 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"

// Movement Macros
# define MOVE_SPEED		0.0045
# define ROT_SPEED		0.0015

// Window Macros
# define IMG_WIDTH		640
# define IMG_HEIGHT		640
# define TEX_WIDTH		128
# define TEX_HEIGHT		128
# define MINIMAP_WIDTH	20
# define MINIMAP_HEIGHT 20
# define TILE_SIZE		8

# define PI				3.14

// Keys Macros
# define UP				65362
# define DOWN			65364
# define RIGHT			65363
# define LEFT			65361
# define UP_W			119
# define DOWN_S			115
# define RIGHT_D		100
# define LEFT_A			97
# define EXIT			17
# define KEY_ESC		65307

// Game Macros
# define DOOR_OPENED	'O'
# define DOOR_CLOSED	'D'

typedef float	t_color	__attribute__((vector_size (16)));
typedef float	t_v2f	__attribute__((vector_size (8)));

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

typedef struct s_control
{
	bool		w;
	bool		s;
	bool		a;
	bool		d;
	bool		left_arrow;
	bool		right_arrow;
	bool		left_mouse;
	bool		right_mouse;
}	t_control;

/* General structure */
typedef struct s_data
{
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

	char		**map;
	int			width;
	int			height;
	t_control	controls;

	t_v2f		plane;
	t_v2f		player_pos;
	t_v2f		camera_dir;

	float		tex_pos;
	float		step_all;
	int			tex_x;
	int			side;

	int			map_x;
	int			map_y;
	t_v2f		step;
	t_v2f		side_dist;
	int			draw_start;
	int			draw_end;

	void		*minimap;
	int			dir;

	int			fd;

	bool		in_win;
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
void	err(char *s);

/* Draw */
void	ft_my_put_pixel(t_data *data, int x, int y, int color);
void	draw_floor(t_data *data, int x, int start, int *i);
void	draw_wall(t_data *data, int x, int end, int *i);
void	draw_ceiling(t_data *data, int x, int *i);
void	draw_slice(t_data *data, int x);

/* Fill_world */
bool	fill_map(t_data *data, char **line);
bool	fill_ceiling(t_data *data, char *line);
bool	fill_floor(t_data *data, char *line);

/* Fill_sides */
bool	fill_north(t_data *data, char *line);
bool	fill_south(t_data *data, char *line);
bool	fill_west(t_data *data, char *line);
bool	fill_east(t_data *data, char *line);

/* Mlx_handling_1 */
void	ft_handle_key_arrow(int key, t_data *data);
void	move(t_data *data);
int		key_release(int key, t_data *data);
int		key_event(int keycode, t_data *data);

/* Mlx_handling_2 */
void	rotate_camera(t_data *data);
void	move_longitudinal(t_data *data);
void	move_sideways(t_data *data);

/* Parsing_utils_1 */
void	free_strs(char ***strs);
bool	is_a_white_space(char c);
int		identify_line(char *str);
int		count_char_in_str(char c, char *str);
float	abs_value(float x);

/* Parsing_utils_2 */
void	jump_int(char **str);
bool	atocolor(char *str, t_color *color);

/* Render */
t_v2f	get_ray(t_data *data, int x);
void	render(t_data *data);

/* Setup_mlx */
void	init_values(t_data *data);
int		data_clear(t_data *data);
bool	setup_mlx(t_data *data);

/* Setup_player */
bool	find_player(t_data *data);

/* Setup_world */
bool	fill_new_line(t_data *data, char **line);
bool	setup_world(t_data *data, char *map);

/* Minimap */
void	draw_minimap(t_data *data, int x, int y);
void	draw_map_components(t_data *data, int x, int y, int color);

/* Render_1 */
t_v2f	get_ray(t_data *data, int x);
void	wall_calc(t_data *data, t_v2f ray, float perp_wall_dist);
t_v2f	delta_dist_calc(t_data *data, t_v2f *ray);
void	render(t_data *data);

/* Render_2 */
bool	side_assignment(t_data *data, t_v2f delta_dist);
void	side_calc(t_data *data, t_v2f ray, t_v2f delta_dist);
void	next_cube(t_data *data, t_v2f ray, int x, t_v2f delta_dist);
void	unleek_gnl(int fd);

char	*ft_strndup(char *s, int size);
bool	dup_next_world(char *str, char **dest);
void	jump_word(char **str);

int		mouse_handler(int x, int y, t_data *data);
void	rotate(t_v2f *v2f, float angle);
void	move_mouse(t_data *data);

int		enter_win(t_data *data);
int		leave_win(t_data *data);

// door
void	open_doors(t_data *data);
bool	can_i_close_the_door(t_data *data, int x, int y);
void	close_doors(t_data *data);
int	data_clear_le_2(t_data *data);

#endif
