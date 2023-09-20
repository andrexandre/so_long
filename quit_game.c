/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:25:58 by analexan          #+#    #+#             */
/*   Updated: 2023/09/20 20:12:41 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_handling(int error)
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
	mlx_destroy_image(game->mlx, game->i.adown.img);
	mlx_destroy_image(game->mlx, game->i.aup.img);
	mlx_destroy_image(game->mlx, game->i.aleft.img);
	mlx_destroy_image(game->mlx, game->i.aright.img);
	mlx_destroy_image(game->mlx, game->i.aadown.img);
	mlx_destroy_image(game->mlx, game->i.aaup.img);
	mlx_destroy_image(game->mlx, game->i.aaleft.img);
	mlx_destroy_image(game->mlx, game->i.aaright.img);
}

int	quit(t_game *game)
{
	if (game->map[game->y_pl][game->x_pl] == 'D')
		prt("\033[1;31mYou lose!\033[0m\n");
	else if (game->map[game->y_pl][game->x_pl] == 'E' && !game->collectibles)
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
