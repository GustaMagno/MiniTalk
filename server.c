/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:28 by gustoliv          #+#    #+#             */
/*   Updated: 2025/07/03 15:28:26 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <signal.h>

char	*ft_strjoin(char *s1, char *s2, char *s1_temp)
{
	char		*str;
	size_t		i;
	size_t		j;
	char		*temp;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2[j] != '\n' && s2[j])
		j++;
	str = malloc((i + j + 1 + (s2[j] == '\n')) * sizeof(char));
	if (!str)
		return (NULL);
	temp = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (*s2 && *s2 != '\n')
		*str++ = *s2++;
	if (*s2 == '\n')
		*str++ = '\n';
	free(s1_temp);
	*str = '\0';
	return (temp);
}

void	handler(int sig, siginfo_t *info, void *cpu)
{
	static char	c;
	static int number = 0;
	static int count = 0;
	static int i = 7;

	if (count < 32 && count++)
	{
		if (sig == SIGUSR1)
			number |= (0 << i);
		if (sig == SIGUSR2)
			number |= (1 << i);
	}
	else
	{
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
}

int main(void)
{
	int pid;
	struct sigaction sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
	pid = getpid();
	ft_printf("----------------------------------\n", pid);
	ft_printf("               SERVER            \n", pid);
	ft_printf("----------------------------------\n", pid);
	ft_printf("Process ID: %d\n Mensage:", pid);
	sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
	// signal(SIGUSR1, handler);
	// signal(SIGUSR2, handler);
	while (1)
		pause();
}

