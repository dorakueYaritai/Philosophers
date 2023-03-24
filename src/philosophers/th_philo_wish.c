/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo_wish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:33:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/25 01:23:24 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id, int id)
{
	ft_pthread_mutex_lock(&wish->mutex);
	if (wish->request_info.request == LET_DEAD)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		return (ERROR);
	}
	wish->request_info.request = request;
	wish->request_info.act_time = sec_milli;
	wish->request_info.fork_id = fork_id;

	ft_pthread_mutex_unlock(&wish->mutex);
	return (SUCCESS);
}

int	get_monitor_answer(t_wish *wish, int id, int wish_act)
{
	int	ret;

	if (ft_pthread_mutex_trylock(&wish->mutex) == ERROR)
		return (wish_act);
	ret = wish->request_info.request;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (wish_act);
	return (ret);
}

// int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id, int id)
// {
// 	if (ft_pthread_mutex_trylock(&wish->mutex) == ERROR)
// 		retturn 
// 	if (wish->request == LET_DEAD)
// 	{
// 		ft_pthread_mutex_unlock(&wish->mutex);
// 		return (ERROR);
// 	}
// 	wish->request = request;
// 	wish->sec_milli = sec_milli;
// 	wish->fork_id = fork_id;
// 	ft_pthread_mutex_unlock(&wish->mutex);
// 	return (SUCCESS);
// }
