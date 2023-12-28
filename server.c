/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:51:03 by hbenazza          #+#    #+#             */
/*   Updated: 2023/12/23 12:57:24 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_str = 0;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -(n);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + 48);
}

void	handler(int s)
{
	static int	i = 0;
	int			tmp;

	tmp = 0;
	if (s == SIGUSR1)
	{
		tmp = g_str << 1;
		g_str = tmp | 1;
	}
	else if (s == SIGUSR2)
	{
		g_str = g_str << 1;
	}
	if (i == 7)
	{
		write(1, &g_str, 1);
		g_str = 0;
		i = 0;
		return ;
	}
	i++;
}

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "WELCOME TO MINITALK\n", 20);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
