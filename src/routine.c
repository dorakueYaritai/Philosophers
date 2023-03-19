/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:38 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 16:44:37 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	philo_think(t_philo *philo);
int	update_time_to_die(t_philo *philo, long new_time_to_die);
static int	philo_sleep(t_philo *philo);
static int	philo_eat(t_philo *philo);
static int	exe_act(t_philo *philo, int act);

int	update_time_to_die(t_philo *philo, long new_time_to_die)
{
	ft_pthread_mutex_lock(&philo->dead_info->mutex);
	*philo->dead_info->time_to_die = new_time_to_die;
	ft_pthread_mutex_unlock(&philo->dead_info->mutex);
	return (SUCCESS);
}

static int	exe_act(t_philo *philo, int act)
{
	struct timeval t1;
	long sec_milli;
	long time;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (check_am_i_dead(philo))
		return (ERROR);
	if (print_time(philo->philo_id, sec_milli, act, NONE) == ERROR)
		return (ERROR);
	if (act == EAT)
	{
		update_time_to_die(philo, sec_milli + philo->time_to_starve);
		usleep((unsigned int)(philo->time_to_eat) * 1000);
	}
	else if (act == SLEEP)
		usleep((unsigned int)(philo->time_to_sleep) * 1000);
	return (SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	if (exe_act(philo, EAT) == ERROR)
	{
		put_forks(philo);
		return (ERROR);
	}
	if (put_forks(philo) == ERROR)
		return (ERROR);
	return (philo_sleep(philo));
}

static int	philo_sleep(t_philo *philo)
{
	if (exe_act(philo, SLEEP) == ERROR)
		return (ERROR);
	return (philo_think(philo));
}

int	philo_think(t_philo *philo)
{
	if (exe_act(philo, THINK) == ERROR)
		return (ERROR);
	if (take_forks(philo) == ERROR)
	{
		return (ERROR);
	}
	return (philo_eat(philo));
}

