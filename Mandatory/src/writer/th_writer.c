/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_writer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:32:20 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 00:40:00 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <libft.h>

int	writer_exe(t_queue *queue)
{
	t_list	*node;
	size_t	len;

	while (1)
	{
		ft_pthread_mutex_lock(&queue->mutex);
		node = ft_dequeue(&queue->list);
		ft_pthread_mutex_unlock(&queue->mutex);
		if (node == NULL)
		{
			usleep(10000);
			continue;
		}
		if (node->content == NULL)
			continue;
		len = ft_strlen(node->content);
		if (len == 0)
		{
			free (node->content);
			free (node);
			return (0);
		}
		if (write(1, node->content, len) == ERROR)
			return (ERROR);
		free (node->content);
		free (node);
		usleep(10000);
	}
	return (0);
}

void	*writer_init(void *arg)
{
	writer_exe(arg);
	return (NULL);
}

