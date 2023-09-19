/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/19 19:29:40 by analexan         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
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

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_image	wall_i;
	t_image	ground_i;
	t_image	collec_i;
	t_image	exit_i;
	t_image	danger_i;
	t_image	player_i;
	t_image	up_i;
	t_image	left_i;
	t_image	right_i;
	t_image	aplayer_i;
	t_image	aup_i;
	t_image	aleft_i;
	t_image	aright_i;
	t_image	aaplayer_i;
	t_image	aaup_i;
	t_image	aaleft_i;
	t_image	aaright_i;
	int		win_width;
	int		win_height;
	int		map_width;
	int		map_height;
	int		tile_width;
	int		tile_height;
	char	**map;
	char	**temp_map;
	int		curr_animation;
	int		is_pressed;
	int		keycode;
	int		temp;
	int		start;
	int		collectibles;
	int		exit_count;
	int		moves;
	int		x_pl;
	int		y_pl;
}			t_game;

typedef struct s_food
{
	t_image food01;
	t_image food02;
}			t_food;

// so_long
void	p(int x, int y);
void	error_handling(int error);

// check_map
char	*check_map_name_and_length(char *str, int fd, t_game *heh);
void	check_map_walls_and_create_array(char *str, int fd, t_game *heh);
void	check_if_valid_map(t_game *heh, int is_player);
void	copy_map_to_temp(t_game *heh);
void	flood_fill(int x, int y, t_game *heh);

// game_ctrl
int		quit(t_game *heh);
void	free_map(int len, t_game *heh);
void	exec_interactions(int t1, int t2, t_game *heh);
void	error_handling(int error);

// func_lib
char	*ft_itoa(int n);
int		ft_strspn(const char *str, const char *accept);
int		ft_strcmp(char *s1, char *s2);

// func_lib2
int rng(int min, int max);

// tool_lib
long	stol(char *str);
int		stoi(char *str);
void	prt(char *string, ...);

// get_next_line
int		ft_strlen(char *s, int mode);
char	*get_next_line(int fd);

#endif