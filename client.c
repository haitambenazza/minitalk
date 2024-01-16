/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:51:06 by hbenazza          #+#    #+#             */
/*   Updated: 2023/12/23 14:47:19 by hbenazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		usleep(250);
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
			usleep(250);
		}
		i++;
	}
	new_line(pid);
}

int	main(int co, char **v)
{
	int		pid;
	size_t	i;

	if (co != 3)
	{
		write(1, "USAGE:./client [PID] [msg]\n", 27);
		return (1);
	}
	i = 0;
	while (v[1][i])
	{
		if (v[1][i] < '0' || v[1][i] > '9')
		{
			write(1, "BAD PID\n", 8);
			return (1);
		}
		i++;
	}
	pid = ft_atoi(v[1]);
	send(v[2], pid);
	return (0);
}
