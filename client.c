/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:14:12 by mgering           #+#    #+#             */
/*   Updated: 2024/04/16 11:28:48 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_server_recived_message = 0;

void	signal_handler(int signum)
{
	if (signum == SIGUSR2)
	{
		write(1, "\x1b[32mServer recived Message\x1b[0m\n", 33);
		g_server_recived_message = 1;
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

int	message_length(char *message, pid_t server_pid)
{
	unsigned int	lenght;
	int				bit_to_send;
	int				bit_index;

	lenght = ft_strlen(message);
	bit_index = 31;
	while (bit_index >= 0)
	{
		bit_to_send = ((lenght) >> bit_index) & 1;
		if (bit_to_send == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		bit_index--;
	}
	printf("%u", lenght);
	return (0);
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	char				*message;
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	if (argc != 3) 
	{
		write(1, "\x1b[31mUsage: ./client <server_pid> <string>\x1b[0m\n", 48);
		return (1);
	}
	if (message_length(message, server_pid) == 0)
	{
		if (message_to_bit(message, server_pid) == 0)
			end_of_line(server_pid);
	}
	while (g_server_recived_message == 0)
		pause();
	return (0);
}
