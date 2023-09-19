/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:06:56 by analexan          #+#    #+#             */
/*   Updated: 2023/09/18 15:10:50 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	copy_map_to_temp(t_game *heh)
{
	int	x;
	int	y;

	y = -1;
	heh->temp_map = malloc(sizeof(heh->map) * (heh->map_height + 1));
	if (!heh->temp_map)
		error_handling(-1);
	heh->temp_map[heh->map_height] = NULL;
	while (++y < heh->map_height)
	{
		x = -1;
		heh->temp_map[y] = malloc(heh->map_width + 2);
		if (!heh->temp_map[y])
			error_handling(-1);
		heh->temp_map[y][heh->map_width + 1] = '\0';
		while (++x < heh->map_width + 1)
		{
			heh->temp_map[y][x] = heh->map[y][x];
			if (heh->map[y][x] == 'P')
			{
				heh->x_pl = x;
				heh->y_pl = y;
			}
		}
	}
}

void	check_if_valid_map(t_game *heh, int is_player)
{
	int	i;
	int	j;

	i = -1;
	while (++i < heh->map_height)
	{
		j = -1;
		while (!(!i || i == heh->map_height - 1) && ++j < heh->map_width)
		{
			if (heh->map[i][j] == 'P')
				is_player++;
			else if (heh->map[i][j] == 'E')
				heh->exit_count++;
			else if (heh->map[i][j] == 'C')
				heh->collectibles++;
		}
	}
	if (is_player != 1 || heh->exit_count != 1 || !heh->collectibles)
	{
		free_map(heh->map_height, heh);
		error_handling(5);
	}
	heh->temp = heh->collectibles;
	heh->x_pl = 0;
	heh->y_pl = 0;
}

void	check_map_walls_and_create_array(char *str, int fd, t_game *heh)
{
	int	i;

	i = 0;
	fd = open(str, O_RDONLY);
	heh->map = malloc(sizeof(char *) * (heh->map_height + 1));
	if (fd < 0 || !heh->map)
		error_handling(2);
	heh->map[heh->map_height] = NULL;
	while (1)
	{
		heh->map[i] = get_next_line(fd);
		if (!heh->map[i])
			break ;
		if (((!i || i == heh->map_height - 1) && 
				(heh->map_width != ft_strspn(heh->map[i], "1")))
			|| heh->map_width != ft_strspn(heh->map[i], "01CEPD"))
		{
			free_map(i + 1, heh);
			error_handling(4);
		}
		i++;
	}
	close(fd);
	heh->collectibles = 0;
	heh->exit_count = 0;
}

char	*check_map_name_and_length(char *str, int fd, t_game *heh)
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
		if (!(heh->map_height)++)
			heh->map_width = ft_strlen(buffer, 1);
		if (ft_strlen(buffer, 1) != heh->map_width || *buffer != '1' 
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

void	flood_fill(int x, int y, t_game *heh)
{
	if (x >= heh->map_width || x < 0 
		|| y >= heh->map_height || y < 0 
		|| heh->map[y][x] == '1' 
		|| heh->map[y][x] == 'D' 
		|| heh->map[y][x] == 'F')
		return ;
	if (heh->map[y][x] == 'C')
		heh->collectibles--;
	else if (heh->map[y][x] == 'E')
		heh->exit_count--;
	heh->map[y][x] = 'F';
	flood_fill(x - 1, y, heh);
	flood_fill(x + 1, y, heh);
	flood_fill(x, y + 1, heh);
	flood_fill(x, y - 1, heh);
}
