/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:28 by gustoliv          #+#    #+#             */
/*   Updated: 2025/07/16 23:35:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <signal.h>

void	make_string(int *number, char c, int *count)
{
	static char	*str = NULL;
	static int	i = 0;

	if (!str)
	{
		str = malloc(*number + 1);
		if (!str)
			exit(1);
	}

	if (i < *number)
		str[i++] = c;
	if (i == *number)
	{
		str[i] = '\0';
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
		*count = 31;
		*number = 0;
		i = 0;
	}
}

static void	handler(int sig, siginfo_t *info)
{
	static char	c = 0;
	static int number = 0;
	static int count = 31;
	static int i = 7;

	if (count >= 0)
	{
		if (sig == SIGUSR2)
			number |= (1 << count);
		count--;
	}
	else
	{
		if (sig == SIGUSR2)
			c |= (1 << i);
		if (i-- == 0)
		{
			make_string(&number, c, &count);
			c = 0;
			i = 7;
		}
	}
	kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	int pid;
	struct sigaction sa;

	sa.sa_sigaction = (void *)handler;
	sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_printf("----------------------------------\n", pid);
	ft_printf("               SERVER            \n", pid);
	ft_printf("----------------------------------\n", pid);
	ft_printf("Process ID: %d\n Mensage:", pid);
	sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
