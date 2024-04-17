/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:49:40 by mgering           #+#    #+#             */
/*   Updated: 2024/04/17 16:28:30 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_char_join(char *message, char const character)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!message && !character)
		return (NULL);
	str = ft_calloc((ft_strlen(message) + 2), sizeof(char));
	if (!str)
		return (free(message), NULL);
	while (message && message[i] != '\0')
	{
		str[i] = message[i];
		i++;
	}
	str[i] = character;
	i++;
	str[i] = '\0';
	if (message)
		free(message);
	return (str);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bit_index = 0;
	static char	character = 0;
	static char	*message;

	(void)context;
	if (!message)
		message = ft_strdup("");
	character = character << 1;
	if (signum == SIGUSR1)
		character |= 1;
	bit_index++;
	if (bit_index == 8)
	{
		message = ft_char_join(message, character);
		if (character == '\0')
		{
			ft_printf("%s\n", message);
			free (message);
			message = NULL;
			kill(info->si_pid, SIGUSR2);
			write(1, "\x1b[32mWaiting for Client:\x1b[0m\n", 30);
		}
		bit_index = 0;
		character = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("\x1b[32mServer PID: %d\x1b[0m\n", pid);
	write(1, "\x1b[32mWaiting for Client:\x1b[0m\n", 30);
	while (1)
	{
		pause();
	}
	return (0);
}
