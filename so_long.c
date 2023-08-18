/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/08/18 19:04:13 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		prt("Negative value for pixel, giving it value 0\n");
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_line(t_data *image, int x1, int y1, int x2, int y2, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (x1 + i < x2 || y1 + j < y2)
	{
		my_mlx_pixel_put(image, x1 + i, y1 + j, color);
		if (x1 + i < x2)
			i++;
		if (y1 + j < y2)
			j++;
	}
	my_mlx_pixel_put(image, x2, y2, color);
}

void	put_square(t_data *image, int x1, int y1, int x2, int y2, int just_perimeter, int color)
{
	if (just_perimeter)
	{
		put_line(image, x1, y1, x1, y2, color);
		put_line(image, x1, y1, x2, y1, color);
		put_line(image, x2, y1, x2, y2, color);
		put_line(image, x1, y2, x2, y2, color);
	}
	else
	{
		int i = 0;
		while (y1 + i <= y2)
		{
			put_line(image, x1, y1 + i, x2, y1 + i, color);
			i++;
		}
	}
}
/*
x = ---->
y =
|
|
\/
*/
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	image;
	int		red;
	int		green;
	int		blue;

	red = 0x00FF0000;
	green = 0x0000FF00;
	blue = 0x000000FF;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	image.img = mlx_new_image(mlx, 500, 500);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	put_square(&image, 0, 0, 100, 100, 1, red);
	put_square(&image, 0, 100+1, 100, 200+1, 1, green);
	put_square(&image, 100+1, 0, 200+1, 100, 1, blue);
	mlx_put_image_to_window(mlx, mlx_win, image.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
