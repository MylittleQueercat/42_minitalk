/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:12:43 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/28 23:30:16 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	recv_log(siginfo_t *info, t_char *g_ch)
{
	int		v;
	t_data	*tmp;

	(void)info;
	tmp = g_ch->head;
	while (tmp)
	{
		v = 0;
		while (v < BUFF_SIZE)
		{
			ft_putchar_fd(tmp->s[v], 1);
			v++;
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("\n\n"FRAME"===================================", 1);
	ft_putstr_fd(RST"\n\n"MATRIX_GR"  >> MESSAGE STREAM COMPLETE <<"RST"\n", 1);
	ft_putstr_fd(GR"    SOURCE PID : " MATRIX_GR BOLD, 1);
	ft_putnbr(info->si_pid);
	ft_putstr_fd(RST"\n", 1);
	ft_putstr_fd(GR"    TOTAL BYTES RECEIVED : " MATRIX_GR, 1);
	ft_putnbr(g_ch->bytes_count);
	ft_putstr_fd(RST "\n", 1);
	ft_putstr_fd("\n"FRAME"==================================="RST"\n\n", 1);
}

void	print_server_pid(int pid)
{
	ft_putstr_fd("\n"FRAME"======================================", 1);
	ft_putstr_fd(RST"\n\n", 1);
	ft_putstr_fd(BOLD MATRIX_GR"   Minitalk Server Terminal: Online", 1);
	ft_putstr_fd(RST"\n", 1);
	ft_putstr_fd(GR"   Listening for incoming signals...\n", 1);
	ft_putstr_fd("        System PID -> "MATRIX_GR, 1);
	ft_putnbr(pid);
	ft_putstr_fd(RST "\n\n", 1);
	ft_putstr_fd(FRAME"======================================", 1);
	ft_putstr_fd(RST "\n\n", 1);
}

int	print_args_error(void)
{
	ft_putstr_fd(BOLD ALERT"[ERROR] Unexpected argument detected.", 2);
	ft_putstr_fd(RST "\n\n", 1);
	return (1);
}
