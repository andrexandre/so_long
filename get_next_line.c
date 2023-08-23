/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:44:07 by analexan          #+#    #+#             */
/*   Updated: 2023/08/23 18:51:16 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i + (s[i] == '\n'));
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	if (i == -1)
		i = 0;
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
		if (s2[j - 1] == '\n')
			break ;
	}
	str[i + j] = 0;
	return (str);
}

int	check_buffer(char *str)
{
	int	nl;
	int	i;
	int	j;

	nl = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (nl)
			str[j++] = str[i];
		if (str[i] == '\n')
			nl = 1;
		str[i++] = 0;
	}
	return (nl);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;

	if (read(fd, 0, 0) || BUFFER_SIZE < 1)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		return (NULL);
	}
	line = NULL;
	while (*buffer != 0 || read(fd, buffer, BUFFER_SIZE))
	{
		temp = line;
		line = ft_strjoin_gnl(line, buffer);
		free(temp);
		if (check_buffer(buffer))
			break ;
	}
	return (line);
}
/*
#include "get_next_line_utils.c"
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c && ./a.out
#include <stdio.h>
#include <fcntl.h>
void	gnl_tester(char *file, int lcnt)
{
	int		fd;
	char	*str;
	int		i;

	i = 1;
	if (!file || lcnt < 0)
		return ;
	fd = open(file, O_RDONLY);
	while (lcnt == 0 && (str = get_next_line(fd)))
	{
		printf("%i:\"%s\"\n", i, str);
		free(str);
		i++;
	}
	while (lcnt != 0 && i <= lcnt)
	{
		str = get_next_line(fd);
		printf("%i:\"%s\"\n", i, str);
		free(str);
		i++;
	}
	close(fd);
}
int main(void)
{
	gnl_tester("lines.txt", 0);
	return (0);
}
*/
