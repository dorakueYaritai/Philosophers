/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wish.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:33:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/21 19:06:04 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>


	// char *join;
	// join = ft_strjoin("::: ", ft_ltoa(id));
	// join = ft_strjoin(join, " update ");
	// join = ft_strjoin(join, ft_ltoa(request));
	// join = ft_strjoin(join, "\n");
	// write(1, join, ft_strlen(join));

int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id, int id)
{
	ft_pthread_mutex_lock(&wish->mutex);
	if (wish->let_me_eat == LET_YOU_ARE_ALREADY_DEAD)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		return (ERROR);
	}
	wish->let_me_eat = request;
	wish->sec_milli = sec_milli;
	wish->fork_id = fork_id;
	ft_pthread_mutex_unlock(&wish->mutex);
}

int	is_wish_come(t_wish *wish, int id)
{
	int	ret;

	if (ft_pthread_mutex_trylock(&wish->mutex) == ERROR)
		return (LET_REJECT);
	ret = wish->let_me_eat;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (LET_REJECT);
	return (ret);
}
