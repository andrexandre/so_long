/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/15 19:24:36 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(int len, t_game *heh)
{
	int	i;

	i = 0;
	while (i < len)
		free(heh->map[i++]);
	free(heh->map);
}

	// if (!heh->image.is_created)
	// 	mlx_destroy_image(heh->mlx, heh->image.img);
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
	if (!heh->player_i.is_created)
		mlx_destroy_image(heh->mlx, heh->player_i.img);
	if (!heh->danger_i.is_created)
		mlx_destroy_image(heh->mlx, heh->danger_i.img);
	if (heh)
		mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free_map(heh->map_height, heh);
	free(heh->mlx);
	exit(EXIT_SUCCESS);
}

static int	ft_intlen(int num)
{
	int	intlen;

	if (!num)
		return (1);
	if (num == -2147483648)
		return (10);
	intlen = 0;
	if (num < 0)
		intlen++;
	while (num)
	{
		intlen++;
		num /= 10;
	}
	return (intlen);
}

static void	ft_changestr(int n, int c, char *str, int mc)
{
	str[c] = 0;
	if (n == 0)
		str[0] = '0';
	if (mc == -1)
		str[0] = '-';
	if (n == -2147483648)
	{
		c--;
		n /= 10;
		n = -n;
		str[0] = '-';
		str[c] = '8';
	}
	while (n > 0)
	{
		str[c-- - 1] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		mc;
	int		c;
	char	*str;

	mc = 1;
	c = 1;
	if (n < 0)
	{
		mc = -1;
		if (n != -2147483648)
			n = -n;
		c++;
	}
	c += ft_intlen(n);
	str = malloc(c--);
	if (!str)
		return (NULL);
	ft_changestr(n, c, str, mc);
	return (str);
}

int	key_hook(int keycode, t_game *heh)
{
	char	*str;
	int		t1;
	int		t2;
	int		x;
	int		y;

	x = 0;
	y = 0;
	t1 = heh->x_pl;
	t2 = heh->y_pl;
	heh->moves++;
	if (keycode == ESC_KEY)
		return (quit(heh));
	if (keycode == UP_KEY || keycode == W_KEY)
		heh->y_pl -= 1;
	else if (keycode == LEFT_KEY || keycode == A_KEY)
		heh->x_pl -= 1;
	else if (keycode == RIGHT_KEY || keycode == D_KEY)
		heh->x_pl += 1;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		heh->y_pl += 1;
	if (heh->map[heh->y_pl][heh->x_pl] == '1')
	{
		heh->x_pl = t1;
		heh->y_pl = t2;
	}
	else if (heh->map[heh->y_pl][heh->x_pl] == 'C')
	{
		heh->map[heh->y_pl][heh->x_pl] = '0';
		heh->collectibles--;
	}
	else if (heh->map[heh->y_pl][heh->x_pl] == 'D' || 
			(heh->map[heh->y_pl][heh->x_pl] == 'E' && !heh->collectibles))
		quit(heh);
	if (!heh->collectibles)
	{
		mlx_destroy_image(heh->mlx, heh->exit_i.img);
		heh->exit_i.img = mlx_xpm_file_to_image(heh->mlx, 
				"./xpm/tiles/tile137.xpm", &heh->exit_i.width, &heh->exit_i.height);
	}
	while (y < heh->win_height - heh->wall_i.height + 1)
	{
		while (x < heh->win_width - heh->wall_i.width + 1)
		{
			if (heh->map[y / heh->wall_i.height][x / heh->wall_i.width] == '1')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->wall_i.img, x, y);
			else if (heh->map[y / heh->wall_i.height][x / heh->wall_i.width] == 'C')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->collec_i.img, x, y);
			else if (heh->map[y / heh->wall_i.height][x / heh->wall_i.width] == 'E')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->exit_i.img, x, y);
			else if (heh->map[y / heh->wall_i.height][x / heh->wall_i.width] == 'D')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->danger_i.img, x, y);
			else
				mlx_put_image_to_window(heh->mlx, heh->win, heh->ground_i.img, x, y);
			if (heh->x_pl == x / heh->wall_i.width && heh->y_pl == y / heh->wall_i.height)
				mlx_put_image_to_window(heh->mlx, heh->win, heh->player_i.img, x, y);
			x += heh->wall_i.width;
		}
		x = 0;
		y += heh->wall_i.height;
	}
	str = ft_itoa(heh->moves);
	mlx_string_put(heh->mlx, heh->win, heh->win_width / 2 - 25, 
		heh->win_height - 5, 0x00FFFFFF, "Moves: ");
	mlx_string_put(heh->mlx, heh->win, heh->win_width / 2 + 40 - 25, 
		heh->win_height - 5, 0x00FFFFFF, str);
	free(str);
	return (0);
}

// returns the length of str that has only char in accept
int	ft_strspn(const char *str, const char *accept)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (accept[j])
			if (str[i] == accept[j++])
				break ;
		if (!accept[j] && str[i] != accept[j - 1])
			return (i);
		j = 0;
		i++;
	}
	return (i);
}

// searches for the string little in the string big
char	*ft_strstr(const char *big, const char *little)
{
	unsigned int	i;
	int				j;
	char			*bptr;
	char			*lptr;

	bptr = (char *)big;
	lptr = (char *)little;
	i = 0;
	j = 0;
	if (!lptr[i])
		return (bptr);
	while (bptr[i])
	{
		while (bptr[i + j] && bptr[i + j] == lptr[j])
		{
			if (!lptr[j + 1])
				return (&bptr[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

void	check_map(t_game *heh, int is_player)
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

void	game_init(char *str, t_game *heh)
{
	char	*buffer;

	heh->map_height = 0;
	buffer = check_map_name_and_length(str, 0, heh);
	if ((!buffer && !heh->map_height) || (heh->map_height < 3 || 
			heh->map_width < 3))
		error_handling(3);
	check_map_walls_and_create_array(str, 0, heh);
	check_map(heh, 0);
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
}

// to-do:
// make bonus (animation)
int	main(int ac, char **av)
{
	static t_game	heh;

	ac = 2;
	av[1] = "maps/test.ber";
	if (ac != 2)
		error_handling(0);
	game_init(av[1], &heh);
	heh.mlx = mlx_init();
	heh.win = mlx_new_window(heh.mlx, heh.win_width, heh.win_height, 
			"So long n thank you for all the fish");
	heh.wall_i.img = mlx_xpm_file_to_image(heh.mlx, 
			"./xpm/tiles/tile001.xpm", &heh.wall_i.width, &heh.wall_i.height);
	heh.ground_i.img = mlx_xpm_file_to_image(heh.mlx, 
			"./xpm/floor/floor227.xpm", &heh.ground_i.width, &heh.ground_i.height);
	heh.collec_i.img = mlx_xpm_file_to_image(heh.mlx, 
			"./xpm/food/food01.xpm", &heh.collec_i.width, &heh.collec_i.height);
	heh.exit_i.img = mlx_xpm_file_to_image(heh.mlx, 
			"./xpm/tiles/tile145.xpm", &heh.exit_i.width, &heh.exit_i.height);
	heh.player_i.img = mlx_xpm_file_to_image(heh.mlx, 
			"./xpm/walk/walk01.xpm", &heh.player_i.width, &heh.player_i.height);
	heh.danger_i.img = mlx_xpm_file_to_image(heh.mlx, 
			"./xpm/tiles/tile016.xpm", &heh.danger_i.width, &heh.danger_i.height);
	heh.moves = -1;
	key_hook(0, &heh);
	mlx_hook(heh.win, 2, 1L << 0, key_hook, &heh);
	mlx_hook(heh.win, 17, 0, quit, &heh);
	mlx_loop(heh.mlx);
	return (0);
}
/* x Width Largura, y Length Comprimento and y Height Altura
// fold all: Ctrl + K Ctrl + 1

	// put_grad_square(&heh.image, 5, 0, heh.win_width - 5, heh.win_height - 5, 0);
	// mlx_string_put(heh.mlx, heh.win, 100, 500, argb(0, 255, 255, 255), "Howdy people!");
	// heh.wall_i.img = mlx_xpm_file_to_image(heh.mlx, "./cwd/file.xpm", &heh.wall_i.width, &heh.wall_i.height);
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

			// mlx_string_put(heh->mlx, heh->win, x + heh->wall_i.width / 2, y + heh->wall_i.width / 2, 0x00FFFFFF, 
			// 	(char []){heh->map[y/heh->wall_i.height][x/heh->wall_i.width], '\0'});
*/
