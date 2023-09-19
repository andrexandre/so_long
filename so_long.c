/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/19 19:32:13 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	p(int x, int y)
{
	prt("\nn1: %i, n2: %i\n", x, y);
}

int	draw_player(int keycode, int x, int y, t_game *heh, int mode)
{
	if (!mode)
	{
		if (keycode == UP_KEY || keycode == W_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->up_i.img, x, y);
		else if (keycode == LEFT_KEY || keycode == A_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->left_i.img, x, y);
		else if (keycode == RIGHT_KEY || keycode == D_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->right_i.img, x, y);
		else if (keycode == DOWN_KEY || keycode == S_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->player_i.img, x, y);
		else
			mlx_put_image_to_window(heh->mlx, heh->win, heh->player_i.img, x, y);
	}
	else if (mode == 1 && !heh->curr_animation)
	{
		if (keycode == UP_KEY || keycode == W_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aup_i.img, x, y);
		else if (keycode == LEFT_KEY || keycode == A_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aleft_i.img, x, y);
		else if (keycode == RIGHT_KEY || keycode == D_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aright_i.img, x, y);
		else if (keycode == DOWN_KEY || keycode == S_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aplayer_i.img, x, y);
		heh->curr_animation = 1;
	}
	else if (mode == 1 && heh->curr_animation)
	{
		if (keycode == UP_KEY || keycode == W_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aaup_i.img, x, y);
		else if (keycode == LEFT_KEY || keycode == A_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aaleft_i.img, x, y);
		else if (keycode == RIGHT_KEY || keycode == D_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aaright_i.img, x, y);
		else if (keycode == DOWN_KEY || keycode == S_KEY)
			mlx_put_image_to_window(heh->mlx, heh->win, heh->aaplayer_i.img, x, y);
		heh->curr_animation = 0;
	}
	return (1);
}

			// mlx_string_put(heh->mlx, heh->win, x + heh->tile_width / 2, 
			// 	y + heh->tile_width / 2, 0x00FFFFFF, 
			// 	(char []){heh->map[y / heh->tile_height][x / heh->tile_width], 
			// 	'\0'});
void	draw_map(int keycode, int x, int y, t_game *heh)
{
	while (y < heh->win_height - heh->tile_height + 1)
	{
		x = 0;
		while (x < heh->win_width - heh->tile_width + 1)
		{
			if (heh->map[y / heh->tile_height][x / heh->tile_width] == '1')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->wall_i.img, x, y);
			else if (heh->map[y / heh->tile_height][x / heh->tile_width] == 'C')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->collec_i.img, x, y);
			else if (heh->map[y / heh->tile_height][x / heh->tile_width] == 'E')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->exit_i.img, x, y);
			else if (heh->map[y / heh->tile_height][x / heh->tile_width] == 'D')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->danger_i.img, x, y);
			else
				mlx_put_image_to_window(heh->mlx, heh->win, heh->ground_i.img, x, y);
			x += heh->tile_width;
		}
		y += heh->tile_height;
	}
	draw_player(keycode, heh->x_pl * heh->tile_width, heh->y_pl * heh->tile_width, heh, 0);
}

int	press(int keycode, t_game *heh)
{
	char	*str;
	int		t1;
	int		t2;

	heh->is_pressed = 1;
	t1 = heh->x_pl;
	t2 = heh->y_pl;
	heh->moves++;
	heh->keycode = keycode;
	if (heh->keycode == ESC_KEY)
		return (quit(heh));
	if (heh->keycode == UP_KEY || heh->keycode == W_KEY)
		heh->y_pl -= 1;
	else if (heh->keycode == LEFT_KEY || heh->keycode == A_KEY)
		heh->x_pl -= 1;
	else if (heh->keycode == RIGHT_KEY || heh->keycode == D_KEY)
		heh->x_pl += 1;
	else if (heh->keycode == DOWN_KEY || heh->keycode == S_KEY)
		heh->y_pl += 1;
	exec_interactions(t1, t2, heh);
	draw_map(heh->keycode, 0, 0, heh);
	str = ft_itoa(heh->moves);
	mlx_string_put(heh->mlx, heh->win, heh->win_width / 2 - 25, 
		heh->win_height - 5, 0x00FFFFFF, "Moves: ");
	mlx_string_put(heh->mlx, heh->win, heh->win_width / 2 + 17, 
		heh->win_height - 5, 0x00FFFFFF, str);
	free(str);
	return (0);
}

int	check_map(char *str, t_game *heh)
{
	char	*buffer;

	heh->map_height = 0;
	buffer = check_map_name_and_length(str, 0, heh);
	if ((!buffer && !heh->map_height) || (heh->map_height < 3 || 
			heh->map_width < 3))
		error_handling(3);
	check_map_walls_and_create_array(str, 0, heh);
	check_if_valid_map(heh, 0);
	copy_map_to_temp(heh);
	flood_fill(heh->x_pl, heh->y_pl, heh);
	free_map(heh->map_height, heh);
	heh->map = heh->temp_map;
	if (heh->collectibles != 0 || heh->exit_count != 0)
	{
		free_map(heh->map_height, heh);
		error_handling(6);
	}
	heh->collectibles = heh->temp;
	heh->tile_width = 32;
	heh->tile_height = 32;
	heh->win_width = heh->tile_width * heh->map_width;
	heh->win_height = heh->tile_height * heh->map_height;
	heh->moves = 0;
	return (1);
}

void	create_image(char *path, t_image *image, t_game *heh)
{
	image->img = mlx_xpm_file_to_image(heh->mlx, 
			path, &image->width, &image->height);
}

void	game_init(t_game *heh)
{
	heh->mlx = mlx_init();
	heh->win = mlx_new_window(heh->mlx, heh->win_width, heh->win_height, 
			"So long");
	create_image("./xpm/tiles/tile001.xpm", &heh->wall_i, heh);
	create_image("./xpm/floor/floor227.xpm", &heh->ground_i, heh);
	create_image("./xpm/food/food1.xpm", &heh->collec_i, heh);
	create_image("./xpm/tiles/tile145.xpm", &heh->exit_i, heh);
	create_image("./xpm/tiles/tile016.xpm", &heh->danger_i, heh);
	create_image("./xpm/walk/walk01.xpm", &heh->player_i, heh);
	create_image("./xpm/walk/walk02.xpm", &heh->up_i, heh);
	create_image("./xpm/walk/walk03.xpm", &heh->left_i, heh);
	create_image("./xpm/walk/walk04.xpm", &heh->right_i, heh);
	create_image("./xpm/walk/walk05.xpm", &heh->aplayer_i, heh);
	create_image("./xpm/walk/walk06.xpm", &heh->aup_i, heh);
	create_image("./xpm/walk/walk07.xpm", &heh->aleft_i, heh);
	create_image("./xpm/walk/walk08.xpm", &heh->aright_i, heh);
	create_image("./xpm/walk/walk13.xpm", &heh->aaplayer_i, heh);
	create_image("./xpm/walk/walk14.xpm", &heh->aaup_i, heh);
	create_image("./xpm/walk/walk15.xpm", &heh->aaleft_i, heh);
	create_image("./xpm/walk/walk16.xpm", &heh->aaright_i, heh);
	draw_map(0, 0, 0, heh);
	mlx_string_put(heh->mlx, heh->win, heh->win_width / 2 - 25, 
		heh->win_height - 5, 0x00FFFFFF, "Moves: 0");
	heh->map[heh->y_pl][heh->x_pl] = '0'; // deletes 'P' from map
}

int	loop_hook(t_game *heh)
{
	heh->temp++;
	if (!heh->is_pressed && heh->temp - heh->start > 20000)
		draw_player(heh->keycode, heh->x_pl * heh->tile_width, heh->y_pl * heh->tile_width, heh, 0);
	return (0);
}

int	release(int keycode, t_game *heh)
{
	heh->start = heh->temp;
	heh->is_pressed = 0;
	draw_player(keycode, heh->x_pl * heh->tile_width, heh->y_pl * heh->tile_width, heh, 1);
	return (0);
}

// to-do:
// animate the exit and make collectibles random
// and make it only render player and previous block
int	main(int ac, char **av)
{
	static t_game	heh;

	ac = 2;
	av[1] = "maps/m1.ber";
	if (!check_map(av[1], &heh) && ac != 2)
		error_handling(0);
	game_init(&heh);
	mlx_do_key_autorepeaton(heh.mlx);
	heh.is_pressed = 0;
	heh.temp = 0;
	heh.curr_animation = 0;
	mlx_hook(heh.win, 2, 1L << 0, press, &heh);
	mlx_hook(heh.win, 3, 1L << 1, release, &heh);
	mlx_hook(heh.win, 17, 0, quit, &heh);
	mlx_loop_hook(heh.mlx, loop_hook, &heh);
	mlx_loop(heh.mlx);
	return (0);
}
/* x Width Largura, y Length Comprimento and y Height Altura

	// av[1] = ".ber"; // Invalid map (walls not 1)
	// av[1] = ".bera"; // Invalid map name
	// av[1] = "asd.ber"; // File doesn't exist
	// av[1] = ".ber.ber"; // invalid map size (little)
	// av[1] = "maps/.ber"; // Invalid map (less walls)
	// av[1] = "maps/.ber.ber"; // empty file (invalid map size)

	// if (keycode < 32 || keycode > 126)
	// 	prt("keycode: %i = NULL\n", keycode);
	// else
	// 	prt("keycode: %i = '%c'\n", keycode, keycode);
*/
