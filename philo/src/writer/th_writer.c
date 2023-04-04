/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_writer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:32:20 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/04 08:40:18 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <libft.h>

int	writer_exe(t_queue *queue)
{
	t_list	*node;
	size_t	len;
	bool	do_proceed;

	do_proceed = true;
	while (do_proceed || node)
	{
		ft_pthread_mutex_lock(&queue->mutex);
		node = ft_dequeue(&queue->list);
		do_proceed = queue->do_proceed;
		ft_pthread_mutex_unlock(&queue->mutex);
		if (node == NULL)
			continue ;
		len = ft_strlen(node->content);
		if (write(1, node->content, len) == -1)
		{
			free (node->content);
			free (node);
			return (ERROR);
		}
		free (node->content);
		free (node);
		usleep(10000);
	}
	return (SUCCESS);
}

void	*writer_init(void *arg)
{
	writer_exe(arg);
	return (NULL);
}
