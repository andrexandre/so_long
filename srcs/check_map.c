/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:56 by analexan          #+#    #+#             */
/*   Updated: 2023/09/26 22:02:26 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// check if the file ends in .ber, map is rectangular
// and first and last line of the file is only '1'
char	*check_map_name_and_length(char *str, int fd, t_game *game)
{
	char	*buffer;

	if (ft_strlen(str, 0) < 4
		|| ft_strcmp(str + (ft_strlen(str, 0) - 4), ".ber"))
		print_error(1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		print_error(2);
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (!(game->map_height)++)
			game->map_width = ft_strlen(buffer, 1);
		if (ft_strlen(buffer, 1) != game->map_width || *buffer != '1'
			|| buffer[ft_strlen(buffer, 1) - 1] != '1')
		{
			free(buffer);
			print_error(4);
		}
		free(buffer);
	}
	close(fd);
	return (buffer);
}

// check if all lines start and end with '1', there's
// no invalid characters and create the map
void	check_map_walls_and_create_array(char *str, int fd, t_game *game)
{
	int	i;

	i = 0;
	fd = open(str, O_RDONLY);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (fd < 0 || !game->map)
		print_error(2);
	game->map[game->map_height] = NULL;
	while (1)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
			break ;
		if (((!i || i == game->map_height - 1)
				&& (game->map_width != ft_strspn(game->map[i], "1")))
			|| game->map_width != ft_strspn(game->map[i], "01CEPD"))
		{
			free_map(i + 1, game);
			print_error(4);
		}
		i++;
	}
	close(fd);
}

// check if player/exit are 1 or if there's collectibles
void	check_if_valid_map(t_game *game, int is_player)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (!(!i || i == game->map_height - 1) && ++j < game->map_width)
		{
			if (game->map[i][j] == 'P')
				is_player++;
			else if (game->map[i][j] == 'E')
				game->exit_count++;
			else if (game->map[i][j] == 'C')
				game->curr_collec++;
		}
	}
	if (is_player != 1 || game->exit_count != 1 || !game->curr_collec)
	{
		free_map(game->map_height, game);
		print_error(5);
	}
	game->total_collectibles = game->curr_collec;
}

void	copy_map_to_temp(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	game->temp_map = malloc(sizeof(game->map) * (game->map_height + 1));
	if (!game->temp_map)
		print_error(-1);
	game->temp_map[game->map_height] = NULL;
	while (++y < game->map_height)
	{
		x = -1;
		game->temp_map[y] = malloc(game->map_width + 2);
		if (!game->temp_map[y])
			print_error(-1);
		game->temp_map[y][game->map_width + 1] = '\0';
		while (++x < game->map_width + 1)
		{
			game->temp_map[y][x] = game->map[y][x];
			if (game->map[y][x] == 'P')
			{
				game->x_pl = x;
				game->y_pl = y;
			}
		}
	}
}

// check if there's a valid path from the player to collectibles and exit
void	flood_fill(int x, int y, t_game *game)
{
	if (x >= game->map_width || x < 0
		|| y >= game->map_height || y < 0
		|| game->map[y][x] == '1'
		|| game->map[y][x] == 'D')
		return ;
	if (game->map[y][x] == 'C')
		game->curr_collec--;
	else if (game->map[y][x] == 'E')
		game->exit_count--;
	game->map[y][x] = '1';
	flood_fill(x - 1, y, game);
	flood_fill(x + 1, y, game);
	flood_fill(x, y + 1, game);
	flood_fill(x, y - 1, game);
}
