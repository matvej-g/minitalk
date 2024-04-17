/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:49:40 by mgering           #+#    #+#             */
/*   Updated: 2024/04/17 14:55:52 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_GlobalData	g_data;

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	g_data.current_char = g_data.current_char << 1;
	if (signum == SIGUSR1)
		g_data.current_char |= 1;
	g_data.bit_index++;
	if (g_data.bit_index == 8)
	{
		if (g_data.current_char == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			kill (info->si_pid, SIGUSR2);
		}
		else
		{
			write(STDOUT_FILENO, (const void *)&g_data.current_char, 1);
			kill (info->si_pid, SIGUSR1);
		}
		g_data.bit_index = 0;
		g_data.current_char = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	g_data.bit_index = 0;
	g_data.current_char = 0;
	pid = getpid();
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("Server PID: %d\n", pid);
	while (1) 
	{
		pause();
	}
	return (0);
}

