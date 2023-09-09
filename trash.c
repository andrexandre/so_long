/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:07:58 by analexan          #+#    #+#             */
/*   Updated: 2023/08/28 11:37:02 by andrealex        ###   ########.fr       */
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

