/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:41:58 by andrealex         #+#    #+#             */
/*   Updated: 2023/09/27 04:12:54 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	update_image(int keycode, t_game *game)
{
	if (keycode == ZERO_NP)
		keycode = '0';
	if (keycode == ONE_NP)
		keycode = '1';
	if (keycode == '1' || keycode == '0' || keycode == 'C' || keycode == 'E'
		|| keycode == 'P' || keycode == 'D')
		game->selected_char = keycode;
	else
		return ;
	if (game->selected_char == '1')
		game->selected_image = &game->i.wall;
	else if (game->selected_char == 'C')
		game->selected_image = &game->i.collec;
	else if (game->selected_char == 'E')
		game->selected_image = &game->i.exit;
	else if (game->selected_char == 'D')
		game->selected_image = &game->i.danger;
	else if (game->selected_char == '0')
		game->selected_image = &game->i.ground;
	else if (game->selected_char == 'P')
		game->selected_image = &game->i.down;
	if (game->last_keycode != game->keycode && game->last_x && game->last_y)
		change_tile(game->selected_char, game);
	prt("\033[1;36m%c selected\n", game->selected_char);
}

int	editor(int keycode, t_game *game)
{
	if (!game->editor_on)
	{
		game->editor_on = 1;
		game->selected_image = &game->i.wall;
		game->keycode = '1';
		game->selected_char = '1';
		change_tile(game->selected_char, game);
		prt("How to edit the map:\n"
			"0 - ground\n"
			"1 - wall\n"
			"e - exit\n"
			"c - collectible\n"
			"p - player\n"
			"d - danger\n"
			"s - save the map\n"
			"n - create a new map\n");
		return (0);
	}
	if (keycode >= 'a' && keycode < 'z')
		keycode -= 32;
	update_image(keycode, game);
	return (0);
}

void	save_map(int fd, t_game *game)
{
	int		i;
	int		needs_free;
	char	*map_name;

	i = -1;
	prt("name of the map (m to map.ber): ");
	map_name = malloc(100);
	if (!map_name)
		print_error(-1);
	scanf("%99s", map_name);
	needs_free = !(*map_name == 'm' && map_name[1] == '\0');
	if (*map_name == 'm' && map_name[1] == '\0')
	{
		free(map_name);
		map_name = "map.ber";
	}
	fd = open(map_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		print_error(-1);
	prt("\033[1;32mMap saved to %s\033[0m\n", map_name);
	if (needs_free)
		free(map_name);
	while (game->map[++i])
		write(fd, game->map[i], ft_strlen(game->map[i], 0));
	close(fd);
}

void	create_blank_map(char **map_name, int map_width, int map_height, int fd)
{
	int	i;
	int	j;

	i = -1;
	fd = open(*map_name, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0666);
	while (++i < map_height)
	{
		j = -1;
		while (++j < map_width)
		{
			if (i == 1 && j == 1 && j++ && j++)
				write(fd, "PCE", 3);
			else if (!j || j == map_width - 1 || !i || i == map_height - 1)
				write(fd, "1", 1);
			else
				write(fd, "0", 1);
		}
		write(fd, "\n", 1);
	}
	close(fd);
}

void	new_map(int map_width, int map_height, t_game *game)
{
	char	*map_name;

	prt("Choose map width and height!\n");
	scanf("%i %i", &map_width, &map_height);
	if (map_width < 5 || map_height < 5 || map_width > 60 || map_height > 31)
	{
		prt("Size has to be:\n5 < map_width < 60\n5 < map_height < 31\n");
		return ;
	}
	prt("name of the map: ");
	map_name = malloc(100);
	if (!map_name)
		print_error(-1);
	scanf("%99s", map_name);
	create_blank_map(&map_name, map_width, map_height, 0);
	prt("\033[1;33mNew map created to %s\033[0m\n", map_name);
	free(map_name);
	quit(game);
}
