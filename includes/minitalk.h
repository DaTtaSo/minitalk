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

/*client*/
void	send_str(int pid, char *str);
void	signal_received(int sig);
void	send_len(int pid, unsigned int len);
void	error_signal(int sig_num, int pid);

/*server*/
void	signal_handler(int sig, siginfo_t *info, void *context);
void	terminate(int sig);
void	filler(int sig, int *bit, char *str);
void	sig_handler_b(char *str, int *bit, unsigned int *len, int *received);

/*utils*/
void	error_signal_utils(void);
void	ft_strcat(char *str, char c);
void	get_len(int sig, int *bit, unsigned int *len, int *received);
void	print_reset(char **str, int *bit, unsigned int *len, int *received);

#endif