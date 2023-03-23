/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:21:19 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 10:00:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_list	*ft_lstnew(void	*content)
{
	t_list	*ndptr;

	ndptr = malloc(sizeof(t_list));
	if (ndptr == NULL)
		return (NULL);
	else
	{
		ndptr->content = content;
		ndptr->next = NULL;
		return (ndptr);
	}
}

static t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

static void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)-> next = new;
}

void	*ft_malloc(size_t size, t_list **alloc_list)
{
	void	*ptr;
	t_list	*node;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	node = ft_lstnew(otr);
	if (ptr == NULL)
	{
		free (ptr);
		return (NULL);
	}
	ft_lstadd_back(alloc_list, node);
}
