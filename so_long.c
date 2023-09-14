/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:42:27 by analexan          #+#    #+#             */
/*   Updated: 2023/09/14 19:02:09 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(int len, t_game *heh)
{
	int	i;

	i = 0;
	while (i < len)
		free(heh->map[i++]);
	// i = 0;
	// while (i < len)
	// 	free(heh->temp_map[i++]);
	free(heh->map);
}

int	quit(t_game *heh)
{
	if (!heh->collectibles)
		prt("You win!\n");
	else
		prt("Exited Sucessfully!\n");
	if (!heh->p_image.is_created)
		mlx_destroy_image(heh->mlx, heh->p_image.img);
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
	if (heh)
		mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free_map(heh->map_height, heh);
	free(heh->mlx);
	exit(EXIT_SUCCESS);
}

void	create_image(int width, int height, int color, t_image *image, t_game *heh)
{
	image->width = width;
	image->height = height;
	image->img = mlx_new_image(heh->mlx, image->width, image->height);
	image->addr = mlx_get_data_addr(image->img, 
			&image->bits_per_pixel, &image->line_length, 
			&image->endian);
	put_square(image, 0, 0, image->width - 1, image->height - 1, 1, color);
	image->is_created = 0;
}

void	pf(char **map, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		prt("%i:%s", i, map[i]);
	prt("\n\n");
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
	int temp = c;
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
	str[temp] = 0;
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
	prt("%s\n", str);
	return (str);
}

int	key_hook(int keycode, t_game *heh)
{
	char	*str;
	int		pixels;
	int		t1;
	int		t2;

	pixels = 1;
	t1 = heh->x;
	t2 = heh->y;
	heh->moves++;
	if (keycode == ESC_KEY)
		return (quit(heh));
	if (keycode == UP_KEY || keycode == W_KEY)
		heh->y -= pixels;
	else if (keycode == LEFT_KEY || keycode == A_KEY)
		heh->x -= pixels;
	else if (keycode == RIGHT_KEY || keycode == D_KEY)
		heh->x += pixels;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		heh->y += pixels;
	if (heh->map[heh->y][heh->x] == '1')
	{
		heh->x = t1;
		heh->y = t2;
	}
	else if (heh->map[heh->y][heh->x] == 'C')
	{
		heh->map[heh->y][heh->x] = '0';
		heh->collectibles--;
	}
	else if (heh->map[heh->y][heh->x] == 'E' && !heh->collectibles)
		quit(heh);
	// if (keycode < 32 || keycode > 126)
	// 	prt("keycode: %i = NULL\n", keycode);
	// else
	// 	prt("keycode: %i = '%c'\n", keycode, keycode);
	mlx_put_image_to_window(heh->mlx, heh->win, heh->p_image.img, 0, 0);
	int y = 0, x = 0;
	while (y < heh->win_height - heh->wall_i.height + 1)
	{
		while (x < heh->win_width - heh->wall_i.width + 1)
		{
			if (heh->map[y/heh->wall_i.height][x/heh->wall_i.width] == '1')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->wall_i.img, x, y);
			else if (heh->map[y/heh->wall_i.height][x/heh->wall_i.width] == 'C')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->collec_i.img, x, y);
			else if (heh->map[y/heh->wall_i.height][x/heh->wall_i.width] == 'E')
				mlx_put_image_to_window(heh->mlx, heh->win, heh->exit_i.img, x, y);
			else
				mlx_put_image_to_window(heh->mlx, heh->win, heh->ground_i.img, x, y);
			if (heh->x == x/heh->wall_i.width && heh->y == y/heh->wall_i.height)
				mlx_put_image_to_window(heh->mlx, heh->win, heh->player_i.img, x, y);
			mlx_string_put(heh->mlx, heh->win, x + 32, y + 32, 0x00FFFFFF, 
				(char []){heh->map[y/heh->wall_i.height][x/heh->wall_i.width], '\0'});
			x += heh->wall_i.width;
		}
		x = 0;
		y += heh->wall_i.height;
	}
	str = ft_itoa(heh->moves);
	mlx_string_put(heh->mlx, heh->win, heh->win_width / 2, heh->win_height - 5, 0x00FFFFFF, "Moves: ");
	mlx_string_put(heh->mlx, heh->win, heh->win_width / 2 + 40, heh->win_height - 5, 0x00FFFFFF, str);
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
	heh->temp = heh->collectibles;
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
	heh->map = heh->temp_map;
	if (heh->collectibles != 0 || heh->exit != 0)
	{
		free_map(heh->map_height, heh);
		error_handling(5);
	}
	heh->collectibles = heh->temp;
	// calculate win_size
	heh->mlx = mlx_init();
	heh->win = mlx_new_window(heh->mlx, 1, 1, "So long n thank you for all the fish");
	heh->wall_i.img = mlx_xpm_file_to_image(heh->mlx, heh->path, &heh->wall_i.width, &heh->wall_i.height);
	heh->win_width = heh->wall_i.width * heh->map_width;
	heh->win_height = heh->wall_i.height * heh->map_height;
	// heh->wall_i.width must be 32
	mlx_destroy_image(heh->mlx, heh->wall_i.img);
	mlx_destroy_window(heh->mlx, heh->win);
	mlx_destroy_display(heh->mlx);
	free(heh->mlx);
}

// to-do:
// change from 64 to 32
// make game work (make textures)
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
	// map_name = "asd/a/s/.ber.ber"; // everything right
	map_name = "maps/test.ber"; // everything right
	game_init(map_name, &heh);
	// if (ac != 2 || !game_init(av[1], &heh))
	// 	error_handling(0);
	// int s = 900;
	// heh.win_width = s;
	// heh.win_height = s;
	heh.mlx = mlx_init();
	heh.win = mlx_new_window(heh.mlx, heh.win_width, heh.win_height, "So long n thank you for all the fish");

	create_image(heh.win_width, heh.win_height, 255, &heh.p_image, &heh);
	create_image(64, 64, argb(0, 128, 64, 0), &heh.wall_i, &heh);
	create_image(64, 64, argb(0, 0, 255, 0), &heh.ground_i, &heh);
	create_image(64, 64, argb(0, 255, 255, 50), &heh.collec_i, &heh);
	create_image(64, 64, argb(0, 255, 0, 0), &heh.exit_i, &heh);
	create_image(64, 64, argb(0, 255, 255, 255), &heh.player_i, &heh);
	// change 64 to 32
	heh.moves = -1;
	key_hook(0, &heh);
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

	// put_grad_square(&heh.p_image, 5, 0, heh.win_width - 5, heh.win_height - 5, 0);
	// mlx_string_put(heh.mlx, heh.win, 100, 500, argb(0, 255, 255, 255), "Howdy people!");
	// heh.wall_i.img = mlx_xpm_file_to_image(heh.mlx, heh.path, &heh.wall_i.width, &heh.wall_i.height);

	exit(0);
*/
