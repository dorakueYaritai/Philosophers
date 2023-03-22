/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:32:20 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 14:15:40 by kakiba           ###   ########.fr       */
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
			continue;
		len = ft_strlen(node->content);
		// if (node->content == NULL)
		// {
		// 	write(1, "!1111111111\n", 12);
		// 	return (0);
		// }

		if (len == 0)
		{
			write(1, "!1111111111\n", 12);
			free (node->content);
			free (node);
			return (0);
		}

		// if (node == NULL)
		// 	return (0);
		// printf("%s", (char *)node->content);
		write(1, node->content, len);
		free (node->content);
		free (node);
		usleep(10000);
	}
	return (0);
}

void	*writer_init(void *arg)
{
	writer_exe(arg);
	write(1, "2222222222222\n", 12);
	return (NULL);
}

