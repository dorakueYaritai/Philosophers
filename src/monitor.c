/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 14:13:20 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int kill_everyone3(t_share *share)
{
	int	i;

	i = 0;
	while (i < share->philo_num)
	{
		if (ft_pthread_mutex_lock(&share->wishs[i].mutex))
			return (ERROR);
		share->wishs[i].let_me_eat = LET_YOU_ARE_ALREADY_DEAD;
		if (ft_pthread_mutex_unlock(&share->wishs[i].mutex))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

bool	did_the_old_man_go_heaven2(t_share *share, int id)
{
	struct timeval	t1;
	long			sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (share->philos_time_to_dead[id] < sec_milli && share->philos_time_to_dead[id] != -1)
	{
		return (true);
	}
	return (false);
}

bool	check_max_loop2(t_share *share)
{
	int	i;

	i = 0;
	if (share->must_eat_times_exists == false)
		return (false);
	while (i < share->philo_num)
	{
		if (share->philos_eat_times[i] < share->must_eat_times)
			return (false);
		i++;
	}
	return (true);
}

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
	if (did_the_old_man_go_heaven2(share, id) == true)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		ft_pthread_mutex_lock(&share->queue->mutex);
		ft_enqueue(&share->queue->list, ft_lstnew(make_msg(id, share->philos_time_to_dead[id], LET_DEAD, NONE)));
		ft_pthread_mutex_unlock(&share->queue->mutex);
		return (LET_DEAD);
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
	
	ft_pthread_mutex_lock(&share->queue->mutex);
	ft_enqueue(&share->queue->list, ft_lstnew(make_msg(id, sec_milli, request, fork_id)));
	ft_pthread_mutex_unlock(&share->queue->mutex);
	// print_time(id, sec_milli, request, fork_id);
	if (request == LET_EAT)
	{
		share->philos_time_to_dead[id] = (sec_milli + share->time_to_starve);
		++share->philos_eat_times[id];
	}
	return (SUCCESS);
}

// PTHREAD_MUTEX_INITIALIZER()
int monitor_philos_death(t_share *share)
{
	int	id;
	int	num;

	num = share->philo_num;
	id = 0;
	while (1)
	{
		// if (did_the_old_man_go_heaven(share, id) == true)
		// 	return (1);
		if (listen_to_old_guys_request(share, id) == LET_DEAD)
		{
			kill_everyone3(share);
			ft_pthread_mutex_lock(&share->queue->mutex);
			ft_enqueue(&share->queue->list, ft_lstnew(strdup("")));
			ft_pthread_mutex_unlock(&share->queue->mutex);
			// print_que(share->queue);
			return (1);
		}
		if (check_max_loop2(share) == true)
		{
			kill_everyone3(share);
			ft_pthread_mutex_lock(&share->queue->mutex);
			ft_enqueue(&share->queue->list, ft_lstnew(strdup("")));
			ft_pthread_mutex_unlock(&share->queue->mutex);
			// print_que(share->queue);
			return (LET_DEAD);
		}
		++id;
		if (id == num)
		{
			// usleep(100);
			id = 0;
		}
		usleep(100);
	}
	return (0);
}
