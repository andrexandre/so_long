/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:25:58 by analexan          #+#    #+#             */
/*   Updated: 2023/09/23 17:59:26 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// resfreshes the map and resets the variables that will be used again
int	restart(t_game *game)
{
	free_map(game->map_height, game);
	game->map = game->temp_map;
	copy_map_to_temp(game);
	mlx_destroy_image(game->mlx, game->i.exit.img);
	game->exit_count = rng(143, 146);
	snprintf(game->exit_filename, 50,
		"./textures/xpm/tile/tile%d.xpm", game->exit_count);
	create_image(game->exit_filename, &game->i.exit, game);
	mlx_destroy_image(game->mlx, game->i.ground.img);
	draw_map(game->map, game);
	create_image("./textures/xpm/floor/floor227.xpm", &game->i.ground, game);
	game->curr_collec = game->total_collectibles;
	game->moves = 0;
	game->current_frame = 0;
	return (0);
}

void	print_error(int error)
{
	prt("\033[1;31mError\n");
	if (!error)
		prt("Needs only 1 argument\n");
	else if (error == 1)
		prt("Invalid map name\n");
	else if (error == 2)
		prt("File doesn't exist or other\n");
	else if (error == 3)
		prt("Invalid map size\n");
	else if (error == 4)
		prt("Invalid walls or characters\n");
	else if (error == 5)
		prt("Player/exit is not 1 || no collectibles\n");
	else if (error == 6)
		prt("Invalid path\n");
	else
		prt("No memory available or other\n");
	prt("\033[0m");
	exit(0);
}

void	destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx, game->i.wall.img);
	mlx_destroy_image(game->mlx, game->i.ground.img);
	mlx_destroy_image(game->mlx, game->i.exit.img);
	mlx_destroy_image(game->mlx, game->i.danger.img);
	mlx_destroy_image(game->mlx, game->i.down.img);
	mlx_destroy_image(game->mlx, game->i.up.img);
	mlx_destroy_image(game->mlx, game->i.left.img);
	mlx_destroy_image(game->mlx, game->i.right.img);
	mlx_destroy_image(game->mlx, game->i.down_r.img);
	mlx_destroy_image(game->mlx, game->i.up_r.img);
	mlx_destroy_image(game->mlx, game->i.left_r.img);
	mlx_destroy_image(game->mlx, game->i.right_r.img);
	mlx_destroy_image(game->mlx, game->i.down_l.img);
	mlx_destroy_image(game->mlx, game->i.up_l.img);
	mlx_destroy_image(game->mlx, game->i.left_l.img);
	mlx_destroy_image(game->mlx, game->i.right_l.img);
}

// based on last tile before quitting prints a message and frees everything
int	quit(t_game *game)
{
	if (game->map[game->y_pl][game->x_pl] == 'D')
		prt("\033[1;31mYou lose!\033[0m\n");
	else if (game->map[game->y_pl][game->x_pl] == 'E' && !game->curr_collec)
		prt("\033[1;32mYou win!\033[0m\n");
	else
		prt("\033[1;34mProgram closed!\033[0m\n");
	destroy_images(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_map(game->map_height, game);
	game->map = game->temp_map;
	free_map(game->map_height, game);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

void	free_map(int len, t_game *game)
{
	int	i;

	i = 0;
	while (i < len)
		free(game->map[i++]);
	free(game->map);
}
