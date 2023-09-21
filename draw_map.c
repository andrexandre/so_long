/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:56 by analexan          #+#    #+#             */
/*   Updated: 2023/09/21 14:22:49 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player_animation(int keycode, int x, int y, t_game *game)
{
	if (!game->curr_animation)
	{
		if (keycode == UP_KEY || keycode == 'w')
			image_to_window(game->i.aup, x, y, game);
		else if (keycode == LEFT_KEY || keycode == 'a')
			image_to_window(game->i.aleft, x, y, game);
		else if (keycode == RIGHT_KEY || keycode == 'd')
			image_to_window(game->i.aright, x, y, game);
		else if (keycode == DOWN_KEY || keycode == 's')
			image_to_window(game->i.adown, x, y, game);
		game->curr_animation = 1;
	}
	else if (game->curr_animation)
	{
		if (keycode == UP_KEY || keycode == 'w')
			image_to_window(game->i.aaup, x, y, game);
		else if (keycode == LEFT_KEY || keycode == 'a')
			image_to_window(game->i.aaleft, x, y, game);
		else if (keycode == RIGHT_KEY || keycode == 'd')
			image_to_window(game->i.aaright, x, y, game);
		else if (keycode == DOWN_KEY || keycode == 's')
			image_to_window(game->i.aadown, x, y, game);
		game->curr_animation = 0;
	}
}

void	draw_player(int keycode, int mode, t_game *game)
{
	int	x;
	int	y;

	x = game->x_pl * game->tile_width;
	y = game->y_pl * game->tile_width;
	if (!mode)
	{
		if (keycode == UP_KEY || keycode == 'w')
			image_to_window(game->i.up, x, y, game);
		else if (keycode == LEFT_KEY || keycode == 'a')
			image_to_window(game->i.left, x, y, game);
		else if (keycode == RIGHT_KEY || keycode == 'd')
			image_to_window(game->i.right, x, y, game);
		else if (keycode == DOWN_KEY || keycode == 's')
			image_to_window(game->i.down, x, y, game);
		else
			image_to_window(game->i.down, x, y, game);
	}
	else
		draw_player_animation(keycode, x, y, game);
}

void	draw_food_or_exit(int x, int y, t_game *game)
{
	char	filename[25];

	if (x < 0 || y < 0)
	{
		y = -1;
		while (++y < game->map_height)
		{
			x = -1;
			while (++x < game->map_width)
				if (game->map[y][x] == 'E')
					mlx_put_image_to_window(game->mlx, game->win,
						game->i.exit.img,
						x * game->tile_width, y * game->tile_height);
		}
	}
	else
	{
		snprintf(filename, sizeof(filename), "./xpm/food/food%d.xpm",
			rng(1, 64));
		create_image(filename, &game->i.collec, game);
		image_to_window(game->i.collec, x, y, game);
		mlx_destroy_image(game->mlx, game->i.collec.img);
	}
}

void	draw_map(char **map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->win_height - game->tile_height + 1)
	{
		x = 0;
		while (x < game->win_width - game->tile_width + 1)
		{
			if (map[y / game->tile_height][x / game->tile_width] == '1')
				image_to_window(game->i.wall, x, y, game);
			else if (map[y / game->tile_height][x / game->tile_width] == 'C')
				draw_food_or_exit(x, y, game);
			else if (map[y / game->tile_height][x / game->tile_width] == 'E')
				image_to_window(game->i.exit, x, y, game);
			else if (map[y / game->tile_height][x / game->tile_width] == 'D')
				image_to_window(game->i.danger, x, y, game);
			else
				image_to_window(game->i.ground, x, y, game);
			x += game->tile_width;
		}
		y += game->tile_height;
	}
	draw_player(0, 0, game);
	mlx_string_put(game->mlx, game->win, 5, 20, 0x00FFFFFF, "0");
}

void	update_map(int x, int y, t_game *game)
{
	char	str[5];

	image_to_window(game->i.wall, 0, 0, game);
	if (game->map[y][x] == 'E')
		image_to_window(game->i.exit,
			x * game->tile_width, y * game->tile_height, game);
	else if (game->map[y][x] == 'D')
		image_to_window(game->i.danger,
			x * game->tile_width, y * game->tile_height, game);
	else
		image_to_window(game->i.ground,
			x * game->tile_width, y * game->tile_height, game);
	draw_player(game->keycode, 0, game);
	snprintf(str, sizeof(str), "%d", ++game->moves);
	mlx_string_put(game->mlx, game->win, 6, 20, 0x00FFFFFF, str);
}
