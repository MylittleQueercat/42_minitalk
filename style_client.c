/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:12:36 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/28 23:29:41 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_log(int pid, t_send *g_send)
{
	ft_putstr_fd("\n"FRAME"=========================================", 1);
	ft_putstr_fd(RST"\n\n", 1);
	ft_putstr_fd(GR" >>> TRANSMISSION SEQUENCE COMPLETED <<<"RST"\n", 1);
	ft_putstr_fd(" TARGET PID  : "BOLD MATRIX_GR, 1);
	ft_putnbr(pid);
	ft_putstr_fd(RST"\n", 1);
	ft_putstr_fd(" BYTES SENT  : "BOLD MATRIX_GR, 1);
	ft_putnbr(g_send->bytes_count);
	ft_putstr_fd(RST"\n\n", 1);
	ft_putstr_fd(FRAME"=========================================", 1);
	ft_putstr_fd(RST"\n\n", 1);
}

int	help_client(void)
{
	ft_putstr_fd("\n"BOLD ALERT"[ERROR] INVALID ARGUMENTS\n"RST, 1);
	ft_putstr_fd(">>> USAGE     : ./client [PID] [MESSAGE]\n", 1);
	ft_putstr_fd(">>> EXAMPLE   : ./client 4242 \"System: Hello.\"\n", 1);
	return (1);
}

int	pid_error(void)
{
	ft_putstr_fd("\n"BOLD ALERT"[ERROR] MALFORMED PID INPUT DETECTED", 1);
	ft_putstr_fd(RST"\n\n", 1);
	return (1);
}

void	timeout_handler(void)
{
	ft_putstr_fd(BOLD ALERT"\n[ERROR] SYSTEM TIMEOUT\n"RST, 1);
	ft_putstr_fd(">>> NO RESPONSE FROM SERVER WITHIN TIME LIMIT\n", 1);
	ft_putstr_fd(">>> POSSIBLE CAUSES:\n", 1);
	ft_putstr_fd("    - INCORRECT PID\n", 1);
	ft_putstr_fd("    - SERVER NOT ACTIVE\n", 1);
	ft_putstr_fd(">>> TERMINATING CLIENT\n\n", 1);
	exit (1);
}
