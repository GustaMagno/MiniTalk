/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:28 by gustoliv          #+#    #+#             */
/*   Updated: 2025/07/17 14:07:58 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <signal.h>

int	make_string(t_variables *v,  siginfo_t *info)
{
	static int	i = 0;

	if (!v->str)
	{
		v->str = malloc(v->number + 1);
		if (!v->str)
			exit(1);
	}
	if (i < v->number)
		v->str[i++] = v->c;
	v->c = 0;
	v->i = 7;
	if (i == v->number)
	{
		v->str[i] = '\0';
		ft_printf("%s\n", v->str);
		free(v->str);
		v->str = NULL;
		v->count = 31;
		v->number = 0;
		i = 0;
		return (1);
	}
	return (0);
}

static void	handler(int sig, siginfo_t *info)
{
	static t_variables v = (t_variables){.c=0, .count=31, .number=0, .i=7};

	if (v.count >= 0)
		v.number |= ((sig == SIGUSR2) << v.count--);
	else
	{
		if (sig == SIGUSR2)
			v.c |= (1 << v.i);
		if (v.i-- == 0)
		{
			if (make_string(&v, info))
			{			
				kill(info->si_pid, SIGUSR2);
				return;
			}
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
