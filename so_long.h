/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/08/19 16:25:55 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
// # include <unistd.h>
# define reset put_square(&image, 0, 0, length, width, 0, 0);

# ifndef length
#  define length 900
# endif
# ifndef width
#  define width 900
# endif

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

// so_long

// tool_lib
long		stol(char *str);
int			stoi(char *str);
void		prt(char *string, ...);

#endif