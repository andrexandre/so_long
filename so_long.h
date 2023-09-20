/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/20 19:46:42 by analexan         ###   ########.fr       */
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
	int		is_created;
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
	t_image	adown;
	t_image	aup;
	t_image	aleft;
	t_image	aright;
	t_image	aadown;
	t_image	aaup;
	t_image	aaleft;
	t_image	aaright;
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
	int		curr_animation;
	int		keycode;
	int		current_frame;
	int		frame_of_release;
	int		collectibles;
	int		total_collectibles;
	int		exit_count;
	char	exit_filename[25];
	int		moves;
	int		x_pl;
	int		y_pl;
}			t_game;

// check_map
char	*check_map_name_and_length(char *str, int fd, t_game *game);
void	check_map_walls_and_create_array(char *str, int fd, t_game *game);
void	check_if_valid_map(t_game *game, int is_player);
void	copy_map_to_temp(t_game *game);
void	flood_fill(int x, int y, t_game *game);

// draw_map
void	draw_player_animation(int keycode, int x, int y, t_game *game);
void	draw_player(int keycode, int mode, t_game *game);
void	draw_food_or_exit(int x, int y, t_game *game);
void	draw_map(char **map, t_game *game);
void	update_map(int x, int y, t_game *game);

// game_func
int		check_map(char *str, t_game *game);
int		restart(t_game *game);
void	exec_interactions(int t1, int t2, t_game *game);
void	create_image(char *path, t_image *image, t_game *game);
void	image_to_window(t_image image, int x, int y, t_game *game);

// quit_game
void	error_handling(int error);
int		quit(t_game *game);
void	free_map(int len, t_game *game);

// func_lib
int		rng(int min, int max);
int		ft_strspn(const char *str, const char *accept);
int		ft_strcmp(char *s1, char *s2);
void	wwrite(int q, const void *w, size_t e);

// tool_lib
long	stol(char *str);
int		stoi(char *str);
void	prt(char *string, ...);

// get_next_line
int		ft_strlen(char *s, int mode);
char	*get_next_line(int fd);

#endif