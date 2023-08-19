/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/08/19 19:13:55 by analexan         ###   ########.fr       */
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

int		argb(double a, int r, int g, int b)
{
	a = 1 - a;
	r *= a;
	g *= a;
	b *= a;
	return (r << 16 | g << 8 | b);
	// return (a << 24 | r << 16 | g << 8 | b); // doesn't work :(
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

void	put_grad_line(t_data *image, int x1, int y1, int x2, int y2)
{
	int	i;
	int	j;
	int r = 255;
	int g = 0;
	int b = 0;

	i = 0;
	j = 0;
	while (x1 + i < x2 || y1 + j < y2)
	{
		my_mlx_pixel_put(image, x1 + i, y1 + j, argb(0, r, g, b));
		if (r == 255 && g < 255 && b == 0)
			g++;
		else if (g == 255 && r > 0)
			r--;
		else if (g == 255 && b < 255)
			b++;
		else if (b == 255 && g > 0)
			g--;
		else if (b == 255 && r < 255)
			r++;
		else if (r == 255 && b > 0)
			b--;
		if (x1 + i < x2)
			i++;
		if (y1 + j < y2)
			j++;
	}
	my_mlx_pixel_put(image, x2, y2, argb(0, i, j, 0));
}

void	put_grad_square(t_data *image, int x1, int y1, int x2, int y2, int just_perimeter)
{
	if (just_perimeter)
	{
		put_grad_line(image, x1, y1, x1, y2);
		put_grad_line(image, x1, y1, x2, y1);
		put_grad_line(image, x2, y1, x2, y2);
		put_grad_line(image, x1, y2, x2, y2);
	}
	else
	{
		int i = 0;
		while (y1 + i <= y2)
		{
			put_grad_line(image, x1, y1 + i, x2, y1 + i);
			i++;
		}
	}
}

int		get_opposite(int color)
{
	return(~color);
}

int	close(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);		
	}
	if (keycode < 32 || keycode > 126)
		prt("keycode: %i = Invalid char\n", keycode);
	else
		prt("keycode: %i = '%c'\n", keycode, keycode);
	return (0);
}

int	dest(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	return (0);
}

int	in(t_vars *vars)
{
	prt("Hello!\n");
	(void)vars;
	return (0);
}

int	out(t_vars *vars)
{
	prt("Bye!\n");
	(void)vars;
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode < 32 || keycode > 126)
		prt("keycode: %i = Invalid char\n", keycode);
	else
		prt("keycode: %i = '%c'\n", keycode, keycode);
	(void)vars;
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	prt("keycode: %i, x: %i, y: %i\n", keycode, x, y);
	(void)vars;
	return (0);
}

int	main(void)
{
	t_vars	vars;
	// t_data	image;
	int		red;
	int		green;
	int		blue;

	red = 0x00FF0000;
	green = 0x0000FF00;
	blue = 0x000000FF;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, length, width, "So long window");
	// image.img = mlx_new_image(vars.mlx, length, width);
	// image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
	// 		&image.line_length, &image.endian);
	// put_grad_square(&image, 5, 5, 900, 50, 1);
	// put_square(&image, 5, 5, 500, 500, 0, green);
	// mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	// mlx_hook(vars.win, 17, 1L<<0, dest, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_hook(vars.win, 7, 1L<<4, in, &vars);
	// mlx_hook(vars.win, 8, 1L<<5, out, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
/*
x = ---->
y =
|
|
\/
	int millisecond = 1000 * 3;
	int r = 255;
	int g = 0;
	int b = 0;
	put_grad_square(&image, 5, 5, 1000, 50, 1);
	while (1)
	{
		put_square(&image, 0, 0, 300, 300, 0, argb(0, r, g, b));
		mlx_put_image_to_window(mlx, mlx_win, image.img, 0, 0);
		usleep(millisecond);
		if (r == 255 && g < 255 && b == 0)
			g++;
		else if (g == 255 && r > 0)
			r--;
		else if (g == 255 && b < 255)
			b++;
		else if (b == 255 && g > 0)
			g--;
		else if (b == 255 && r < 255)
			r++;
		else if (r == 255 && b > 0)
			b--;
	}
*/