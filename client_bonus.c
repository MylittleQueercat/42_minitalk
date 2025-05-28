/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:12:20 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/28 23:32:53 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_send	g_send;

static void	send_bit(int pid, char c)
{
	int	i;
	int	timeout;

	i = 7;
	while (i >= 0)
	{
		timeout = 0;
		while (g_send.state == 0)
		{
			if (timeout > 1000000)
				return (timeout_handler());
			timeout += 10;
			usleep(10);
		}
		g_send.state = 0;
		if (c & (1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
	}
	g_send.bytes_count++;
}

static void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_send.state = 1;
	(void)sig;
	(void)info;
	(void)ucontext;
}

static void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_bit(pid, message[i]);
		i++;
	}
	send_bit(pid, '\0');
	send_log(pid, &g_send);
}

int	main(int ac, char **av)
{
	int			pid;
	struct sigaction	sa1;

	g_send.state = 1;
	g_send.bytes_count = 0;
	if (ac != 3)
		return (help_client());
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (pid_error());
	sa1.sa_sigaction = sigusr1_handler;
	sa1.sa_flags = SA_SIGINFO;
	sigemptyset(&sa1.sa_mask);
	sigaction(SIGUSR1, &sa1, NULL);
	send_message(pid, av[2]);
	return (0);
}
