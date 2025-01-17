/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:41:52 by pcheron           #+#    #+#             */
/*   Updated: 2024/02/11 10:21:00 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ************************************************************************** //
//  INCLUDES
// ************************************************************************** //

# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"
# include <errno.h>

// ************************************************************************** //
//  DEFINES
// ************************************************************************** //

// Parsing Macros
# define ERROR "😭 Boo-hoo 😭\nInvalid map format"

// Movement Macros
# define MOVE_SPEED		0.011
# define ROT_SPEED		0.004
# define PI				3.14

// Window Macros
# define IMG_WIDTH		960
# define IMG_HEIGHT		640
# define TEX_WIDTH		128
# define TEX_HEIGHT		128
# define MINIMAP_WIDTH	20
# define MINIMAP_HEIGHT 20
# define TILE_SIZE		8

// Keys Macros
# define UP				65362
# define DOWN			65364
# define RIGHT			65363
# define LEFT			65361
# define UP_W			119
# define DOWN_S			115
# define RIGHT_D		100
# define LEFT_A			97
# define O_DOOR			111
# define EXIT			17
# define KEY_ESC		65307

// Dialog Images
# define ALICE_D_1	"img/XPM/Dialog/ALICE_1.xpm"
# define ALICE_D_2	"img/XPM/Dialog/ALICE_2.xpm"
# define ALICE_D_3	"img/XPM/Dialog/ALICE_3.xpm"
# define ALICE_D_4	"img/XPM/Dialog/ALICE_4.xpm"
# define ALICE_D_5	"img/XPM/Dialog/ALICE_4.xpm"
# define ALICE_D_6	"img/XPM/Dialog/ALICE_4.xpm"
# define ALICE_D_7	"img/XPM/Dialog/ALICE_4.xpm"
# define RABBIT_D_1	"img/XPM/Dialog/RABBIT_1.xpm"
# define RABBIT_D_2	"img/XPM/Dialog/RABBIT_2.xpm"
# define RABBIT_D_3	"img/XPM/Dialog/RABBIT_3.xpm"
# define CAT_D_1	"img/XPM/Dialog/CAT_1.xpm"
# define CAT_D_2	"img/XPM/Dialog/CAT_2.xpm"
# define CAT_D_3	"img/XPM/Dialog/CAT_3.xpm"
# define DIALOG_BOX	"./img/XPM/Dialog_box.xpm"

// Door Images
# define DOOR_RABBIT_1	"./img/XPM/WHITE_RABBIT_DOOR.xpm"
# define DOOR_RABBIT_2	"./img/XPM/WHITE_RABBIT_DOOR_2.xpm"
# define DOOR_1			"./img/XPM/Walls/DOOR.xpm"

// Game Macros
# define DOOR_OPENED	'O'
# define DOOR_CLOSED	'D'
# define COLLECTIBLE	'C'
# define CHESHIRE_CAT	'P'

// Dialog state
enum e_dialog
{
	DIALOG_NOT_STARTED = 0,
	ALICE_1,
	ALICE_2,
	ALICE_3,
	ALICE_4,
	WHITE_RABBIT_1,
	WHITE_RABBIT_2,
	WHITE_RABBIT_3,
	DIALOG_FINISH_1,
	ALICE_5,
	ALICE_6,
	ALICE_7,
	CHESHIRE_CAT_1,
	CHESHIRE_CAT_2,
	CHESHIRE_CAT_3,
	DIALOG_FINISH_2,
};

enum e_parse
{
	DOOR = 0,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR_2,
	FLOOR,
	CEILING,
	OUT,
	PLAYER,
	MAP,
};

// ************************************************************************** //
//  STRUCTURES
// ************************************************************************** //

typedef float	t_color	__attribute__((vector_size (16)));
typedef float	t_v2f	__attribute__((vector_size (8)));

typedef struct s_coll
{
	struct s_coll	*next;
	t_v2f			pos;
	bool			type;
}	t_coll;

typedef struct s_col_u
{
	int		sprite_screen;
	int		s_wdth;
	int		s_hgt;
	int		draw_start_y;
	int		draw_end_y;
	t_v2f	trans;

}	t_col_u;

typedef struct s_img_info
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		width;
	int		height;
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
	bool		door;
}	t_control;

typedef struct s_data
{
	void			*win;
	void			*mlx;
	t_img_info		img;

	int				fd;
	int				nb_side_parsed;

	t_img_info		north;
	t_img_info		south;
	t_img_info		west;
	t_img_info		east;
	t_img_info		floor;
	t_img_info		ceiling;

	t_color			floor_color;
	int				floor_color_2;
	t_color			ceiling_color;
	int				ceiling_color_2;
	int				img_width;
	int				img_height;
	char			**map;
	int				width;
	int				height;
	t_control		controls;
	t_v2f			plane;
	t_v2f			player_pos;
	t_v2f			camera_dir;
	float			tex_pos;
	float			tex_pos_tmp;
	float			step_all;
	int				tex_x;
	int				side;
	int				map_x;
	int				map_y;
	int				it_x;
	int				it_y;
	t_v2f			step;
	t_v2f			side_dist;
	void			*minimap;
	int				dir;
	bool			in_win;
	int				time;
	long			time_2_le_retour;
	int				draw_start;
	int				draw_end;

	t_img_info		door;
	t_img_info		mushroom;
	t_img_info		dialog_box;
	t_img_info		alice[18];
	t_img_info		white_rabbit[10];
	t_img_info		white_rabbit_door[2];
	t_img_info		catterpilar[17];
	t_img_info		wall_cat[6];
	t_img_info		dialog_cat[6];
	t_img_info		dialog[15];
	int				dialog_stage;
	bool			display_catterpilar;
	bool			display_door;
	t_coll			*coll;
	t_col_u			col_u;
	bool			drug;
	int				drug_timer;
	float			zbuffer[IMG_WIDTH];
	int				cat_timer;

}	t_data;

// ************************************************************************** //
//  PROTOTYPES
// ************************************************************************** //

//		setup
void	make_data_null(t_data *data);

//		fill world
bool	fill_north(t_data *data, char *line);
bool	fill_south(t_data *data, char *line);
bool	fill_west(t_data *data, char *line);
bool	fill_east(t_data *data, char *line);
bool	fill_ceiling(t_data *data, char *line);
bool	fill_floor(t_data *data, char *line);
bool	fill_new_line(t_data *data, char **line);
bool	fill_map(t_data *data, char **line);
bool	fill_map_file(t_data *data, char *map);
bool	setup_mlx(t_data *data);

//		parse utils
bool	is_a_white_space(char c);
void	unleek_gnl(int fd);
void	jump_word(char **str);
char	*ft_strndup(char *s, int size);
bool	dup_next_world(char *str, char **dest);
void	jump_int(char **str);
bool	is_alpha(char c);
bool	atocolor(char *str, t_color *color);
int		count_char_in_str(char c, char *str);

//		render
void	wall_calc(t_data *data, t_v2f ray, float perp_wall_dist);
t_v2f	delta_dist_calc(t_data *data, t_v2f *ray);
void	render(t_data *data);

//		draw
void	ft_my_put_pixel(t_data *data, int x, int y, int color);
void	draw_slice(t_data *data, int x);

//		move
void	move_longitudinal(t_data *data);
void	move_sideways(t_data *data);
void	rotate(t_data *data, float angle, t_v2f old_dir);
int		update_display(t_data *data);

//		key / mous handling
int		key_event(int keycode, t_data *data);
int		key_release(int key, t_data *data);
int		enter_win(t_data *data);
int		leave_win(t_data *data);
int		mouse_handler(int x, int y, t_data *data);

//		cleaning
int		data_clear(t_data *data);
void	free_strs(char ***strs);

//		cleaning_utils
void	err(char *s);
int		quit_game(t_data *data);

//		checkup map
int		count_char_in_map(char c, char **map);
bool	is_char_in_map_are_normal(char **map);
bool	is_char_valid_in_map(char c);
bool	is_a_zero_next_to_wrong(char **map);
void	setup_dir(t_data *data, int x, int y);
bool	checkup_map(char **map);
// void	side_calc(t_data *data, t_v2f ray, t_v2f delta_dist);

//
bool	setup_game(t_data *data);

//		coll utils
void	coll_clear(t_coll **coll);
void	coll_add_back(t_coll **coll, t_coll *new);
void	coll_delete(t_coll **coll, t_v2f pos);
t_coll	*coll_new(t_v2f pos, bool type);
t_coll	*coll_last(t_coll *coll);

#endif
