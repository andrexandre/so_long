/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/27 04:13:40 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// map checking and setting of some variables
int	check_map(char *str, t_game *game)
{
	if ((!check_map_name_and_length(str, 0, game) && !game->map_height)
		|| (game->map_height < 3 || game->map_width < 3))
		print_error(3);
	check_map_walls_and_create_array(str, 0, game);
	check_if_valid_map(game, 0);
	copy_map_to_temp(game);
	flood_fill(game->x_pl, game->y_pl, game);
	free_map(game->map_height, game);
	game->map = game->temp_map;
	if (game->curr_collec != 0 || game->exit_count != 0)
	{
		free_map(game->map_height, game);
		print_error(6);
	}
	copy_map_to_temp(game);
	game->curr_collec = game->total_collectibles;
	game->tile_width = 32;
	game->tile_height = 32;
	game->win_width = game->tile_width * game->map_width;
	game->win_height = game->tile_height * game->map_height;
	return (1);
}

int	key_press(int keycode, t_game *game)
{
	int	prev_x_pl;
	int	prev_y_pl;

	prev_x_pl = game->x_pl;
	prev_y_pl = game->y_pl;
	game->keycode = keycode;
	if (game->keycode == ESC_KEY || game->keycode == 'q')
		return (quit(game));
	else if (game->keycode == 'r')
		return (restart(game));
	if (game->editor_on)
		return (0);
	else if (game->keycode == UP_KEY || game->keycode == 'w')
		game->y_pl -= 1;
	else if (game->keycode == LEFT_KEY || game->keycode == 'a')
		game->x_pl -= 1;
	else if (game->keycode == RIGHT_KEY || game->keycode == 'd')
		game->x_pl += 1;
	else if (game->keycode == DOWN_KEY || game->keycode == 's')
		game->y_pl += 1;
	else
		return (0);
	exec_interactions(prev_x_pl, prev_y_pl, game);
	update_map(prev_x_pl, prev_y_pl, game);
	return (0);
}

// saves the frame_of_release to compare in loop function
// i used game->keycode to bug fix
int	key_release(int keycode, t_game *game)
{
	game->frame_of_release = game->current_frame;
	if (game->keycode == 'h')
		mlx_clear_window(game->mlx, game->win);
	if (!game->editor_on)
	{
		draw_player(game->keycode, 1, game);
		if (keycode == 'e')
			editor(keycode, game);
		return (0);
	}
	else
		editor(game->keycode, game);
	if (keycode == 's')
		save_map(0, game);
	else if (keycode == 'n')
		new_map(-1, -1, game);
	return (0);
}

// if 20000 frames have passes since the
// release of the key, the player stops walking
int	loop(t_game *game)
{
	game->current_frame++;
	if (!game->editor_on)
		if (game->current_frame
			- game->frame_of_release > game->animation_delay)
			draw_player(game->keycode, 0, game);
	return (0);
}

int	main(int ac, char **av)
{
	static t_game	game;

	if (!check_map(av[1], &game) && ac != 2)
		print_error(0);
	game.current_map = av[1];
	srand(time(NULL));
	game_init(&game);
	if (!strcmp(getenv("USER"), "andrealex"))
		game.animation_delay = 10000;
	else
		game.animation_delay = 20000;
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 4, 1L << 2, mouse_press, &game);
	mlx_hook(game.win, 5, 1L << 3, mouse_release, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_hook(game.win, 17, 0, quit, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
