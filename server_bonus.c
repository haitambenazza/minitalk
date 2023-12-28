/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:28:19 by hbenazza          #+#    #+#             */
/*   Updated: 2023/12/23 14:29:35 by hbenazza         ###   ########.fr       */
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

void	send(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void	handler(int s, siginfo_t *siginfo, void *context)
{
	static int	i;
	int			tmp;

	tmp = 0;
	(void)context;
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
		if (g_str == '\n')
			send(siginfo->si_pid);
		g_str = 0;
		i = 0;
		return ;
	}
	i++;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	write(1, "WELCOME TO MINITALK\n", 20);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
