/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:36:08 by analexan          #+#    #+#             */
/*   Updated: 2023/09/26 22:02:26 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// initiate the mlx, window, images and map
void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"So long");
	create_image("./textures/xpm/tile/tile001.xpm", &game->i.wall, game);
	game->exit_count = 143 + rand() % 4;
	snprintf(game->exit_filename, 50, "./textures/xpm/tile/tile%d.xpm",
		game->exit_count);
	create_image(game->exit_filename, &game->i.exit, game);
	create_image("./textures/xpm/tile/tile016.xpm", &game->i.danger, game);
	create_image("./textures/xpm/walk/walk01.xpm", &game->i.down, game);
	create_image("./textures/xpm/walk/walk02.xpm", &game->i.up, game);
	create_image("./textures/xpm/walk/walk03.xpm", &game->i.left, game);
	create_image("./textures/xpm/walk/walk04.xpm", &game->i.right, game);
	create_image("./textures/xpm/walk/walk05.xpm", &game->i.down_r, game);
	create_image("./textures/xpm/walk/walk06.xpm", &game->i.up_r, game);
	create_image("./textures/xpm/walk/walk07.xpm", &game->i.left_r, game);
	create_image("./textures/xpm/walk/walk08.xpm", &game->i.right_r, game);
	create_image("./textures/xpm/walk/walk09.xpm", &game->i.down_l, game);
	create_image("./textures/xpm/walk/walk10.xpm", &game->i.up_l, game);
	create_image("./textures/xpm/walk/walk11.xpm", &game->i.left_l, game);
	create_image("./textures/xpm/walk/walk12.xpm", &game->i.right_l, game);
	create_image("./textures/xpm/food/food1.xpm", &game->i.collec, game);
	draw_map(game->map, game);
	create_image("./textures/xpm/floor/floor227.xpm", &game->i.ground, game);
	mlx_do_key_autorepeaton(game->mlx);
}

// check if player hit a wall, collectibles, danger and if
// hit the last collectible, change the exit texture
void	exec_interactions(int t1, int t2, t_game *game)
{
	if (game->map[game->y_pl][game->x_pl] == '1')
	{
		game->x_pl = t1;
		game->y_pl = t2;
		game->moves--;
	}
	else if (game->map[game->y_pl][game->x_pl] == 'C')
	{
		game->map[game->y_pl][game->x_pl] = '0';
		game->curr_collec--;
		if (!game->curr_collec)
		{
			game->exit_count -= 8;
			snprintf(game->exit_filename, 50,
				"./textures/xpm/tile/tile%d.xpm", game->exit_count);
			mlx_destroy_image(game->mlx, game->i.exit.img);
			game->i.exit.img = mlx_xpm_file_to_image(game->mlx,
					game->exit_filename, &game->i.exit.width,
					&game->i.exit.height);
			draw_food_or_exit(-1, -1, game);
		}
	}
	else if (game->map[game->y_pl][game->x_pl] == 'D' ||
			(game->map[game->y_pl][game->x_pl] == 'E' && !game->curr_collec))
		quit(game);
}

// this is called every time the player moves and
// only updates the next, previous tile and moves
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

void	create_image(char *path, t_image *image, t_game *game)
{
	image->img = mlx_xpm_file_to_image(game->mlx,
			path, &image->width, &image->height);
}

void	image_to_window(t_image image, int x, int y, t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, image.img, x, y);
}
