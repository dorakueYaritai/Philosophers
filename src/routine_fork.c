/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/18 12:33:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_fork(t_philo *philo, t_fork *fork)
{
	struct timeval t1;
	long sec_milli;

	pthread_mutex_lock(&fork->fork_check);
	while (fork->is_fork_available == false)
	{
		if (check_am_i_dead(philo))
		{
			pthread_mutex_unlock(&fork->fork_check);
			return (ERROR);
		}
	}
	pthread_mutex_lock(&fork->fork);
	fork->is_fork_available = false;
	pthread_mutex_unlock(&fork->fork_check);
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die != -1 && philo->time_to_die <= sec_milli)
	{
		return (ERROR);
		// return (print_time(philo->philo_id, philo->time_to_die, DEAD, NONE));
	}
	return (print_time(philo->philo_id, sec_milli, FORK, fork->fork_id));
}

int	put_fork(t_philo *philo, t_fork *fork)
{
	if (check_am_i_dead(philo))
		return (ERROR);
	if (pthread_mutex_unlock(&fork->fork))
		return (ERROR);
	fork->is_fork_available = true;
	return (SUCCESS);
}
