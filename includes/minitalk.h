/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbedouan <nbedouan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:54:40 by nbedouan          #+#    #+#             */
/*   Updated: 2025/03/22 20:36:38 by nbedouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "./libft/libft.h"

/*client.c*/
void	send_char(int pid, char *str);
void	error_signal(void);
void	signal_received(int sig);
void	send_len(int pid, int len);

/*server.c*/
void	signal_handler(int sig, siginfo_t *info, void *context);
void	terminate(int sig);

void	ft_strcat(char *str, char c);
void	filler(int sig, int *bit, char *str);
void	get_len(int sig, int *bit, int *len, int * received);
void	print_reset(char **str, int *bit, int *len, int *received);

#endif