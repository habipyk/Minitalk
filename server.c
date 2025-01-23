/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:17:27 by hyalcink          #+#    #+#             */
/*   Updated: 2023/07/25 13:07:52 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

void	setbits(int x)
{
	static int				bit = 6;
	static unsigned char	set = 0;

	set = set + (x << bit);
	if (bit == 0)
	{
		write(1, &set, 1);
		bit = 6;
		set = 0;
	}
	else
		bit--;
}

void	signal_handler(int x)
{
	if (x == SIGUSR1)
		setbits(1);
	else
		setbits(0);
}

void	putnbr(int n)
{
	if (n > 10)
		putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

int	main(void)
{
	putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
}
