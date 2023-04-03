/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:01:25 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 14:40:08 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*ndptr;

	(void)content;
	ndptr = malloc(sizeof(t_list));
	if (ndptr == NULL)
		return (NULL);
	else
	{
		ndptr -> next = NULL;
		ndptr->content = content;
		return (ndptr);
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst -> content);
	free(lst);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*nd;

	if (lst == NULL || new == NULL)
		return ;
	nd = ft_lstlast(new);
	nd->next = (*lst);
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)-> next = new;
}
