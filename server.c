/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:28 by gustoliv          #+#    #+#             */
/*   Updated: 2025/07/09 14:11:32 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <signal.h>

void	make_string(int number, char c)
{
	static char	*str = NULL;
	static int i = 0;
	
	if (!str)
		str = malloc(number + 1);
	if (!str)
		exit(1);
	if (i < number)
		str[i++] = c;
	else if (i == number)
	{
		str[i] = '\0';
		ft_printf("%s", str);
		free(str);
	}
}



void	handler(int sig, siginfo_t *info, void *cpu)
{
	static char	c;
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
			make_string(number, c);
			c = 0;
			i = 7;
		}
	}
}

int main(void)
{
	int pid;
	struct sigaction sa;

	sa.sa_sigaction = handler;
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

