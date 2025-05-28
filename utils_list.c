/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:12:38 by leticiabi         #+#    #+#             */
/*   Updated: 2025/05/28 19:45:24 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = (unsigned char)c;
}

void	append_data_node(t_char *g_ch)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return ;
	ft_memset(new->s, 0, BUFF_SIZE);
	new->next = NULL;
	if (g_ch->tail != NULL)
		g_ch->tail->next = new;
	else
		g_ch->head = new;
	g_ch->tail = new;
}

void	free_data_list(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data;
		data = data->next;
		free(tmp);
	}
}
