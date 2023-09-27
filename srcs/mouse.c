/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:44:57 by andrealex         #+#    #+#             */
/*   Updated: 2023/09/26 22:02:26 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	mouse_press(int button, int m_x, int m_y, t_game *game)
{
	int	curr_x;
	int	curr_y;

	curr_y = 0;
	game->mouse_clicking = 1;
	while (curr_y < game->win_height - game->tile_height + 1)
	{
		curr_x = 0;
		while (curr_x < game->win_width - game->tile_width + 1)
		{
			if (m_x > curr_x && m_y > curr_y && m_x < curr_x + game->tile_width
				&& m_y < curr_y + game->tile_height)
			{
				if (game->editor_on)
					game->map[curr_y / game->tile_height][curr_x
						/ game->tile_width] = game->selected_char;
				change_tile(game->map[curr_y / game->tile_height][curr_x
					/ game->tile_width], game);
			}
			curr_x += game->tile_width;
		}
		curr_y += game->tile_height;
	}
	(void)button;
	return (0);
}

int	mouse_release(int button, int m_x, int m_y, t_game *game)
{
	game->mouse_clicking = 0;
	(void)button;
	(void)m_x;
	(void)m_y;
	return (0);
}

void	mouse_move_operations(int curr_x, int curr_y, t_game *game)
{
	if (game->mouse_clicking)
		game->map[curr_y / game->tile_height][curr_x
			/ game->tile_width] = game->selected_char;
	if (game->editor_on && game->last_map_char)
		change_tile(game->last_map_char, game);
	game->last_x = curr_x / game->tile_width;
	game->last_y = curr_y / game->tile_height;
	game->last_map_char = game->map[game->last_y][game->last_x];
	if (game->editor_on)
		image_to_window(*game->selected_image, curr_x, curr_y, game);
}

int	mouse_move(int m_x, int m_y, t_game *game)
{
	int	curr_x;
	int	curr_y;

	curr_y = 0;
	while (curr_y < game->win_height - game->tile_height + 1)
	{
		curr_x = 0;
		while (curr_x < game->win_width - game->tile_width + 1)
		{
			if (m_x > curr_x && m_y > curr_y && m_x < curr_x + game->tile_width
				&& m_y < curr_y + game->tile_height)
			{
				if (game->last_x == curr_x / game->tile_width
					&& game->last_y == curr_y / game->tile_height)
					break ;
				mouse_move_operations(curr_x, curr_y, game);
				game->tile_called = 1;
			}
			curr_x += game->tile_width;
		}
		curr_y += game->tile_height;
	}
	return (0);
}

void	change_tile(char map_char, t_game *game)
{
	if (game->tile_called)
	{
		game->last_x *= game->tile_width;
		game->last_y *= game->tile_height;
	}
	if (map_char == '1')
		image_to_window(game->i.wall, game->last_x, game->last_y, game);
	else if (map_char == 'C')
		image_to_window(game->i.collec, game->last_x, game->last_y, game);
	else if (map_char == 'E')
		image_to_window(game->i.exit, game->last_x, game->last_y, game);
	else if (map_char == 'D')
		image_to_window(game->i.danger, game->last_x, game->last_y, game);
	else if (map_char == '0')
		image_to_window(game->i.ground, game->last_x, game->last_y, game);
	else if (map_char == 'P')
		image_to_window(game->i.down, game->last_x, game->last_y, game);
	game->tile_called = 0;
}
