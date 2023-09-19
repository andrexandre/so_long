/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:20:32 by analexan          #+#    #+#             */
/*   Updated: 2023/09/16 12:24:32 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
