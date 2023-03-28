/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/28 15:03:25 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	listen_to_old_guys_request(t_share *share, int id);
int	answer_request(t_share *share, t_wish *wish, int id, t_wish_info info);
// int	answer_request(t_share *share, t_wish *wish, int id, int request);
static int	save_request(t_wish_info *info, t_wish_info *philo_request);
void	update_dead_time(t_share *share, int id, t_wish_info info);
static int is_log_needed_action(int act);

void	*monitor_init(void *share)
{
	t_share	*share_;

	share_ = (t_share *)share;
	monitor_philos(share_);
	return (NULL);
}

int	monitor_philos(t_share *share)
{
	int	ret;

	printf("E\n");
	while (1)
	{
		ret = listen_to_old_guys_request(share, share->philo_id);
		printf("F\n");
		if (ret)
		{
			printf("G\n");
			answer_dead_to_all_request(share);
			// enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
			return (ret);
		}
		printf("H\n");
		if (is_must_eat_times_fulfilled(share) == true)
		{
			printf("I\n");
			answer_dead_to_all_request(share);
			// enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
			return (SUCCESS);
		}
		usleep(100);
	}
	return (0);
}

// wishs という配列に、それぞれのphiloからのrequest内容が入っている
int	listen_to_old_guys_request(t_share *share, int id)
{
	t_wish			*wish;
	t_wish_info		info;

	wish = &share->wishs[id];
	if (lock_right_own_left(share, id, share->philo_num) == ERROR)
	{
		printf("a\n");
		return (ERROR);
	}
	ft_pthread_mutex_lock(&wish->mutex);
	save_request(&info, &wish->request_info);
	if (answer_request(share, wish, id, info) == FOUND_DEAD)
	{
		printf("b\n");
		unlock_right_own_left(share, id, share->philo_num);
		return (FOUND_DEAD);
	}
	update_dead_time(share, id, info);
	ft_pthread_mutex_unlock(&wish->mutex);
	unlock_right_own_left(share, id, share->philo_num);
	if (is_log_needed_action(info.request))
	{
		if (enqueue_log_msg_to_writer(share, id, info.act_time , info.request) == ERROR)
		{
			printf("c\n");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	answer_request(t_share *share, t_wish *wish, int id, t_wish_info info)
{
	printf("D\n");
	if (did_the_old_man_go_heaven(share, id) == true)
	{
		enqueue_log_msg_to_writer(share, id, share->time_to_die_array[id].time_to_die, LET_DEAD);
		ft_pthread_mutex_unlock(&wish->mutex);//
		answer_dead_to_all_request(share);
		return (FOUND_DEAD);
	}
	else if (info.request == LET_DEAD)
	{
		enqueue_log_msg_to_writer(share, id, info.act_time, LET_DEAD);
		ft_pthread_mutex_unlock(&wish->mutex);
		answer_dead_to_all_request(share);
		return (FOUND_DEAD);
	}
	else if (info.request == LET_TRY_TO_TAKE_FORKS)
	{
		if (is_ok_the_guy_take_forks(share, id, share->philo_num))
			wish->request_info.request = LET_OK;
	}
	else
		wish->request_info.request = LET_OK;
	return (SUCCESS);
}

static int	save_request(t_wish_info *info, t_wish_info *philo_request)
{
	info->act_time = philo_request->act_time;
	info->fork_id = philo_request->fork_id;
	info->request = philo_request->request;
	return (0);
}

void	update_dead_time(t_share *share, int id, t_wish_info info)
{
	if (info.request == LET_EAT || info.request == LET_INIT)
	{
		share->time_to_die_array[id].time_to_die = info.act_time + share->time_to_starve;
		if (info.request == LET_EAT)
		{
			++share->philos_eat_times[id];
			share->time_to_die_array[id].is_eating = true;
		}
	}
	else if (info.request == LET_SLEEP)
	{
		share->time_to_die_array[id].is_eating = false;
	}
}

static int is_log_needed_action(int act)
{
	return (act == LET_EAT || act == LET_TAKE_A_FORK \
	|| act == LET_SLEEP || act == LET_DEAD || act == LET_THINK);
}

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
