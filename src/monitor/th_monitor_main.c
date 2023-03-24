/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/25 00:27:16 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	listen_to_old_guys_request(t_share *share, int id);

int	monitor_philos(t_share *share)
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
			answer_dead_to_all_request(share);
			enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
			return (ret);
		}
		if (is_must_eat_times_fulfilled(share) == true)
		{
			answer_dead_to_all_request(share);
			enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
			return (SUCCESS);
		}
		++id;
		if (id == num)
			id = 0;
	}
	return (0);
}

int	answer_request(t_share *share, t_wish *wish, int id, int request)
{
	if (did_the_old_man_go_heaven(share, id) == true)
	{
		enqueue_log_msg_to_writer(share, id, share->philos_time_to_dead[id], LET_DEAD);
		wish->request = LET_DEAD;
		wish->request_info.request = LET_DEAD;

		ft_pthread_mutex_unlock(&share->wishs[id].mutex);
		// ft_pthread_mutex_unlock(&wish->mutex);
		answer_dead_to_all_request(share);
		return (FOUND_DEAD);
	}
	if (request == LET_TRY_TO_TAKE_FORKS)
	{
		if (is_ok_the_guy_take_forks(share, id, share->philo_num))
		{
			wish->request = LET_OK;
			wish->request_info.request = LET_OK;
		}
	}
	else
	{
		wish->request = LET_OK;
		wish->request_info.request = LET_OK;
	}
}

static int	save_request(t_wish_info *info, t_wish_info *philo_request)
{
	info->act_time = philo_request->act_time;
	info->fork_id = philo_request->fork_id;
	info->request = philo_request->request;
	return (0);
}

// int	listen_to_old_guys_request(t_share *share, int id)
// {
// 	t_wish		*wish;
// 	t_wish_info	info;

// 	wish = &share->wishs[id];
// 	ft_pthread_mutex_lock(&wish->mutex);
// 	save_request(&info, &wish->request_info);
// 	if (answer_request(share, wish, id, info.request) == FOUND_DEAD)
// 		return (FOUND_DEAD);
// 	ft_pthread_mutex_unlock(&wish->mutex);
// 	if (enqueue_log_msg_to_writer(share, id, info.act_time, info.request) == ERROR)
// 		return (ERROR);
// 	if (info.request == LET_EAT || info.request == LET_INIT)
// 	{
// 		share->philos_time_to_dead[id] = (info.act_time + share->time_to_starve);
// 		if (info.request == LET_EAT)
// 			++share->philos_eat_times[id];
// 	}
// 	return (SUCCESS);
// }

// int	listen_to_old_guys_request(t_share *share, int id)
// {
// 	t_wish			*wish;
// 	t_wish_info		info;

// 	wish = &share->wishs[id];
// 	ft_pthread_mutex_lock(&wish->mutex);
// 	save_request(&info, &wish->request_info);
// 	if (did_the_old_man_go_heaven(share, id) == true)
// 	{
// 		ft_pthread_mutex_unlock(&wish->mutex);
// 		enqueue_log_msg_to_writer(share, id, share->philos_time_to_dead[id], LET_DEAD);
// 		return (FOUND_DEAD);
// 	}
// 	answer_request(share, wish, id, info.request);
// 	ft_pthread_mutex_unlock(&wish->mutex);
// 	if (enqueue_log_msg_to_writer(share, id, info.act_time, info.request) == ERROR)
// 	{
// 		return (ERROR);
// 	}
// 	// update_dead_time(share, id)
// 	if (info.request == LET_EAT || info.request == LET_INIT)
// 	{
// 		share->philos_time_to_dead[id] = (info.act_time + share->time_to_starve);
// 		if (info.request == LET_EAT)
// 			++share->philos_eat_times[id];
// 	}
// 	return (SUCCESS);
// }

// wishs という配列に、それぞれのphiloからのrequest内容が入っている
int	listen_to_old_guys_request(t_share *share, int id)
{
	t_wish			*wish;
	t_wish_info		info;
	int			request;
	long		sec_milli;
	int			fork_id;

	wish = &share->wishs[id];
	ft_pthread_mutex_lock(&wish->mutex);
	save_request(&info, &wish->request_info);
	request = wish->request;
	sec_milli = wish->sec_milli;
	fork_id = wish->fork_id;

	info.request = wish->request;
	info.act_time = wish->sec_milli;
	info.fork_id = wish->fork_id;

	info.request = wish->request_info.request;
	info.act_time = wish->request_info.act_time;
	info.fork_id = wish->request_info.fork_id;


	if (did_the_old_man_go_heaven(share, id) == true)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		enqueue_log_msg_to_writer(share, id, share->philos_time_to_dead[id], LET_DEAD);
		return (FOUND_DEAD);
	}
	answer_request(share, wish, id, info.request);
	// answer_request(share, wish, id, request);
	ft_pthread_mutex_unlock(&wish->mutex);
	// if (enqueue_log_msg_to_writer(share, id, sec_milli, request) == ERROR)
	if (enqueue_log_msg_to_writer(share, id, info.act_time ,info.request) == ERROR)
	{
		return (ERROR);
	}
	// update_dead_time(share, id)
	if (request == LET_EAT || request == LET_INIT)
	{
		share->philos_time_to_dead[id] = (info.act_time + share->time_to_starve);
		if (request == LET_EAT)
			++share->philos_eat_times[id];
	}
	return (SUCCESS);
}
