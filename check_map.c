/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:56 by analexan          #+#    #+#             */
/*   Updated: 2023/09/20 19:38:11 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	copy_map_to_temp(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	game->temp_map = malloc(sizeof(game->map) * (game->map_height + 1));
	if (!game->temp_map)
		error_handling(-1);
	game->temp_map[game->map_height] = NULL;
	while (++y < game->map_height)
	{
		x = -1;
		game->temp_map[y] = malloc(game->map_width + 2);
		if (!game->temp_map[y])
			error_handling(-1);
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
				game->collectibles++;
		}
	}
	if (is_player != 1 || game->exit_count != 1 || !game->collectibles)
	{
		free_map(game->map_height, game);
		error_handling(5);
	}
	game->total_collectibles = game->collectibles;
	game->x_pl = 0;
	game->y_pl = 0;
}

void	check_map_walls_and_create_array(char *str, int fd, t_game *game)
{
	int	i;

	i = 0;
	fd = open(str, O_RDONLY);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (fd < 0 || !game->map)
		error_handling(2);
	game->map[game->map_height] = NULL;
	while (1)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
			break ;
		if (((!i || i == game->map_height - 1) && 
				(game->map_width != ft_strspn(game->map[i], "1")))
			|| game->map_width != ft_strspn(game->map[i], "01CEPD"))
		{
			free_map(i + 1, game);
			error_handling(4);
		}
		i++;
	}
	close(fd);
	game->collectibles = 0;
	game->exit_count = 0;
}

char	*check_map_name_and_length(char *str, int fd, t_game *game)
{
	char	*buffer;

	if (ft_strlen(str, 0) < 4 || 
		ft_strcmp(str + (ft_strlen(str, 0) - 4), ".ber"))
		error_handling(1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		error_handling(2);
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
			error_handling(4);
		}
		free(buffer);
	}
	close(fd);
	return (buffer);
}

void	flood_fill(int x, int y, t_game *game)
{
	if (x >= game->map_width || x < 0 
		|| y >= game->map_height || y < 0 
		|| game->map[y][x] == '1' 
		|| game->map[y][x] == 'D' 
		|| game->map[y][x] == 'F')
		return ;
	if (game->map[y][x] == 'C')
		game->collectibles--;
	else if (game->map[y][x] == 'E')
		game->exit_count--;
	game->map[y][x] = 'F';
	flood_fill(x - 1, y, game);
	flood_fill(x + 1, y, game);
	flood_fill(x, y + 1, game);
	flood_fill(x, y - 1, game);
}
