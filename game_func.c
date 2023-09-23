/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:36:08 by analexan          #+#    #+#             */
/*   Updated: 2023/09/23 17:55:07 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

// random number generator based on reading /dev/urandom
// print_error(-1); = Failed to open/read /dev/urandom
int	rng(int min, int max)
{
	int		random_data;
	int		fd;
	ssize_t	bytes_read;

	random_data = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		print_error(-1);
	bytes_read = read(fd, &random_data, sizeof(random_data));
	if (bytes_read < 0)
		print_error(-1);
	close(fd);
	if (random_data < 0)
		return ((-random_data % (max - min + 1)) + min);
	return ((random_data % (max - min + 1)) + min);
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
