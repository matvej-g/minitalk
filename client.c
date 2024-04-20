/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:14:12 by mgering           #+#    #+#             */
/*   Updated: 2024/04/20 17:47:56 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_flag = 1;

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR2)
	{
		ft_printf("\x1b[32mPID:%d recived Message\x1b[0m\n", info->si_pid);
		g_flag = 0;
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

	i = -1;
	while (message[++i] != '\0')
	{
		bit_index = 8;
		while (--bit_index >= 0)
		{
			bit_to_send = ((int)message[i] >> bit_index) & 1;
			if (bit_to_send == 1)
			{
				if (kill(server_pid, SIGUSR1) == -1)
					return (-1);
			}
			else
			{
				if (kill(server_pid, SIGUSR2) == -1)
					return (-1);
			}
			usleep(100);
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	char				*message;
	struct sigaction	sa;
	int					result;

	if (argc != 3)
		return (ft_printf("Usage: ./client <server_pid> <string>"), 1);
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	result = message_to_bit(message, server_pid);
	if (result == 0)
	{
		end_of_line(server_pid);
		while (g_flag == 1)
			pause();
	}
	else if (result == -1)
		perror("Error sending message");
	return (0);
}
