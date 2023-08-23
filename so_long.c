/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/08/23 19:24:18 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// 💀 lines to skip * line_size + pixels to skip * bits_per_pixel
void	my_mlx_pixel_put(t_data *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		prt("Neg. value, x: %i, y: %i\n", x, y);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	// if (x >= 0 && y >= 0 && x < image->width && y < image->height)
	// {
	// }
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

int	quit(t_vars *heh)
{
	if (heh->p_image.img)
		mlx_destroy_image(heh->mlx, heh->p_image.img);
	if (heh)
		mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free(heh->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_vars *heh)
{
	if (keycode == ESC_KEY)
		return (quit(heh));
	if (keycode == UP_KEY || keycode == W_KEY)
		(*heh).y -= 10;
	else if (keycode == LEFT_KEY || keycode == A_KEY)
		(*heh).x -= 10;
	else if (keycode == RIGHT_KEY || keycode == D_KEY)
		(*heh).x += 10;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		(*heh).y += 10;
	if (keycode < 32 || keycode > 126)
		prt("keycode: %i = Invalid char\n", keycode);
	else
		prt("keycode: %i = '%c'\n", keycode, keycode);
	return (0);
}

int	mouse_click_hook(int x, int y, int keycode, t_vars *heh)
{
	prt("x: %i, y: %i, keycode: %i\n", x, y, keycode);
	usleep(1000 * 10);
	// heh->x = x;
	// heh->y = y;
	// acessing the struct's variables is illegal and gives seg fault?
	(void)heh;
	// prt("\033[1;31mPassed\n");
	return (0);
}

// by AI
void put_circle(t_data *image, int xc, int yc, int radius, int just_perimeter, int color)
{
	int x = radius;
	int y = 0;
	int err = 0;
	int i;

	while (x >= y)
	{
		if (just_perimeter)
		{
			my_mlx_pixel_put(image, xc + x, yc + y, color);
			my_mlx_pixel_put(image, xc + y, yc + x, color);
			my_mlx_pixel_put(image, xc - y, yc + x, color);
			my_mlx_pixel_put(image, xc - x, yc + y, color);
			my_mlx_pixel_put(image, xc - x, yc - y, color);
			my_mlx_pixel_put(image, xc - y, yc - x, color);
			my_mlx_pixel_put(image, xc + y, yc - x, color);
			my_mlx_pixel_put(image, xc + x, yc - y, color);
		}
		else
		{
			for (i = xc - x; i <= xc + x; i++)
			{
				my_mlx_pixel_put(image, i, yc + y, color);
				my_mlx_pixel_put(image, i, yc - y, color);
			}
			for (i = xc - y; i <= xc + y; i++)
			{
				my_mlx_pixel_put(image, i, yc + x, color);
				my_mlx_pixel_put(image, i, yc - x, color);
			}
		}
		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

int	rbgc(t_vars *heh)
{
	int millisecond = 1000;
	mlx_destroy_image(heh->mlx, heh->p_image.img);
	heh->p_image.img = mlx_new_image(heh->mlx, heh->win_width, heh->win_height);
	heh->p_image.addr = mlx_get_data_addr(heh->p_image.img, &heh->p_image.bits_per_pixel,
			&heh->p_image.line_length, &heh->p_image.endian);
	put_square(&heh->p_image, 0, 0, heh->win_width, heh->win_height, 0, argb(0, (*heh).r, (*heh).g, (*heh).b));
	mlx_put_image_to_window((*heh).mlx, (*heh).win, heh->p_image.img, 0, 0);
	if ((*heh).r == 255 && (*heh).g < 255 && (*heh).b == 0)
		(*heh).g++;
	else if ((*heh).g == 255 && (*heh).r > 0)
		(*heh).r--;
	else if ((*heh).g == 255 && (*heh).b < 255)
		(*heh).b++;
	else if ((*heh).b == 255 && (*heh).g > 0)
		(*heh).g--;
	else if ((*heh).b == 255 && (*heh).r < 255)
		(*heh).r++;
	else if ((*heh).r == 255 && (*heh).b > 0)
		(*heh).b--;
	put_circle(&heh->p_image, (*heh).x, (*heh).y, 30, 0, 0);
	usleep(millisecond * 10);
	return (0);
}

int	fti(t_vars *heh)
{
	int millisecond = 1000;
	mlx_destroy_image(heh->mlx, heh->p_image.img);
	heh->p_image.img = mlx_xpm_file_to_image(heh->mlx, ".xpm/tile.xpm", &heh->p_image.width, &heh->p_image.height);
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, (*heh).x - 64, (*heh).y - 64);
	usleep(millisecond * 100);
	return (0);
}

void p(int x, int y)
{
	prt("n1: %i, n2: %i\n", x, y);
}

void check_map_len(char *str)
{
	int fd = open(str, O_RDONLY);
	int i = 0;
	char *buffer;
	while ((buffer = get_next_line(fd)))
	{
		prt("%i:\"%s\"\n", i, buffer);
		free(buffer);
		i++;
	}
}

int	main(void)
{
	static t_vars	heh;
	heh.r = 255;
	heh.b = 0;
	heh.g = 0;
	heh.win_width = 900;
	heh.win_height = 900;
	// heh.win_width = tile_length * ft_strlen(buffer);

	heh.x = heh.win_width / 2;
	heh.y = heh.win_height / 2;
	heh.mlx = mlx_init();
	heh.win = mlx_new_window(heh.mlx, heh.win_width, heh.win_height, "So long window");
	
	// check_map_len("maps/test.ber");
	heh.p_image.img = mlx_new_image(heh.mlx, heh.win_width, heh.win_height);
	heh.p_image.addr = mlx_get_data_addr(heh.p_image.img, &heh.p_image.bits_per_pixel, &heh.p_image.line_length, &heh.p_image.endian);
	put_square(&heh.p_image, 0, 0, heh.win_width, heh.win_height, 0, argb(0, 0, 255, 0));
	// mlx_put_image_to_window(heh.mlx, heh.win, heh.p_image.img, 0, 0);
	// int y = 0, x = 0;
	// heh.p_image.img = mlx_xpm_file_to_image(heh.mlx, "./xpm/tile.xpm", &heh.p_image.width, &heh.p_image.height);
	// while (y < heh.win_width - heh.p_image.width)
	// {
	// 	while (x < heh.win_height - heh.p_image.width)
	// 	{
	// 		mlx_put_image_to_window(heh.mlx, heh.win, heh.p_image.img, x, y);
	// 		x += heh.p_image.width;
	// 	}
	// 	x = 0;
	// 	y += heh.p_image.height;
	// }
	// p(heh.p_image.width, heh.p_image.height);
	// seg fault with xpm

	mlx_loop_hook(heh.mlx, rbgc, &heh);
	// mlx_loop_hook(heh.mlx, fti, &heh);
	mlx_hook(heh.win, 2, 1L<<0, key_hook, &heh);
	mlx_hook(heh.win, 17, 0, quit, &heh);
	mlx_loop(heh.mlx);
	return (0);
}
/*
x Width, y length and y height
x Largura, y comprimento e y altura
	// put_grad_square(&heh.p_image, 5, 0, heh.win_width - 5, 50, 0);
	// mlx_string_put(heh.mlx, heh.win, 100, 500, argb(0, 255, 255, 255), "Howdy people!");
*/