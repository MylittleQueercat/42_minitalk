/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:12:31 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/28 21:47:06 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_char	g_ch;

static void	prep_struct(siginfo_t *info)
{
	if (info->si_pid <= 0)
		return ;
	if (g_ch.bit == 8)
	{
		g_ch.bytes_count++;
		if (g_ch.bytes_count > g_ch.nb_struct * BUFF_SIZE)
		{
			g_ch.nb_struct++;
			append_data_node(&g_ch);
		}
		g_ch.tail->s[(g_ch.bytes_count - 1) % BUFF_SIZE] = g_ch.c;
		if (g_ch.c == '\0')
		{
			recv_log(info, &g_ch);
			g_ch.bytes_count = 0;
			g_ch.nb_struct = 0;
			g_ch.bit = 0;
			g_ch.c = 0;
			free_data_list(g_ch.head);
			g_ch.tail = NULL;
			g_ch.head = NULL;
		}
		g_ch.bit = 0;
		g_ch.c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

static void	sigusr1_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_ch.c <<= 1;
	g_ch.c &= 0xFE;
	g_ch.bit++;
	prep_struct(info);
	(void)sig;
	(void)info;
	(void)ucontext;
}
// 0xFE == 11111110

static void	sigusr2_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_ch.c <<= 1;
	g_ch.c |= 0x01;
	g_ch.bit++;
	prep_struct(info);
	(void)sig;
	(void)info;
	(void)ucontext;
}
// 0x01 == 00000001

static void	start_server(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_sigaction = sigusr1_handler;
	sa1.sa_flags = SA_SIGINFO;
	sigemptyset(&sa1.sa_mask);
	sigaction(SIGUSR1, &sa1, NULL);
	sa2.sa_sigaction = sigusr2_handler;
	sa2.sa_flags = SA_SIGINFO;
	sigemptyset(&sa2.sa_mask);
	sigaction(SIGUSR2, &sa2, NULL);
	while (1)
	{
		pause();
	}
}

int	main(int ac, char **av)
{
	int	pid;

	(void)av;
	g_ch.bit = 0;
	g_ch.c = 0;
	g_ch.bytes_count = 0;
	g_ch.nb_struct = 0;
	g_ch.head = NULL;
	g_ch.tail = NULL;
	if (ac != 1)
		return (print_args_error());
	pid = getpid();
	print_server_pid(pid);
	start_server();
	return (0);
}
