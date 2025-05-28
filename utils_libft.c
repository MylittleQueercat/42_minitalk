/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:12:41 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/28 10:17:16 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *s)
{
	int	v;
	int	res;
	int	sign;

	v = 0;
	res = 0;
	sign = 1;
	if (s[v] == '-')
	{
		sign = -1;
		v++;
	}
	while (s[v] >= '0' && s[v] <= '9')
	{
		res = res * 10 + s[v] - '0';
		v++;
	}
	return (sign * res);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	v;

	v = 0;
	while (s[v])
		v++;
	write(fd, s, v);
}

void	ft_putnbr(int n)
{
	if (n < 0)
		write (1, "-", 1);
	if (n > 9 || n < -9)
	{
		if (n < 0)
			ft_putnbr(n / (-10));
		else
			ft_putnbr(n / 10);
	}
	if (n < 0)
		write (1, &"0123456789"[-(n % 10)], 1);
	else
		write (1, &"0123456789"[n % 10], 1);
}
