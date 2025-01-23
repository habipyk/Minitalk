/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:13:16 by hyalcink          #+#    #+#             */
/*   Updated: 2023/07/25 13:13:02 by hyalcink         ###   ########.fr       */
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

void	bitshift(int pid, char *str)
{
	int				i;
	unsigned char	c;

	while (*str)
	{
		i = 6;
		c = *str;
		while (i >= 0 && *str >= 0 && *str <= 127)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
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
