/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/21 21:04:02 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int kill_everyone(t_shere *shere, int philo_num, int dead_id)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (i != dead_id)
		{
			// ft_pthread_mutex_lock(&shere->dead_info[i].mutex);
			ft_pthread_mutex_lock(&shere->wishs[i].mutex);
		}
		// shere->dead_info[i].is_death = true;
		shere->wishs[i].let_me_eat = LET_YOU_ARE_ALREADY_DEAD;
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		// ft_pthread_mutex_unlock(&shere->dead_info[i].mutex);
		ft_pthread_mutex_unlock(&shere->wishs[i].mutex);
		i++;
	}
	return (SUCCESS);
}

bool	did_the_old_man_go_heaven(t_shere *shere, int id)
{
	struct timeval	t1;
	long			sec_milli;

	ft_pthread_mutex_lock(&shere->dead_info[id].mutex);
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (*shere->dead_info[id].time_to_die < sec_milli && *shere->dead_info[id].time_to_die != -1)
	{
		kill_everyone(shere, shere->philo_num, id);
		print_time(id, sec_milli, LET_DEAD, NONE);
		ft_pthread_mutex_unlock(&shere->dead_info[id].mutex);
		return (true);
	}
	ft_pthread_mutex_unlock(&shere->dead_info[id].mutex);
	return (false);
}

bool	check_max_loop(t_shere *shere)
{
	int	i;

	i = 0;
	while (i < shere->philo_num)
	{
		ft_pthread_mutex_lock(&shere->dead_info[i].mutex);
		if (*(shere->dead_info[i].must_eat_times) >= 0)
		{
			while (i >= 0)
			{
				ft_pthread_mutex_unlock(&shere->dead_info[i].mutex);
				i--;
			}
			return (false);
		}
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_pthread_mutex_unlock(&shere->dead_info[i].mutex);
		i--;
	}
	return (true);
}

int	listen_to_old_guys_request(t_shere *shere, int id)
{
	t_wish	*wish;
	int		request;
	long	sec_milli;
	int		fork_id;

	wish = &shere->wishs[id];
	ft_pthread_mutex_lock(&wish->mutex);
	if (shere->must_eat_times_exists && check_max_loop(shere))
	{
		// write(1, "KILL SITAYO!\n", 13);
		ft_pthread_mutex_lock(&shere->dead_info[id].mutex);
		kill_everyone(shere, shere->philo_num, id);
		return (LET_DEAD);
	}
	if (did_the_old_man_go_heaven(shere, id) == true)
		return (LET_DEAD);
	request = wish->let_me_eat;
	if (request == LET_TRY_TO_TAKE_FORKS)
		wish->let_me_eat = is_ok_the_guy_eat(shere, id, shere->philo_num);
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
		update_time_to_die_monitor(sec_milli + philo->status.time_to_starve);
	print_time(id, sec_milli, request, fork_id);
	return (SUCCESS);
}

// PTHREAD_MUTEX_INITIALIZER()
int monitor_philos_death(t_shere *shere)
{
	int	id;
	int	num;

	num = shere->philo_num;
	id = 0;
	while (1)
	{
		// if (did_the_old_man_go_heaven(shere, id) == true)
		// 	return (1);
		if (listen_to_old_guys_request(shere, id) == LET_DEAD)
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
