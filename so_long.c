/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/20 20:11:04 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, 
			"So long");
	create_image("./xpm/tile/tile001.xpm", &game->i.wall, game);
	create_image("./xpm/floor/floor227.xpm", &game->i.ground, game);
	game->exit_count = rng(143, 146);
	snprintf(game->exit_filename, 25, "./xpm/tile/tile%d.xpm", 
		game->exit_count);
	create_image(game->exit_filename, &game->i.exit, game);
	create_image("./xpm/tile/tile016.xpm", &game->i.danger, game);
	create_image("./xpm/walk/walk01.xpm", &game->i.down, game);
	create_image("./xpm/walk/walk02.xpm", &game->i.up, game);
	create_image("./xpm/walk/walk03.xpm", &game->i.left, game);
	create_image("./xpm/walk/walk04.xpm", &game->i.right, game);
	create_image("./xpm/walk/walk05.xpm", &game->i.adown, game);
	create_image("./xpm/walk/walk06.xpm", &game->i.aup, game);
	create_image("./xpm/walk/walk07.xpm", &game->i.aleft, game);
	create_image("./xpm/walk/walk08.xpm", &game->i.aright, game);
	create_image("./xpm/walk/walk09.xpm", &game->i.aadown, game);
	create_image("./xpm/walk/walk10.xpm", &game->i.aaup, game);
	create_image("./xpm/walk/walk11.xpm", &game->i.aaleft, game);
	create_image("./xpm/walk/walk12.xpm", &game->i.aaright, game);
	copy_map_to_temp(game);
	draw_map(game->map, game);
	mlx_do_key_autorepeaton(game->mlx);
}

int	press(int keycode, t_game *game)
{
	int		prev_x_pl;
	int		prev_y_pl;

	prev_x_pl = game->x_pl;
	prev_y_pl = game->y_pl;
	game->keycode = keycode;
	if (game->keycode == ESC_KEY || game->keycode == 'q')
		return (quit(game));
	else if (game->keycode == 'r')
		return (restart(game));
	else if (game->keycode == UP_KEY || game->keycode == 'w')
		game->y_pl -= 1;
	else if (game->keycode == LEFT_KEY || game->keycode == 'a')
		game->x_pl -= 1;
	else if (game->keycode == RIGHT_KEY || game->keycode == 'd')
		game->x_pl += 1;
	else if (game->keycode == DOWN_KEY || game->keycode == 's')
		game->y_pl += 1;
	exec_interactions(prev_x_pl, prev_y_pl, game);
	update_map(prev_x_pl, prev_y_pl, game);
	return (0);
}

int	release(int keycode, t_game *game)
{
	game->frame_of_release = game->current_frame;
	draw_player(game->keycode, 1, game);
	(void)keycode;
	return (0);
}

int	loop(t_game *game)
{
	game->current_frame++;
	if (game->current_frame - game->frame_of_release > 20000)
		draw_player(game->keycode, 0, game);
	return (0);
}

int	main(int ac, char **av)
{
	static t_game	game;

	if (!check_map(av[1], &game) && ac != 2)
		error_handling(0);
	game_init(&game);
	game.current_frame = 0;
	game.curr_animation = 0;
	mlx_hook(game.win, 2, 1L << 0, press, &game);
	mlx_hook(game.win, 3, 1L << 1, release, &game);
	mlx_hook(game.win, 17, 0, quit, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
/* x Width Largura, y Length Comprimento and y Height Altura
	if (game->map_width > 60 || game->map_height > 31)
		it's bigger than the screen;
	if (keycode < 32 || keycode > 126)
		prt("keycode: %i = NULL\n", keycode);
	else
		prt("keycode: %i = '%c'\n", keycode, keycode);
	// ac = 2;
	// av[1] = "maps/test.ber";
*/
