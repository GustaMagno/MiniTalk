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

void	send_bit(char *spid, char c)
{
	int	i;

	
	i = 7;
	while (1)
	{
		if ((c >> i) & 1)
		{
			kill(ft_atoi(spid), SIGUSR2);
			usleep(100);
		}
		else
		{
			kill(ft_atoi(spid), SIGUSR1);
			usleep(100);
		}
		if (i-- == 0)
			return ;
	}
}

int main(int argc, char	**str)
{
	if (argc != 3)
		return (0);
	// kill(ft_atoi(str[1]), SIGUSR2);
	while (*str[2])
	{
		send_bit(str[1], *str[2]);
		str[2]++;
	}
}