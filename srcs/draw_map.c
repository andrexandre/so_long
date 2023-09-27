/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:56 by analexan          #+#    #+#             */
/*   Updated: 2023/09/26 22:02:25 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	draw_player_animation(int keycode, int x, int y, t_game *game)
{
	if (!game->is_left_leg_to_animate)
	{
		if (keycode == UP_KEY || keycode == 'w')
			image_to_window(game->i.up_r, x, y, game);
		else if (keycode == LEFT_KEY || keycode == 'a')
			image_to_window(game->i.left_r, x, y, game);
		else if (keycode == RIGHT_KEY || keycode == 'd')
			image_to_window(game->i.right_r, x, y, game);
		else if (keycode == DOWN_KEY || keycode == 's')
			image_to_window(game->i.down_r, x, y, game);
		game->is_left_leg_to_animate = 1;
	}
	else if (game->is_left_leg_to_animate)
	{
		if (keycode == UP_KEY || keycode == 'w')
			image_to_window(game->i.up_l, x, y, game);
		else if (keycode == LEFT_KEY || keycode == 'a')
			image_to_window(game->i.left_l, x, y, game);
		else if (keycode == RIGHT_KEY || keycode == 'd')
			image_to_window(game->i.right_l, x, y, game);
		else if (keycode == DOWN_KEY || keycode == 's')
			image_to_window(game->i.down_l, x, y, game);
		game->is_left_leg_to_animate = 0;
	}
}

void	draw_player(int keycode, int walking, t_game *game)
{
	int	x;
	int	y;

	x = game->x_pl * game->tile_width;
	y = game->y_pl * game->tile_width;
	if (!walking)
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
	char	filename[50];

	if (x < 0 || y < 0)
	{
		y = -1;
		while (++y < game->map_height)
		{
			x = -1;
			while (++x < game->map_width)
				if (game->map[y][x] == 'E')
					mlx_put_image_to_window(game->mlx, game->win,
						game->i.exit.img, x * game->tile_width, y
						* game->tile_height);
		}
	}
	else
	{
		mlx_destroy_image(game->mlx, game->i.collec.img);
		snprintf(filename, sizeof(filename),
			"./textures/xpm/food/food%d.xpm", 1 + rand() % 64);
		create_image(filename, &game->i.collec, game);
		image_to_window(game->i.collec, x, y, game);
	}
}

void	draw_ground(int x, int y, t_game *game)
{
	char	filename[50];

	if (rand() % 3)
		snprintf(filename, sizeof(filename),
			"./textures/xpm/floor/floor%d.xpm", 227 + rand() % 5);
	else
		snprintf(filename, sizeof(filename),
			"./textures/xpm/floor/floor227.xpm");
	create_image(filename, &game->i.ground, game);
	image_to_window(game->i.ground, x, y, game);
	mlx_destroy_image(game->mlx, game->i.ground.img);
}

// this is called 1 time when the game initiates and restarts
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
				draw_ground(x, y, game);
			x += game->tile_width;
		}
		y += game->tile_height;
	}
	draw_player(0, 0, game);
	mlx_string_put(game->mlx, game->win, 5, 20, 0x00FFFFFF, "0");
}
