/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/23 17:55:07 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <mlx.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define UP_KEY 65362
# define LEFT_KEY 65361
# define DOWN_KEY 65364
# define RIGHT_KEY 65363
# define ESC_KEY 65307

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_image;

typedef struct s_imgs
{
	t_image	wall;
	t_image	ground;
	t_image	collec;
	t_image	exit;
	t_image	danger;
	t_image	down;
	t_image	up;
	t_image	left;
	t_image	right;
	t_image	down_r;
	t_image	up_r;
	t_image	left_r;
	t_image	right_r;
	t_image	down_l;
	t_image	up_l;
	t_image	left_l;
	t_image	right_l;
}			t_imgs;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_imgs	i;
	int		win_width;
	int		win_height;
	int		map_width;
	int		map_height;
	int		tile_width;
	int		tile_height;
	char	**map;
	char	**temp_map;
	int		is_left_leg_to_animate;
	int		keycode;
	int		current_frame;
	int		frame_of_release;
	int		curr_collec;
	int		total_collectibles;
	int		exit_count;
	char	exit_filename[50];
	int		moves;
	int		x_pl;
	int		y_pl;
}			t_game;

// game_init
void	game_init(t_game *game);

// check_map
char	*check_map_name_and_length(char *str, int fd, t_game *game);
void	check_map_walls_and_create_array(char *str, int fd, t_game *game);
void	check_if_valid_map(t_game *game, int is_player);
void	copy_map_to_temp(t_game *game);
void	flood_fill(int x, int y, t_game *game);

// draw_map
void	draw_player(int keycode, int walking, t_game *game);
void	draw_food_or_exit(int x, int y, t_game *game);
void	draw_map(char **map, t_game *game);

// game_func
void	exec_interactions(int t1, int t2, t_game *game);
void	update_map(int x, int y, t_game *game);
int		rng(int min, int max);
void	create_image(char *path, t_image *image, t_game *game);
void	image_to_window(t_image image, int x, int y, t_game *game);

// quit_game
int		restart(t_game *game);
void	print_error(int error);
int		quit(t_game *game);
void	free_map(int len, t_game *game);

// tool_lib
void	prt(char *string, ...);
int		ft_strspn(const char *str, const char *accept);
int		ft_strcmp(char *s1, char *s2);

// get_next_line
int		ft_strlen(char *s, int mode);
char	*get_next_line(int fd);

#endif