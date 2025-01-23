/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:39:33 by hyalcink          #+#    #+#             */
/*   Updated: 2023/09/29 20:37:51 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	my_atoi(char *str)
{
	int	number;

	number = 0;
	while (*str)
	{
		number = (10 * number) + (*str - 48);
		str++;
	}
	return (number);
}

void	msg_client(int x)
{
	static int	i = 0;

	if (i == 0 && x == SIGUSR2)
	{
		i++;
		write(1, "Success!\n", 10);
	}
}

void	bitshift(int pid, char *str)
{
	int				i;
	unsigned char	c;

	while (*str)
	{
		i = 31;
		c = *str;
		while (i >= 0)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			signal(SIGUSR2, msg_client);
			usleep(100);
			i--;
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		return (0);
	}
	bitshift(my_atoi(argv[1]), argv[2]);
	bitshift(my_atoi(argv[1]), "\n");
	return (0);
}
