/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbedouan <nbedouan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:25:23 by nbedouan          #+#    #+#             */
/*   Updated: 2025/03/22 20:36:38 by nbedouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t	g_signal_received = 0;

void	signal_handler_s(int sig)
{
	if (sig == SIGUSR1)
	{
		g_signal_received = 1;
	}
}

void	bit_handler(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_signal_received = 0;
		if ((c & (1 << bit)) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putendl_fd("Error while sending SIGUSR1", 2);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putendl_fd("Error while sending SIGUSR2", 2);
				exit(1);
			}
		}
		while (!g_signal_received)
			usleep(100);
		bit--;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3 || !ft_strlen(av[2]))
	{
		ft_putendl_fd("Error: format is wrong", 2);
		ft_putendl_fd("try typing: ./client <PID> <message>", 2);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 1)
	{
		ft_putendl_fd("invalid PID, must be greater than 1", 2);
		return (1);
	}
	i = 0;
	signal(SIGUSR1, signal_handler_s);
	while (av[2][i] != '\0')
	{
		bit_handler(pid, av[2][i]);
		i++;
	}
	bit_handler(pid, '\0');
	return (0);
}
