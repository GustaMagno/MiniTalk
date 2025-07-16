
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:49:21 by gustoliv          #+#    #+#             */
/*   Updated: 2025/06/23 13:47:04 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				check;
	int				nb;

	i = 0;
	check = 0;
	nb = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			check++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	if (check == 1)
		nb *= -1;
	return (nb);
}
void	handler_ack(int sig)
{
	(void)sig;
}
void	send_len(int pid, char *s)
{
	int i;
	int len;

	len = 0;
	while (s[len])
		len++;
	i = 31;
	while (i >= 0)
	{
		if ((len >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(1500);
	}
}

void	send_bit(int pid, char c)
{
	int	i;

	
	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(1500);
	}
}

int main(int argc, char	**str)
{
	int pid;

	signal(SIGUSR1, handler_ack);
	if (argc != 3)
		return (0);
	pid = ft_atoi(str[1]);
	if (pid < 0)
		return (1);
	send_len(pid, str[2]);
	while (*str[2])
	{
		send_bit(pid, *str[2]);
		str[2]++;
	}
}
