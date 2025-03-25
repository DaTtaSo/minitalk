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

void	signal_received(int sig)
{
	if (sig == SIGUSR1)
		__atomic_store_n(&g_signal_received, 1, __ATOMIC_RELEASE);
}

void	error_signal(int sig_num, int pid)
{
	if (sig_num == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
			error_signal_utils();
	}
	if (sig_num == 2)
	{
		if (kill(pid, SIGUSR2) == -1)
			error_signal_utils();
	}
}

void	send_len(int pid, int len)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		g_signal_received = 0;
		if ((len & (1 << i)))
		{
			if (kill(pid, SIGUSR1) == -1)
				error_signal_utils();
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error_signal_utils();
		}
		while (!__atomic_load_n(&g_signal_received, __ATOMIC_ACQUIRE))
			usleep(100);
		i++;
	}
}

void	send_str(int pid, char *str)
{
	int	bit;
	int	i;

	i = 0;
	while (str[i])
	{
		bit = 7;
		while (bit >= 0)
		{
			g_signal_received = 0;
			if ((str[i] & (1 << bit)))
				error_signal(1, pid);
			else
				error_signal(2, pid);
			while (!__atomic_load_n(&g_signal_received, __ATOMIC_ACQUIRE))
				usleep(100);
			bit--;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

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
	sa.sa_handler = signal_received;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	send_len(pid, ft_strlen(av[2]));
	send_str(pid, av[2]);
	send_str(pid, "\0");
	return (0);
}
