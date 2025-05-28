/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:12:25 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/28 19:18:23 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L
# define _DEFAULT_SOURCE

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define BOLD  "\033[1m"
# define MATRIX_GR  "\033[38;5;46m"
# define GR "\033[2m"
# define RST "\033[0m"
# define FRAME "\033[38;5;22m"
# define ALERT "\033[38;5;196m"

# define BUFF_SIZE 256

typedef struct s_data	t_data;
typedef struct s_char	t_char;
typedef struct s_send	t_send;

typedef struct s_data
{
	t_data	*next;
	char	s[BUFF_SIZE];
}	t_data;

typedef struct s_char
{
	t_data	*head;
	t_data	*tail;
	char	c;
	int		bit;
	int		bytes_count;
	int		nb_struct;
}	t_char;

typedef struct s_send
{
	int	state;
	int	bytes_count;
}	t_send;

void	print_server_pid(int pid);
void	recv_log(siginfo_t *info, t_char *g_ch);
void	send_log(int pid, t_send *g_send);
int		print_args_error(void);
int		help_client(void);
int		pid_error(void);
void	timeout_handler(void);
void	ft_putnbr(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_atoi(char *s);
void	append_data_node(t_char *g_ch);
void	free_data_list(t_data *data);

#endif
