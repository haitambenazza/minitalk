/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:28:22 by hbenazza          #+#    #+#             */
/*   Updated: 2023/12/23 13:04:26 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_str = 0;

int	ft_atoi(char *str)
{
	int			sign;
	long long	number;
	size_t		i;

	sign = 1;
	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

void	new_line(int pid)
{
	int	j;
	int	bit;

	j = 7;
	bit = 0;
	while (j >= 0)
	{
		bit = '\n' >> j;
		if (bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		j--;
		usleep(150);
	}
}

void	send(char *msg, int pid)
{
	size_t	i;
	int		j;
	int		bit;
	int		ascii;

	i = 0;
	while (msg[i] != '\0')
	{
		j = 7;
		bit = 0;
		ascii = msg[i];
		while (j >= 0)
		{
			bit = ascii >> j;
			if (bit & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
			usleep(150);
		}
		i++;
	}
	new_line(pid);
}

void	handler(int s)
{
	if (s == SIGUSR1 || s == SIGUSR2)
		write(1, "Message received by the server\n", 32);
	exit(1);
}

int	main(int co, char **v)
{
	int	pid;
	int	i;

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	if (co != 3)
		return (write(1, "USAGE:./client [PI] [msg]\n", 26), 1);
	i = 0;
	pid = ft_atoi(v[1]);
	while (v[1][i])
	{
		if (v[1][i] < '0' || v[1][i] > '9')
			return (write(1, "USAGE:./client [PID] [msg]\n", 27), 1);
		i++;
	}
	send(v[2], pid);
	while (1)
	{
		pause();
	}
	return (0);
}
