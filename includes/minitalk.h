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
void	bit_handler(int pid, char c);
void	error_signal(void);
void	signal_handler_s(int sig);

/*server.c*/
void	signal_handler(int sig, siginfo_t *info, void *context);
void	terminate(int sig);

#endif