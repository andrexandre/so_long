/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:36:08 by analexan          #+#    #+#             */
/*   Updated: 2023/09/20 19:44:46 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(char *str, t_game *game)
{
	game->map_height = 0;
	if ((!check_map_name_and_length(str, 0, game) && !game->map_height) || 
		(game->map_height < 3 || game->map_width < 3))
		error_handling(3);
	check_map_walls_and_create_array(str, 0, game);
	check_if_valid_map(game, 0);
	copy_map_to_temp(game);
	flood_fill(game->x_pl, game->y_pl, game);
	free_map(game->map_height, game);
	game->map = game->temp_map;
	if (game->collectibles != 0 || game->exit_count != 0)
	{
		free_map(game->map_height, game);
		error_handling(6);
	}
	game->collectibles = game->total_collectibles;
	game->tile_width = 32;
	game->tile_height = 32;
	game->win_width = game->tile_width * game->map_width;
	game->win_height = game->tile_height * game->map_height;
	game->moves = 0;
	return (1);
}

int	restart(t_game *game)
{
	free_map(game->map_height, game);
	game->map = game->temp_map;
	copy_map_to_temp(game);
	mlx_destroy_image(game->mlx, game->i.exit.img);
	game->exit_count = rng(143, 146);
	snprintf(game->exit_filename, 25, 
		"./xpm/tile/tile%d.xpm", game->exit_count);
	create_image(game->exit_filename, &game->i.exit, game);
	draw_map(game->map, game);
	game->collectibles = game->total_collectibles;
	game->moves = 0;
	game->current_frame = 0;
	return (0);
}

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
		game->collectibles--;
		if (!game->collectibles)
		{
			game->exit_count -= 8;
			snprintf(game->exit_filename, 25, 
				"./xpm/tile/tile%d.xpm", game->exit_count);
			mlx_destroy_image(game->mlx, game->i.exit.img);
			game->i.exit.img = mlx_xpm_file_to_image(game->mlx, 
					game->exit_filename, &game->i.exit.width, 
					&game->i.exit.height);
			draw_food_or_exit(-1, -1, game);
		}
	}
	else if (game->map[game->y_pl][game->x_pl] == 'D' || 
			(game->map[game->y_pl][game->x_pl] == 'E' && !game->collectibles))
		quit(game);
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

