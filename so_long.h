/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/08/22 20:09:00 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define reset put_square(&image, 0, 0, length, width, 0, 0);

# ifndef win_length
#  define win_length 900
# endif
# ifndef win_width
#  define win_width 900
# endif

#define W_KEY      119
#define A_KEY       97
#define S_KEY      115
#define D_KEY      100
#define UP_KEY   65362
#define LEFT_KEY 65361
#define DOWN_KEY 65364
#define RIGHT_KEY 65363
#define ESC_KEY 65307

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	p_image;
	int		r;
	int		g;
	int		b;
	int		x;
	int		y;
	int		width;
	int		height;
}			t_vars;

// so_long


// tool_lib
long		stol(char *str);
int			stoi(char *str);
void		prt(char *string, ...);

#endif