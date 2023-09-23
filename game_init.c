/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:06:36 by andrealex         #+#    #+#             */
/*   Updated: 2023/09/23 17:11:10 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_walking_images(t_game *game)
{
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
}

// initiate the mlx, window, images and map
void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"So long");
	create_image("./textures/xpm/tile/tile001.xpm", &game->i.wall, game);
	game->exit_count = rng(143, 146);
	snprintf(game->exit_filename, 50, "./textures/xpm/tile/tile%d.xpm",
		game->exit_count);
	create_image(game->exit_filename, &game->i.exit, game);
	create_image("./textures/xpm/tile/tile016.xpm", &game->i.danger, game);
	create_walking_images(game);
	copy_map_to_temp(game);
	draw_map(game->map, game);
	create_image("./textures/xpm/floor/floor227.xpm", &game->i.ground, game);
	mlx_do_key_autorepeaton(game->mlx);
}
