/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/08/29 17:55:14 by andrealex        ###   ########.fr       */
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
		(*heh).y -= 10;
	else if (keycode == LEFT_KEY || keycode == A_KEY)
		(*heh).x -= 10;
	else if (keycode == RIGHT_KEY || keycode == D_KEY)
		(*heh).x += 10;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		(*heh).y += 10;
	if (keycode < 32 || keycode > 126)
		prt("keycode: %i = NULL\n", keycode);
	else
		prt("keycode: %i = '%c'\n", keycode, keycode);
	return (0);
}

void	rgbc_init(t_game *heh)
{
	heh->r = 255;
	heh->b = 0;
	heh->g = 0;
	heh->p_image.img = mlx_new_image(heh->mlx, heh->win_width, heh->win_height);
	heh->p_image.addr = mlx_get_data_addr(heh->p_image.img, 
			&heh->p_image.bits_per_pixel, &heh->p_image.line_length, 
			&heh->p_image.endian);
	heh->p_image.width = heh->win_width;
	heh->p_image.height = heh->win_height;
}

int	rbgc(t_game *heh)
{
	int	millisecond;

	millisecond = 1000;
	put_square(&heh->p_image, 0, 0, heh->win_width - 1, heh->win_height - 1, 0, 
		argb(0, heh->r, heh->g, heh->b));
	put_circle(&heh->p_image, heh->x, heh->y, 30, 0, 0);
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, 0, 0);
	if (heh->r == 255 && heh->g < 255 && heh->b == 0)
		heh->g++;
	else if (heh->g == 255 && heh->r > 0)
		heh->r--;
	else if (heh->g == 255 && heh->b < 255)
		heh->b++;
	else if (heh->b == 255 && heh->g > 0)
		heh->g--;
	else if (heh->b == 255 && heh->r < 255)
		heh->r++;
	else if (heh->r == 255 && heh->b > 0)
		heh->b--;
	usleep(millisecond * 10);
	return (0);
}

void	fti_init(t_game *heh)
{
	heh->p_image.img = mlx_xpm_file_to_image(heh->mlx, "./xpm/tile.xpm", 
			&heh->p_image.width, &heh->p_image.height);
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, 
		heh->x - 64, heh->y - 64);
}

int	fti(t_game *heh)
{
	int	millisecond;

	millisecond = 1000;
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, 
		heh->x - 64, heh->y - 64);
	usleep(millisecond * 10);
	return (0);
}

void	p(int x, int y)
{
	prt("n1: %i, n2: %i\n", x, y);
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
		prt("Character/exit is not 1 || no collectibles\n");
	else if (error == 5)
		prt("Other error\n");
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
	free(heh->map);
}

		// prt("map[%i]: %s\n", i, heh->map[i]);
void	check_map_stuff(t_game *heh, int is_player, int is_exit)
{
	int	i;
	int	j;

	i = -1;
	while (++i < heh->y)
	{
		j = -1;
		while (!(!i || i == heh->y - 1) && ++j < heh->x)
		{
			if (heh->map[i][j] == 'P')
				is_player++;
			else if (heh->map[i][j] == 'E')
				is_exit++;
			else if (heh->map[i][j] == 'C')
				heh->collectibles++;
		}
	}
	if (is_player != 1 || is_exit != 1 || !heh->collectibles)
	{
		free_map(heh->y, heh);
		error_handling(4);
	}
}

void	check_map_walls_and_create_array(char *str, int *fd, t_game *heh)
{
	int	i;

	i = 0;
	heh->map = NULL;
	*fd = open(str, O_RDONLY);
	heh->map = malloc(sizeof(char *) * (heh->y + 1));
	if (*fd < 0 || !heh->map)
		error_handling(1);
	heh->map[heh->y] = NULL;
	while (1)
	{
		heh->map[i] = get_next_line(*fd);
		if (!heh->map[i])
			break ;
		if (((!i || i == heh->y - 1) && (heh->x != ft_strspn(heh->map[i], "1")))
			|| heh->x != ft_strspn(heh->map[i], "01CEP"))
		{
			free_map(i + 1, heh);
			error_handling(3);
		}
		i++;
	}
	close(*fd);
	heh->collectibles = 0;
}

char	*check_map_name_and_length(char *str, int *fd, t_game *heh)
{
	char	*buffer;

	if (ft_strlen(str, 0) < 4 || 
		ft_strcmp(str + (ft_strlen(str, 0) - 4), ".ber"))
		error_handling(0);
	*fd = open(str, O_RDONLY);
	if (*fd < 0)
		error_handling(1);
	while (1)
	{
		buffer = get_next_line(*fd);
		if (!buffer)
			break ;
		if (!(heh->y)++)
			heh->x = ft_strlen(buffer, 1);
		if (ft_strlen(buffer, 1) != heh->x || *buffer != '1' 
			|| buffer[ft_strlen(buffer, 1) - 1] != '1')
		{
			free(buffer);
			error_handling(3);
		}
		free(buffer);
	}
	close(*fd);
	return (buffer);
}

void  flood_fill(int x, int y, t_game *heh)
{
	if (x >= heh->x || x < 0
	 || y >= heh->y || y < 0
	 || heh->map[y][x] != '1') // to search for
		return ;
	heh->map[y][x] = '1'; // change to this
	flood_fill(x - 1, y, heh);
	flood_fill(x + 1, y, heh);
	flood_fill(x, y + 1, heh);
	flood_fill(x, y - 1, heh);
}
// game_init

void	check_map(char *str, t_game *heh)
// void	game_init(char *str, t_game *heh)
{
	char	*buffer;
	int		fd;

	heh->y = 0;
	buffer = check_map_name_and_length(str, &fd, heh);
	if ((!buffer && !heh->y) || (heh->y < 3 || heh->x < 3))
		error_handling(2);
	check_map_walls_and_create_array(str, &fd, heh);
	check_map_stuff(heh, 0, 0);

	heh->temp = heh->map;
	int	i = -1;
	while (++i < heh->y)
		prt("%i:%s", i, heh->map[i]);
	prt("\n\n");
	flood_fill(0, 0, heh);
	i = -1;
	while (++i < heh->y)
		prt("%i:%s", i, heh->map[i]);

	// temp begin
	heh->mlx = mlx_init();
	heh->win = mlx_new_window(heh->mlx, 1, 1, "So long n thank you for all the fish");
	heh->p_image.img = mlx_xpm_file_to_image(heh->mlx, heh->path, &heh->p_image.width, &heh->p_image.height);
	heh->win_width = heh->p_image.width * heh->x;
	heh->win_height = heh->p_image.height * heh->y;
	mlx_destroy_image(heh->mlx, heh->p_image.img);
	mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free(heh->mlx);
	// temp end
}

// to-do:
// valid paths from character to exit/collectibles (flood_fill checks)
// make all sprites 64/64 (box:56/60)
int	main(void)
{
	static t_game	heh;

	heh.path = "./xpm/tile.xpm";
	// heh.path = "./xpm/tiles/tile60.xpm";
	// heh.path = "./xpm/tiles/tile61.xpm";
	// game_init();
	// check_map(".ber", &heh); // Invalid map (walls not 1)
	// check_map(".bera", &heh); // Invalid map name
	// check_map(".baer", &heh); // "
	// check_map("asd.ber", &heh); // File doesn't exist
	// check_map(".ber.ber", &heh); // invalid map size (little)
	// check_map("maps/.ber", &heh); // Invalid map (less walls)
	// check_map("maps/.ber.ber", &heh); // empty file (invalid map size)
	check_map("asd/a/s/.ber.ber", &heh); // everything right
	free_map(heh.y, &heh);
	// if (ac != 2 || !checkmap(av[1], &heh))
	// 	error_handling(-1);
	// int s = 900;
	// heh.win_width = s; // x
	// heh.win_height = s; // y
	heh.mlx = mlx_init();
	heh.win = mlx_new_window(heh.mlx, heh.win_width, heh.win_height, "So long n thank you for all the fish");

	// heh.p_image.img = mlx_new_image(heh.mlx, heh.win_width, heh.win_height);
	// heh.p_image.addr = mlx_get_data_addr(heh.p_image.img, 
	// 		&heh.p_image.bits_per_pixel, &heh.p_image.line_length, 
	// 		&heh.p_image.endian);
	// heh.p_image.width = heh.win_width;
	// heh.p_image.height = heh.win_height;
	// put_square(&heh.p_image, 0, 0, heh.win_width - 1, heh.win_height - 1, 0, 255);
	// mlx_put_image_to_window(heh.mlx, heh.win, heh.p_image.img, 0, 0);
	// mlx_destroy_image(heh.mlx, heh.p_image.img);
	// put_line(&heh.p_image, 0, 0, s, s, argb(0, 255, 255, 255));
	// put_line(&heh.p_image, 3, 3, 4, 4, 65000);
	// put_square(&heh.p_image, 0, 0, 2, 2, 0, argb(0, 255, 255, 255));
	// put_square(&heh.p_image, 3, 3, heh.win_width - 1, heh.win_height - 1, 0, 65000);
	// mlx_put_image_to_window(heh.mlx, heh.win, heh.p_image.img, 0, 0);

	int y = 0, x = 0;
	heh.p_image.img = mlx_xpm_file_to_image(heh.mlx, heh.path, &heh.p_image.width, &heh.p_image.height);
	while (y < heh.win_height - heh.p_image.height + 1)
	{
		while (x < heh.win_width - heh.p_image.width + 1)
		{
			mlx_put_image_to_window(heh.mlx, heh.win, heh.p_image.img, x, y);
			x += heh.p_image.width;
		}
		x = 0;
		y += heh.p_image.height;
	}

	// heh.x = heh.win_width / 2;
	// heh.y = heh.win_height / 2;
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
// fold all: Ctrl + K Ctrl + 0
	// put_grad_square(&heh.p_image, 5, 0, heh.win_width - 5, heh.win_height - 5, 0); heh.win_width = 1400;
	// mlx_string_put(heh.mlx, heh.win, 100, 500, argb(0, 255, 255, 255), "Howdy people!");

	// check_map(".ber", &heh); // Invalid map (walls not 1)
	// check_map(".bera", &heh); // Invalid map name
	// check_map(".baer", &heh); // "
	// check_map("asd.ber", &heh); // File doesn't exist
	// check_map(".ber.ber", &heh); // invalid map size (little)
	// check_map("maps/.ber", &heh); // Invalid map (less walls)
	// check_map("maps/.ber.ber", &heh); // empty file (invalid map size)
	check_map("asd/a/s/.ber.ber", &heh); // everything right
	// free_map(map);
	exit(0);
*/
