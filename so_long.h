/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/13 18:47:13 by analexan         ###   ########.fr       */
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

// # define TILE_WIDTH 56
// # define TILE_HEIGHT 60

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

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_image	p_image;
	int		win_width;
	int		win_height;
	int		tile_width;
	int		tile_height;
	int		map_width;
	int		map_height;
	char	**map;
	char	**temp;
	int		collectibles;
	int		exit;
	char	*path;
	int		r;
	int		g;
	int		b;
	int		x;
	int		y;
}			t_game;

// so_long


// tool_lib
long	stol(char *str);
int		stoi(char *str);
void	prt(char *string, ...);

// get_next_line
int		ft_strlen(char *s, int mode);
char	*get_next_line(int fd);

// trash
void	my_mlx_pixel_put(t_image *image, int x, int y, int color);
void	put_line(t_image *image, int x1, int y1, int x2, int y2, int color);
void	put_square(t_image *image, int x1, int y1, int x2, int y2, 
			int just_perimeter, int color);
int		argb(double a, int r, int g, int b);
void	put_circle(t_image *image, int xc, int yc, int radius, 
			int just_perimeter, int color);
void	p(int x, int y);
void	put_grad_square(t_image *image, int x1, int y1, int x2, int y2, 
			int just_perimeter);
void	rgbc_init(t_game *heh);
int		rbgc(t_game *heh);
void	fti_init(t_game *heh);
int		fti(t_game *heh);

#endif