/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:16:37 by analexan          #+#    #+#             */
/*   Updated: 2023/09/20 17:39:49 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

long	stol(char *str)
{
	long	num;
	int		mc;

	mc = 1 - 2 * (*str == '-' && *str++);
	num = 0;
	while (*str)
		num = num * 10 + *str++ - 48;
	return (num * mc);
}

int	stoi(char *str)
{
	int		num;
	int		mc;

	mc = 1 - 2 * (*str == '-' && *str++);
	num = 0;
	while (*str)
		num = num * 10 + *str++ - 48;
	return (num * mc);
}

void	pn(int num)
{
	if (num < 0)
	{
		wwrite(1, "-", 1);
		if (num == -2147483648)
		{
			wwrite(1, "2", 1);
			num = -147483648;
		}
		num = -num;
	}
	if (num > 9)
		pn(num / 10);
	wwrite(1, &"0123456789"[num % 10], 1);
}

void	ps(char *str, int mode)
{
	if (!str)
	{
		wwrite(1, "(null)", 6);
		return ;
	}
	if (!mode)
		while (*str)
			wwrite(1, str++, 1);
	else
		wwrite(1, &str, 1);
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
			wwrite(1, &string[i++], 1);
	}
	va_end(args);
}
