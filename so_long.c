/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/08/22 20:10:38 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		prt("Warning -x | -y, x: %i, y: %i\n", x, y);
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

int	put_grad_line(t_data *image, int x1, int y1, int x2, int y2)
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
	return (argb(0, r, g, b));
}

void	put_grad_square(t_data *image, int x1, int y1, int x2, int y2, int just_perimeter)
{
	if (just_perimeter)
	{
		put_grad_line(image, x1, y1, x1, y2);
		put_grad_line(image, x1, y1, x2, y1);
		put_grad_line(image, x1, y2, x2, y2);
		put_grad_line(image, x2, y1, x2, y2);
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

int	quit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->p_image.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
		return (quit(vars));
	if (keycode == UP_KEY || keycode == W_KEY)
		(*vars).y -= 10;
	else if (keycode == LEFT_KEY || keycode == A_KEY)
		(*vars).x -= 10;
	else if (keycode == RIGHT_KEY || keycode == D_KEY)
		(*vars).x += 10;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		(*vars).y += 10;
	if (keycode < 32 || keycode > 126)
		prt("keycode: %i = Invalid char\n", keycode);
	else
		prt("keycode: %i = '%c'\n", keycode, keycode);
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

int	mouse_hook(int x, int y, int keycode, t_vars *vars)
{
	prt("x: %i, y: %i, keycode: %i\n", x, y, keycode);
	prt("x %i y %i\n", (*vars).x, (*vars).y);
	(*vars).r = 0;
	// vars->y = y;
	prt("\033[1;31mpassedpadpassedpasassed\n");
	return (0);
}
// acessing the struct's variables is illegal and gives seg fault?

// by chatgpt
void put_circle(t_data *image, int xc, int yc, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        my_mlx_pixel_put(image, xc + x, yc + y, color);
        my_mlx_pixel_put(image, xc + y, yc + x, color);
        my_mlx_pixel_put(image, xc - y, yc + x, color);
        my_mlx_pixel_put(image, xc - x, yc + y, color);
        my_mlx_pixel_put(image, xc - x, yc - y, color);
        my_mlx_pixel_put(image, xc - y, yc - x, color);
        my_mlx_pixel_put(image, xc + y, yc - x, color);
        my_mlx_pixel_put(image, xc + x, yc - y, color);
        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

// by chatgpt
void put_filled_circle(t_data *image, int xc, int yc, int radius, int color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        int i;
        for (i = xc - x; i <= xc + x; i++) {
            my_mlx_pixel_put(image, i, yc + y, color);
            my_mlx_pixel_put(image, i, yc - y, color);
        }
        for (i = xc - y; i <= xc + y; i++) {
            my_mlx_pixel_put(image, i, yc + x, color);
            my_mlx_pixel_put(image, i, yc - x, color);
        }
        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

int	power(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->p_image.img);
	// put_square(&vars->p_image, 0, 0, win_length, win_width, 0, argb(0, (*vars).r, (*vars).g, (*vars).b));
	// mlx_put_image_to_window((*vars).mlx, (*vars).win, vars->p_image.img, 0, 0);
	usleep(1000 * 3);
	// if ((*vars).r == 255 && (*vars).g < 255 && (*vars).b == 0)
	// 	(*vars).g++;
	// else if ((*vars).g == 255 && (*vars).r > 0)
	// 	(*vars).r--;
	// else if ((*vars).g == 255 && (*vars).b < 255)
	// 	(*vars).b++;
	// else if ((*vars).b == 255 && (*vars).g > 0)
	// 	(*vars).g--;
	// else if ((*vars).b == 255 && (*vars).r < 255)
	// 	(*vars).r++;
	// else if ((*vars).r == 255 && (*vars).b > 0)
	// 	(*vars).b--;
	vars->p_image.img = mlx_xpm_file_to_image(vars->mlx, "./cursor.xpm", &vars->p_image.width, &vars->p_image.height);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->p_image.img, 0, 0);
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->p_image.img, (*vars).x - 64, (*vars).y - 64);
	
	// put_filled_circle(&vars->p_image, (*vars).x, (*vars).y, 30, 0);
	// put_square((*vars).img, (*vars).x - 5, (*vars).y - 5, (*vars).x + 5, (*vars).y + 5, 0, 0);
	// prt("x: %i, y: %i, keycode: %i\n", x, y, keycode);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, win_length, win_width, "So long window");
	// vars.p_image.img = mlx_new_image(vars.mlx, win_length, win_width);
	// vars.p_image.addr = mlx_get_data_addr(vars.p_image.img, &vars.p_image.bits_per_pixel,
	// 		&vars.p_image.line_length, &vars.p_image.endian);
	vars.r = 255;
	vars.b = 0;
	vars.g = 0;
	vars.x = win_length / 2;
	vars.y = win_width / 2;
	// put_grad_square(&vars.p_image, 5, 0, win_length - 5, 50, 0);
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.p_image.img, 0, 0);
	// mlx_hook(vars.win, 2, 1L<<0, close_all, &vars);
	mlx_hook(vars.win, 17, 0, quit, &vars);
	vars.p_image.img = mlx_xpm_file_to_image(vars.mlx, "./cursor.xpm", &vars.p_image.width, &vars.p_image.height);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.p_image.img, 0, 0);
	// mlx_hook(vars.win, 6, 1L<<6, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, power, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
/*
x = ---->
y =
|
|
\/
	// 0x00FF0000 = argb(0, 255, 0, 0)
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
	// mlx_hook(vars.win, 7, 1L<<4, in, &vars);
	// mlx_hook(vars.win, 8, 1L<<5, out, &vars);
	// mlx_hook(vars.win, 6, 1L<<6, mouse_hook, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);

*/