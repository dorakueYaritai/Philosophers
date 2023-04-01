/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_queue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:42:33 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/30 20:53:56 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

t_list	*ft_dequeue(t_list **lst)
{
	t_list	*return_nd;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	return_nd = (*lst);
	(*lst) = (*lst)->next;
	return (return_nd);
}

void	ft_enqueue(t_list **lst, t_list *new)
{
	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)-> next = new;
}

int	print_que(t_queue *queue)
{
	t_list	*node;

	while (1)
	{
		node = ft_dequeue(&queue->list);
		if (node == NULL)
			return (0);
		printf("%s", (char *)node->content);
		free (node->content);
		free (node);
	}
	return (0);
}
