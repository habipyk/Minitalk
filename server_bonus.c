/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:39:58 by hyalcink          #+#    #+#             */
/*   Updated: 2023/09/29 20:37:44 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	signal_handler(int signal, siginfo_t *sig, void *cnt)
{
	static int				bit = 31;
	static unsigned char	set = 0;

	(void)cnt;
	if (signal == SIGUSR1)
		set += (1 << bit);
	if (bit == 0)
	{
		write(1, &set, 1);
		bit = 31;
		set = 0;
		kill(sig->si_pid, SIGUSR2);
	}
	else
		bit--;
}

void	putnbr(int n)
{
	if (n > 10)
		putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = 40;
	act.sa_sigaction = signal_handler;
	putnbr(getpid());
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act,
			NULL) == -1)
	{
		write(1, "error!\n", 8);
		return (0);
	}
	while (1)
		pause();
}
