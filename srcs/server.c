/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbedouan <nbedouan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:55:59 by nbedouan          #+#    #+#             */
/*   Updated: 2025/03/22 17:59:31 by nbedouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	filler(int sig, int *bit, char *str)
{
	static char	c = 0;

	if (sig == SIGUSR1)
		c |= (1 << (7 - *bit));
	(*bit)++;
	if (*bit == 8)
	{
		ft_strcat(str, c);
		*bit = 0;
		c = 0;
	}
}

void	print_reset(char **str, int *bit, int *len, int *received)
{
	ft_putendl_fd(*str, 1);
	*bit = 0;
	*len = 0;
	*received = 0;
	free(*str);
	*str = NULL;
}

void	signal_handler_bis(char *str, int *bit, int *len, int *received)
{
	static int	char_count = 0;

	if (*bit == 0 && received)
	{
		char_count++;
		if (char_count == *len)
		{
			print_reset(&str, bit, len, received);
			char_count = 0;
		}
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static int	received = 0;
	static int	len = 0;
	static char	*str = NULL;

	(void)context;
	if (!received)
	{
		get_len(sig, &bit, &len, &received);
		if (received == 1)
		{
			str = ft_calloc(len + 1, sizeof(char));
			if (!str)
				exit(1);
		}
	}
	else if (str != NULL)
	{
		filler(sig, &bit, str);
		signal_handler_bis(str, &bit, &len, &received);
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	signal(SIGINT, terminate);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 \
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error setting up signal handlers\n", 2);
		return (1);
	}
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
}
