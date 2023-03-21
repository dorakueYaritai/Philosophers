/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 00:05:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int kill_everyone(t_share *share, int philo_num, int dead_id)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (i != dead_id)
		{
			// ft_pthread_mutex_lock(&share->dead_info[i].mutex);
			ft_pthread_mutex_lock(&share->wishs[i].mutex);
		}
		// share->dead_info[i].is_death = true;
		share->wishs[i].let_me_eat = LET_YOU_ARE_ALREADY_DEAD;
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		// ft_pthread_mutex_unlock(&share->dead_info[i].mutex);
		ft_pthread_mutex_unlock(&share->wishs[i].mutex);
		i++;
	}
	return (SUCCESS);
}

int kill_everyone2(t_share *share, int philo_num, int dead_id)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (i != dead_id)
		{
			// ft_pthread_mutex_lock(&share->dead_info[i].mutex);
			ft_pthread_mutex_lock(&share->wishs[i].mutex);
		}
		// share->dead_info[i].is_death = true;
		share->wishs[i].let_me_eat = LET_YOU_ARE_ALREADY_DEAD;
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		// ft_pthread_mutex_unlock(&share->dead_info[i].mutex);
		ft_pthread_mutex_unlock(&share->wishs[i].mutex);
		i++;
	}
	return (SUCCESS);
}

bool	did_the_old_man_go_heaven(t_share *share, int id)
{
	struct timeval	t1;
	long			sec_milli;

	ft_pthread_mutex_lock(&share->dead_info[id].mutex);
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (*share->dead_info[id].time_to_die < sec_milli && *share->dead_info[id].time_to_die != -1)
	{
		kill_everyone(share, share->philo_num, id);
		print_time(id, sec_milli, LET_DEAD, NONE);
		ft_pthread_mutex_unlock(&share->dead_info[id].mutex);
		return (true);
	}
	ft_pthread_mutex_unlock(&share->dead_info[id].mutex);
	return (false);
}

bool	did_the_old_man_go_heaven2(t_share *share, int id)
{
	struct timeval	t1;
	long			sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (share->philos_time_to_dead[id] < sec_milli && share->philos_time_to_dead[id] != -1)
	{
		kill_everyone(share, share->philo_num, id);
		print_time(id, sec_milli, LET_DEAD, NONE);
		return (true);
	}
	return (false);
}

bool	check_max_loop(t_share *share)
{
	int	i;

	i = 0;
	while (i < share->philo_num)
	{
		ft_pthread_mutex_lock(&share->dead_info[i].mutex);
		if (*(share->dead_info[i].must_eat_times) >= 0)
		{
			while (i >= 0)
			{
				ft_pthread_mutex_unlock(&share->dead_info[i].mutex);
				i--;
			}
			return (false);
		}
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_pthread_mutex_unlock(&share->dead_info[i].mutex);
		i--;
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
		share->philos_time_to_dead[id] = (sec_milli + share->time_to_starve);
	if (share->must_eat_times_exists && check_max_loop(share))
	{
		// write(1, "KILL SITAYO!\n", 13);
		ft_pthread_mutex_lock(&share->dead_info[id].mutex);
		kill_everyone(share, share->philo_num, id);
		return (LET_DEAD);
	}
	// if (did_the_old_man_go_heaven(share, id) == true)
	// 	return (LET_DEAD);
	if (did_the_old_man_go_heaven2(share, id) == true)
		return (LET_DEAD);
	if (request == LET_TRY_TO_TAKE_FORKS)
		wish->let_me_eat = is_ok_the_guy_eat2(share, id, share->philo_num);
		// wish->let_me_eat = is_ok_the_guy_eat(share, id, share->philo_num);
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
	if (request == LET_EAT)
	{
		share->philos_time_to_dead[id] = (sec_milli + share->time_to_starve);
		// char *str = ft_strjoin(ft_ltoa(id), "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[id]));
		// str = ft_strjoin(str, "\n");
		// write(1, str, ft_strlen(str));
	}
	print_time(id, sec_milli, request, fork_id);
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
			return (1);
		++id;
		if (id == num)
		{
			// usleep(100);
			id = 0;
		}
	}
	return (0);
}
