/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:28 by gustoliv          #+#    #+#             */
/*   Updated: 2025/06/24 13:36:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

void	handler(int sig)
{
	static char	c;
	static int i = 7;

	if (sig == SIGUSR1)
		c |= (0 << i);
	if (sig == SIGUSR2)
		c |= (1 << i);
	if (i-- == 0)
	{
		ft_printf("%c", c);
		c = 0;
		i = 7;
	}
}

int main(void)
{
	int pid;

	pid = getpid();
	ft_printf("----------------------------------\n", pid);
	ft_printf("               SERVER            \n", pid);
	ft_printf("----------------------------------\n", pid);
	ft_printf("Process ID: %d\n Mensage:", pid);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}

