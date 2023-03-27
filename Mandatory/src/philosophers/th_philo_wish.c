/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo_wish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:33:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 23:04:17 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

	// wish->request_info.request = info->request;
	// wish->request_info.act_time = info->act_time;
	// wish->request_info.fork_id = info->fork_id;

int	update_wish_status(t_wish *wish, t_wish_info *info)
{
	ft_pthread_mutex_lock(&wish->mutex);
	if (wish->request_info.request == LET_DEAD)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		return (ERROR);
	}
	wish->request_info = *info;
	ft_pthread_mutex_unlock(&wish->mutex);
	return (SUCCESS);
}

int	get_monitor_answer(t_wish *wish)
{
	int	ret;

	if (ft_pthread_mutex_lock(&wish->mutex) == ERROR)
		return (LET_DEAD);
	ret = wish->request_info.request;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (LET_DEAD);
	return (ret);
}

int	ft_return(t_philo *philo, int ret)
{
	if (ret != SUCCESS)
	{
		exe_act(philo, LET_DEAD);
		return (ret);
	}
	return (SUCCESS);
}

void	init_wish_info(t_wish_info *info, \
	long act_time, int fork_id, int request)
{
	info->act_time = act_time;
	info->fork_id = fork_id;
	info->request = request;
}
