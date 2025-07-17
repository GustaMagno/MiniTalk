/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:08:04 by gustoliv          #+#    #+#             */
/*   Updated: 2025/06/19 22:40:09 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# define HEX_U "0123456789ABCDEF"
# define HEX_L "0123456789abcdef"
# define SIGUSR1 10
# define SIGUSR2 12

typedef unsigned long long	t_ll;

int			ft_printf(const char *str, ...);
void		send_bit(int pid, char c);
void		handler_ack(int sig);
int			ft_atoi(const char *str);
void		send_len(int pid, char *s);
void		handler_ack(int sig);
typedef struct s_variables
{
	char	c;
	int number;
	int count;
	int i;
	 char	*str;
} t_variables;


#endif