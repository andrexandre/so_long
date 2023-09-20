/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:20:32 by analexan          #+#    #+#             */
/*   Updated: 2023/09/20 17:39:59 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

// error_handling(-1); = Failed to open/read /dev/urandom
int	rng(int min, int max)
{
	int		random_data;
	int		urandom_fd;
	ssize_t	bytes_read;

	random_data = 0;
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		error_handling(-1);
	bytes_read = read(urandom_fd, &random_data, sizeof(random_data));
	if (bytes_read < 0)
		error_handling(-1);
	close(urandom_fd);
	return ((ft_abs(random_data) % (max - min + 1)) + min);
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

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	wwrite(int q, const void *w, size_t e)
{
	ssize_t	compatibility_for_my_ubuntu;

	compatibility_for_my_ubuntu = write(q, w, e);
	(void)compatibility_for_my_ubuntu;
}
