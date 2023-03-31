/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/31 13:35:52 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int		answer_to_philo_request(t_share *share, int id);
int		answer_request(t_share *share, t_wish *wish, int id, t_wish_info info);
void	update_dead_time(t_share *share, int id, t_wish_info info);
int		answer_dead_to_all_request(t_share *share);

// answer the philo's request
// if philo is dead, monitor will answer to all philo's request to be dead(exit)

void	*monitor_init(void *share_)
{
	t_share	*share;
	int		ret;

	share = (t_share *)share_;
	while (1)
	{
		ret = answer_to_philo_request(share, share->philo_id);
		if (ret)
		{
			answer_dead_to_all_request(share);
			return ((void *)ERROR);
		}
		if (is_must_eat_times_fulfilled(share) == true)
		{
			answer_dead_to_all_request(share);
			return ((void *)SUCCESS);
		}
	}
	return ((void *)SUCCESS);
}

// wishs という配列に、それぞれのphiloからのrequest内容が入っている
int	answer_to_philo_request(t_share *share, int id)
{
	t_wish			*wish;
	t_wish_info		save_info;

	wish = &share->wishs[id];
	if (lock_data_avoiding_race(share, id, share->philo_num) == ERROR)
		return (ERROR);
	ft_pthread_mutex_lock(&wish->mutex);
	save_info = wish->request_info;
	if (answer_request(share, wish, id, save_info))
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		unlock_data_avoiding_race(share, id, share->philo_num);
		return (FOUND_DEAD);
	}
	update_dead_time(share, id, save_info);
	ft_pthread_mutex_unlock(&wish->mutex);
	unlock_data_avoiding_race(share, id, share->philo_num);
	return (SUCCESS);
}

int	answer_request(t_share *share, t_wish *wish, int id, t_wish_info info)
{
	if (did_the_old_man_go_heaven(share, id) || info.request == LET_DEAD)
	{
		if (info.request == LET_DEAD)
			enqueue_log_msg_to_writer(share, id, info.act_time, LET_DEAD);
		else
			enqueue_log_msg_to_writer(share, id, \
				share->time_to_die_array[id].time_to_die, LET_DEAD);
		return (FOUND_DEAD);
	}
	else if (info.request == LET_TRY_TO_TAKE_FORKS)
	{
		if (whethre_allow_taking_the_fork(share, id, share->philo_num) == true)
		{
			wish->request_info.request = LET_OK;
			share->time_to_die_array[id].is_taking_fork = true;
		}
	}
	else if (info.request == LET_INIT)
		wish->request_info.request = LET_OK;
	else
	{
		if (enqueue_log_msg_to_writer(share, id, info.act_time, info.request))
			return (ERROR);
		wish->request_info.request = LET_OK;
	}
	return (SUCCESS);
}

void	update_dead_time(t_share *share, int id, t_wish_info info)
{
	if (info.request == LET_EAT || info.request == LET_INIT)
	{
		share->time_to_die_array[id].time_to_die
			= info.act_time + share->time_to_starve;
		if (info.request == LET_EAT)
			++share->philos_eat_times[id];
	}
	else if (info.request == LET_SLEEP)
	{
		share->time_to_die_array[id].is_taking_fork = false;
	}
}

int	answer_dead_to_all_request(t_share *share)
{
	int	i;

	i = 0;
	while (i < share->philo_num)
	{
		if (ft_pthread_mutex_lock(&share->wishs[i].mutex))
			return (ERROR);
		share->wishs[i].request_info.request = LET_DEAD;
		if (ft_pthread_mutex_unlock(&share->wishs[i].mutex))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
