/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbedouan <nbedouan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:37:01 by nbedouan          #+#    #+#             */
/*   Updated: 2025/03/24 20:37:10 by nbedouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	terminate(int sig)
{
	(void)sig;
	ft_putstr_fd("\nServer terminated\n", 1);
	exit(0);
}

void	ft_strcat(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
	str[i + 1] = '\0';
}

void	get_len(int sig, int *bit, int *len, int *received)
{
	if (sig == SIGUSR1)
		*len |= 1 << *bit;
	(*bit)++;
	if (*bit == 32)
	{
		*bit = 0;
		*received = 1;
	}
}

void	error_signal_utils(void)
{
	ft_putendl_fd("Error", 2);
	exit(1);
}
