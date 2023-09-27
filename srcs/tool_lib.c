/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealex <andrealex@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:16:37 by analexan          #+#    #+#             */
/*   Updated: 2023/09/26 22:02:25 by andrealex        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	pn(int num)
{
	if (num < 0)
	{
		write(1, "-", 1);
		if (num == -2147483648)
		{
			write(1, "2", 1);
			num = -147483648;
		}
		num = -num;
	}
	if (num > 9)
		pn(num / 10);
	write(1, &"0123456789"[num % 10], 1);
}

void	ps(char *str, int mode)
{
	if (!str)
	{
		write(1, "(null)", 6);
		return ;
	}
	if (!mode)
		while (*str)
			write(1, str++, 1);
	else
		write(1, &str, 1);
}

void	prt(char *string, ...)
{
	va_list	args;
	int		i;

	va_start(args, string);
	i = 0;
	while (string[i])
	{
		if (string[i] == '%')
		{
			i++;
			if (string[i] == 'i')
				pn(va_arg(args, int));
			else if (string[i] == 's')
				ps(va_arg(args, char *), 0);
			else if (string[i] == 'c')
				ps(va_arg(args, char *), 1);
			i++;
		}
		else
			write(1, &string[i++], 1);
	}
	va_end(args);
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
