/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:14:12 by mgering           #+#    #+#             */
/*   Updated: 2024/04/17 16:49:47 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR2)
	{
		ft_printf("\x1b[32mPID:%d recived Message\x1b[0m\n", info->si_pid);
	}
}

int	end_of_line(pid_t server_pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(server_pid, SIGUSR2);
		usleep(100);
		i++;
	}
	return (0);
}

int	message_to_bit(char *message, pid_t server_pid)
{
	int		i;
	int		bit_index;
	int		bit_to_send;

	i = 0;
	while (message[i] != '\0')
	{
		bit_index = 7;
		while (bit_index >= 0)
		{
			bit_to_send = ((int)message[i] >> bit_index) & 1;
			if (bit_to_send == 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(100);
			bit_index--;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	char				*message;
	struct sigaction	sa;
	sigset_t			mask;
	int					sig;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	if (argc != 3)
	{
		write(1, "\x1b[31mUsage: ./client <server_pid> <string>\x1b[0m\n", 48);
		return (1);
	}
	if (message_to_bit(message, server_pid) == 0)
		end_of_line(server_pid);
	sigwait(&mask, &sig);
	return (0);
}
