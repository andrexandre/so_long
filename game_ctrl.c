/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:25:58 by analexan          #+#    #+#             */
/*   Updated: 2023/09/19 19:16:37 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exec_interactions(int t1, int t2, t_game *heh)
{
	if (heh->map[heh->y_pl][heh->x_pl] == '1')
	{
		heh->x_pl = t1;
		heh->y_pl = t2;
		// heh->moves--;
	}
	else if (heh->map[heh->y_pl][heh->x_pl] == 'C')
	{
		heh->map[heh->y_pl][heh->x_pl] = '0';
		heh->collectibles--;
		if (!heh->collectibles)
		{
			mlx_destroy_image(heh->mlx, heh->exit_i.img);
			heh->exit_i.img = mlx_xpm_file_to_image(heh->mlx, 
					"./xpm/tiles/tile137.xpm", &heh->exit_i.width, 
					&heh->exit_i.height);
		}
	}
	else if (heh->map[heh->y_pl][heh->x_pl] == 'D' || 
			(heh->map[heh->y_pl][heh->x_pl] == 'E' && !heh->collectibles))
		quit(heh);
}

void	error_handling(int error)
{
	prt("\033[1;31mError\n");
	if (!error)
		prt("Needs only 1 argument\n");
	else if (error == 1)
		prt("Invalid map name\n");
	else if (error == 2)
		prt("File doesn't exist or other\n");
	else if (error == 3)
		prt("Invalid map size\n");
	else if (error == 4)
		prt("Invalid walls or characters\n");
	else if (error == 5)
		prt("Player/exit is not 1 || no collectibles\n");
	else if (error == 6)
		prt("Invalid path\n");
	else
		prt("No memory available\n");
	prt("\033[0m");
	exit(0);
}

int	quit(t_game *heh)
{
	if (heh->map[heh->y_pl][heh->x_pl] == 'D')
		prt("\033[1;31mYou lose!\033[0m\n");
	else if (heh->map[heh->y_pl][heh->x_pl] == 'E' && !heh->collectibles)
		prt("\033[1;32mYou win!\033[0m\n");
	else
		prt("\033[1;34mExited Sucessfully!\033[0m\n");
	if (!heh->wall_i.is_created)
		mlx_destroy_image(heh->mlx, heh->wall_i.img);
	if (!heh->ground_i.is_created)
		mlx_destroy_image(heh->mlx, heh->ground_i.img);
	if (!heh->collec_i.is_created)
		mlx_destroy_image(heh->mlx, heh->collec_i.img);
	if (!heh->exit_i.is_created)
		mlx_destroy_image(heh->mlx, heh->exit_i.img);
	if (!heh->danger_i.is_created)
		mlx_destroy_image(heh->mlx, heh->danger_i.img);
	if (!heh->player_i.is_created)
		mlx_destroy_image(heh->mlx, heh->player_i.img);
	if (!heh->up_i.is_created)
		mlx_destroy_image(heh->mlx, heh->up_i.img);
	if (!heh->left_i.is_created)
		mlx_destroy_image(heh->mlx, heh->left_i.img);
	if (!heh->right_i.is_created)
		mlx_destroy_image(heh->mlx, heh->right_i.img);
	if (!heh->aplayer_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aplayer_i.img);
	if (!heh->aup_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aup_i.img);
	if (!heh->aleft_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aleft_i.img);
	if (!heh->aright_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aright_i.img);
	if (!heh->aaplayer_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aaplayer_i.img);
	if (!heh->aaup_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aaup_i.img);
	if (!heh->aaleft_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aaleft_i.img);
	if (!heh->aaright_i.is_created)
		mlx_destroy_image(heh->mlx, heh->aaright_i.img);
	if (heh)
		mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free_map(heh->map_height, heh);
	free(heh->mlx);
	exit(EXIT_SUCCESS);
}

void	free_map(int len, t_game *heh)
{
	int	i;

	i = 0;
	while (i < len)
		free(heh->map[i++]);
	free(heh->map);
}
