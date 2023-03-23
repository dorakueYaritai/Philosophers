/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 17:29:39 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	listen_to_old_guys_request(t_share *share, int id)
{
	t_wish	*wish;
	int		request;
	long	sec_milli;
	int		fork_id;

	wish = &share->wishs[id];
	ft_pthread_mutex_lock(&wish->mutex);
	request = wish->let_me_eat;
	if (request == LET_INIT)
	{
		share->philos_time_to_dead[id] = (wish->sec_milli + share->time_to_starve);
		wish->let_me_eat = LET_OK;
	}
	if (did_the_old_man_go_heaven(share, id) == true)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		enqueue_log_msg_to_writer(share, id, share->philos_time_to_dead[id], LET_DEAD);
		return (FOUND_DEAD);
	}
	if (request == LET_TRY_TO_TAKE_FORKS && is_ok_the_guy_eat2(share, id, share->philo_num))
		wish->let_me_eat = LET_OK;
	if (request != LET_EAT && request != LET_SLEEP && request != LET_THINK &&
			request != LET_TAKE_A_FORK)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		return (SUCCESS);
	}
	sec_milli = wish->sec_milli;
	fork_id = wish->fork_id;
	wish->let_me_eat = LET_OK;
	ft_pthread_mutex_unlock(&wish->mutex);
	if (enqueue_log_msg_to_writer(share, id, sec_milli, request) == ERROR)
		return (ERROR);
	if (request == LET_EAT)
	{
		share->philos_time_to_dead[id] = (sec_milli + share->time_to_starve);
		++share->philos_eat_times[id];
	}
	return (SUCCESS);
}

int	monitor_philos_death(t_share *share)
{
	int	id;
	int	num;
	int	ret;

	num = share->philo_num;
	id = 0;
	while (1)
	{
		ret = listen_to_old_guys_request(share, id);
		if (ret)
		{
			kill_everyone(share);
			enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
			return (ret);
		}
		if (is_must_eat_times_fulfilled(share) == true)
		{
			kill_everyone(share);
			enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
			return (SUCCESS);
		}
		++id;
		if (id == num)
			id = 0;
	}
	return (0);
}
