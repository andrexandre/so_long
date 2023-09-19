/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_lib2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:23:43 by analexan          #+#    #+#             */
/*   Updated: 2023/09/18 11:28:58 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_abs(int x)
{
	if (x < 0)
		return -x;
	return x;
}

// error_handling(-1); = Failed to open/read /dev/urandom
int rng(int min, int max)
{
	int		randomData;
	int		urandom_fd;
	ssize_t	bytesRead;

	randomData = 0;
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		error_handling(-1);
	bytesRead = read(urandom_fd, &randomData, sizeof(randomData));
	if (bytesRead < 0)
		error_handling(-1);
	close(urandom_fd);
	return ((ft_abs(randomData) % (max - min + 1)) + min);
}
