/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/13 19:15:30 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	quit(t_game *heh)
{
	if (heh->p_image.img)
		mlx_destroy_image(heh->mlx, heh->p_image.img);
	if (heh)
		mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free(heh->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game *heh)
{
	if (keycode == ESC_KEY)
		return (quit(heh));
	if (keycode == UP_KEY || keycode == W_KEY)
		heh->y -= 10;
	else if (keycode == LEFT_KEY || keycode == A_KEY)
		heh->x -= 10;
	else if (keycode == RIGHT_KEY || keycode == D_KEY)
		heh->x += 10;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		heh->y += 10;
	if (keycode < 32 || keycode > 126)
		prt("keycode: %i = NULL\n", keycode);
	else
		prt("keycode: %i = '%c'\n", keycode, keycode);
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
		prt("Invalid map name\n");
	else if (error == 1)
		prt("File doesn't exist or other\n");
	else if (error == 2)
		prt("Invalid map size\n");
	else if (error == 3)
		prt("Invalid map walls or characters\n");
	else if (error == 4)
		prt("Player/exit is not 1 || no collectibles\n");
	else if (error == 5)
		prt("Invalid path\n");
	else
		prt("No memory available\n");
	prt("\033[0m");
	exit(0);
}

void	free_map(int len, t_game *heh)
{
	int	i;

	i = 0;
	while (i < len)
		free(heh->map[i++]);
	// i = 0;
	// while (i < len)
	// 	free(heh->temp[i++]);
	free(heh->map);
}

void	copy_map_to_temp(t_game *heh)
{
	int	x;
	int	y;

	y = -1;
	heh->temp = malloc(sizeof(heh->map) * (heh->map_height + 1));
	if (!heh->temp)
		error_handling(-1);
	heh->temp[heh->map_height] = NULL;
	while (++y < heh->map_height)
	{
		x = -1;
		heh->temp[y] = malloc(heh->map_width + 2);
		if (!heh->temp[y])
			error_handling(-1);
		heh->temp[y][heh->map_width + 1] = '\0';
		while (++x < heh->map_width + 1)
		{
			heh->temp[y][x] = heh->map[y][x];
			if (heh->map[y][x] == 'P')
			{
				heh->x = x;
				heh->y = y;
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
				heh->exit++;
			else if (heh->map[i][j] == 'C')
				heh->collectibles++;
		}
	}
	if (is_player != 1 || heh->exit != 1 || !heh->collectibles)
	{
		free_map(heh->map_height, heh);
		error_handling(4);
	}
	heh->x = 0;
	heh->y = 0;
}

void	check_map_walls_and_create_array(char *str, int fd, t_game *heh)
{
	int	i;

	i = 0;
	heh->map = NULL;
	fd = open(str, O_RDONLY);
	heh->map = malloc(sizeof(char *) * (heh->map_height + 1));
	if (fd < 0 || !heh->map)
		error_handling(1);
	heh->map[heh->map_height] = NULL;
	while (1)
	{
		heh->map[i] = get_next_line(fd);
		if (!heh->map[i])
			break ;
		if (((!i || i == heh->map_height - 1) && (heh->map_width != ft_strspn(heh->map[i], "1")))
			|| heh->map_width != ft_strspn(heh->map[i], "01CEP"))
		{
			free_map(i + 1, heh);
			error_handling(3);
		}
		i++;
	}
	close(fd);
	heh->collectibles = 0;
	heh->exit = 0;
}

char	*check_map_name_and_length(char *str, int fd, t_game *heh)
{
	char	*buffer;

	if (ft_strlen(str, 0) < 4 || 
		ft_strcmp(str + (ft_strlen(str, 0) - 4), ".ber"))
		error_handling(0);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		error_handling(1);
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
			error_handling(3);
		}
		free(buffer);
	}
	close(fd);
	return (buffer);
}

void  flood_fill(int x, int y, t_game *heh)
{
	if (x >= heh->map_width || x < 0
	 || y >= heh->map_height || y < 0
	 || heh->map[y][x] == '1'
	 || heh->map[y][x] == 'F')
		return ;
	if (heh->map[y][x] == 'C')
		heh->collectibles--;
	else if (heh->map[y][x] == 'E')
		heh->exit--;
	heh->map[y][x] = 'F';
	flood_fill(x - 1, y, heh);
	flood_fill(x + 1, y, heh);
	flood_fill(x, y + 1, heh);
	flood_fill(x, y - 1, heh);
}

void	pf(char **map, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		prt("%i:%s", i, map[i]);
	prt("\n\n");
}

void	game_init(char *str, t_game *heh)
{
	char	*buffer;

	heh->map_height = 0;
	buffer = check_map_name_and_length(str, 0, heh);
	if ((!buffer && !heh->map_height) || (heh->map_height < 3 || heh->map_width < 3))
		error_handling(2);
	check_map_walls_and_create_array(str, 0, heh);
	check_map(heh, 0);
	copy_map_to_temp(heh);
	flood_fill(heh->x, heh->y, heh);
	free_map(heh->map_height, heh);
	heh->map = heh->temp;
	if (heh->collectibles != 0 || heh->exit != 0)
	{
		free_map(heh->map_height, heh);
		error_handling(5);
	}
	// temp begin
	heh->mlx = mlx_init();
	heh->win = mlx_new_window(heh->mlx, 1, 1, "So long n thank you for all the fish");
	heh->p_image.img = mlx_xpm_file_to_image(heh->mlx, heh->path, &heh->p_image.width, &heh->p_image.height);
	heh->win_width = heh->p_image.width * heh->map_width; // 64
	heh->win_height = heh->p_image.height * heh->map_height;
	mlx_destroy_image(heh->mlx, heh->p_image.img);
	mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free(heh->mlx);
	// temp end
}

// to-do:
// make game work (player is black and move stuff)
int	main(void)
{
	static t_game	heh;
	char			*map_name;

	heh.path = "./xpm/tile.xpm";
	// map_name = ".ber"; // Invalid map (walls not 1)
	// map_name = ".bera"; // Invalid map name
	// map_name = ".baer"; // "
	// map_name = "asd.ber"; // File doesn't exist
	// map_name = ".ber.ber"; // invalid map size (little)
	// map_name = "maps/.ber"; // Invalid map (less walls)
	// map_name = "maps/.ber.ber"; // empty file (invalid map size)
	map_name = "asd/a/s/.ber.ber"; // everything right
	game_init(map_name, &heh);
	// if (ac != 2 || !game_init(av[1], &heh))
	// 	error_handling(-1);
	// int s = 900;
	// heh.win_width = s;
	// heh.win_height = s;
	heh.mlx = mlx_init();
	heh.win = mlx_new_window(heh.mlx, heh.win_width, heh.win_height, "So long n thank you for all the fish");

	int y = 0, x = 0;
	heh.p_image.img = mlx_xpm_file_to_image(heh.mlx, heh.path, &heh.p_image.width, &heh.p_image.height);
	while (y < heh.win_height - heh.p_image.height + 1)
	{
		while (x < heh.win_width - heh.p_image.width + 1)
		{
			if (heh.x != x/heh.p_image.width || heh.y != y/heh.p_image.height)
				mlx_put_image_to_window(heh.mlx, heh.win, heh.p_image.img, x, y);
			x += heh.p_image.width;
		}
		x = 0;
		y += heh.p_image.height;
	}
	free_map(heh.map_height, &heh);
	// rgbc_init(&heh);
	// mlx_loop_hook(heh.mlx, rbgc, &heh);
	// fti_init(&heh);
	// mlx_loop_hook(heh.mlx, fti, &heh);
	mlx_hook(heh.win, 2, 1L<<0, key_hook, &heh);
	mlx_hook(heh.win, 17, 0, quit, &heh);
	mlx_loop(heh.mlx);
	return (0);
}
/* x Width Largura, y Length Comprimento and y Height Altura
// fold all: Ctrl + K Ctrl + 1

	// heh.p_image.img = mlx_new_image(heh.mlx, heh.win_width, heh.win_height);
	// heh.p_image.addr = mlx_get_data_addr(heh.p_image.img, 
	// 		&heh.p_image.bits_per_pixel, &heh.p_image.line_length, 
	// 		&heh.p_image.endian);
	// heh.p_image.width = heh.win_width;
	// heh.p_image.height = heh.win_height;
	// mlx_put_image_to_window(heh.mlx, heh.win, heh.p_image.img, 0, 0);
	// mlx_destroy_image(heh.mlx, heh.p_image.img);

	// put_grad_square(&heh.p_image, 5, 0, heh.win_width - 5, heh.win_height - 5, 0); heh.win_width = 1400;
	// mlx_string_put(heh.mlx, heh.win, 100, 500, argb(0, 255, 255, 255), "Howdy people!");

	exit(0);
*/
