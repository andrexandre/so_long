/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:07:58 by analexan          #+#    #+#             */
/*   Updated: 2023/09/13 18:47:34 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// if i want to use the prevention of putting pixel in illegal space
// and i didnt use the new image i have to set the image wid/hei myself
// lines to skip * line_size + pixels to skip * bits_per_pixel
void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < image->width && y < image->height)
	{
		dst = image->addr 
			+ (y * image->line_length + x * (image->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
		prt("Illegal value x: %i, y: %i\n", x, y);
}

void	put_line(t_image *image, int x1, int y1, int x2, int y2, int color)
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

	// return (a << 24 | r << 16 | g << 8 | b); // doesn't work :(
int	argb(double a, int r, int g, int b)
{
	a = 1 - a;
	r *= a;
	g *= a;
	b *= a;
	return (r << 16 | g << 8 | b);
}

void	put_square(t_image *image, int x1, int y1, int x2, int y2, 
		int just_perimeter, int color)
{
	int	i;

	if (just_perimeter)
	{
		put_line(image, x1, y1, x1, y2, color);
		put_line(image, x1, y1, x2, y1, color);
		put_line(image, x2, y1, x2, y2, color);
		put_line(image, x1, y2, x2, y2, color);
	}
	else
	{
		i = 0;
		while (y1 + i <= y2)
		{
			put_line(image, x1, y1 + i, x2, y1 + i, color);
			i++;
		}
	}
}

int	put_grad_line(t_image *image, int x1, int y1, int x2, int y2)
{
	int	i;
	int	j;
	int	r;
	int	g;
	int	b;

	r = 255;
	g = 0;
	b = 0;
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

void	put_grad_square(t_image *image, int x1, int y1, int x2, int y2, 
		int just_perimeter)
{
	int	i;

	if (just_perimeter)
	{
		put_grad_line(image, x1, y1, x1, y2);
		put_grad_line(image, x1, y1, x2, y1);
		put_grad_line(image, x1, y2, x2, y2);
		put_grad_line(image, x2, y1, x2, y2);
	}
	else
	{
		i = 0;
		while (y1 + i <= y2)
		{
			put_grad_line(image, x1, y1 + i, x2, y1 + i);
			i++;
		}
	}
}

// by AI
void	put_circle(t_image *image, int xc, int yc, int radius, 
		int just_perimeter, int color)
{
	int	x;
	int	y;
	int	err;
	int	i;

	x = radius;
	y = 0;
	err = 0;
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
			i = xc - x - 1;
			while (++i <= xc + x)
			{
				my_mlx_pixel_put(image, i, yc + y, color);
				my_mlx_pixel_put(image, i, yc - y, color);
			}
			i = xc - y - 1;
			while (++i <= xc + y)
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

void	rgbc_init(t_game *heh)
{
	heh->x = heh->win_width / 2;
	heh->y = heh->win_height / 2;
	heh->r = 255;
	heh->b = 0;
	heh->g = 0;
	heh->p_image.img = mlx_new_image(heh->mlx, heh->win_width, heh->win_height);
	heh->p_image.addr = mlx_get_data_addr(heh->p_image.img, 
			&heh->p_image.bits_per_pixel, &heh->p_image.line_length, 
			&heh->p_image.endian);
	heh->p_image.width = heh->win_width;
	heh->p_image.height = heh->win_height;
}

int	rbgc(t_game *heh)
{
	int	millisecond;

	millisecond = 1000;
	put_square(&heh->p_image, 0, 0, heh->win_width - 1, heh->win_height - 1, 0, 
		argb(0, heh->r, heh->g, heh->b));
	put_circle(&heh->p_image, heh->x, heh->y, 30, 0, 0);
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, 0, 0);
	if (heh->r == 255 && heh->g < 255 && heh->b == 0)
		heh->g++;
	else if (heh->g == 255 && heh->r > 0)
		heh->r--;
	else if (heh->g == 255 && heh->b < 255)
		heh->b++;
	else if (heh->b == 255 && heh->g > 0)
		heh->g--;
	else if (heh->b == 255 && heh->r < 255)
		heh->r++;
	else if (heh->r == 255 && heh->b > 0)
		heh->b--;
	usleep(millisecond * 10);
	return (0);
}

void	fti_init(t_game *heh)
{
	heh->x = heh->win_width / 2;
	heh->y = heh->win_height / 2;
	heh->p_image.img = mlx_xpm_file_to_image(heh->mlx, "./xpm/tile.xpm", 
			&heh->p_image.width, &heh->p_image.height);
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, 
		heh->x - 64, heh->y - 64);
}

int	fti(t_game *heh)
{
	int	millisecond;

	millisecond = 1000;
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, 
		heh->x - 64, heh->y - 64);
	usleep(millisecond * 10);
	return (0);
}

void	p(int x, int y)
{
	prt("\nn1: %i, n2: %i\n", x, y);
}
