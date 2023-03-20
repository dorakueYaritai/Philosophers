/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 23:08:40 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	put_fork(t_philo *philo, t_fork *fork);
static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had);

int	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	first = philo->forks[FIRST];
	second = philo->forks[SECOND];
	update_wish_status(philo->wish);
	while (1)
	{
		if (check_am_i_dead(philo) == true)
			return (ERROR);
		if (is_wish_come(philo->wish) == true)
		{
			// thanks_a_host(philo->wish);
			break;
		}
	}
	if (take_fork(philo, first, NULL) == ERROR)
		return (ERROR);
	if (take_fork(philo, second, first) == ERROR)
	{
		put_fork(philo, first);
		return (ERROR);
	}
	return (0);
}

static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
{
	struct timeval t1;
	long sec_milli;
	int				ret;

	while (1)
	{
		if (check_am_i_dead(philo) == true)
			return (ERROR);
		if (ft_pthread_mutex_trylock(&fork->fork) == SUCCESS)
			break;
		if (had)
		{
			if (put_fork(philo, had) == ERROR)
				return (ERROR);
			usleep(100);
			return (take_forks(philo));
		}
	}
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (check_am_i_dead(philo) == true)
	{
		put_fork(philo, fork);
		return (ERROR);
	}
	// ft_pthread_mutex_lock(&philo->dead_info->mutex);
	ret = print_time(philo->philo_id, sec_milli, FORK, fork->fork_id);
	// ft_pthread_mutex_unlock(&philo->dead_info->mutex);
	return (ret);
}

int	put_forks(t_philo *philo)
{
	// t_fork	*first;
	// t_fork	*second;

	// first = philo->forks[FIRST];
	// second = philo->forks[SECOND];
	// if (put_fork(philo, first) == ERROR)
	// 	return (ERROR);
	// if (put_fork(philo, second) == ERROR)
	// 	return (ERROR);
	if (put_fork(philo, philo->forks[FIRST]) == ERROR)
		return (ERROR);
	if (put_fork(philo, philo->forks[SECOND]) == ERROR)
		return (ERROR);	
	return (SUCCESS);
}

int	put_fork(t_philo *philo, t_fork *fork)
{
	struct timeval t1;//
	long sec_milli;//
	int	ret;

	gettimeofday(&t1, NULL);//
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;//
	if (check_am_i_dead(philo) == true)
	{
		pthread_mutex_unlock(&fork->fork.stuff);
		fork->fork.is_available = false;
		return (ERROR);
	}
	ret = print_time(philo->philo_id, sec_milli, PUTOFF, fork->fork_id);//
	fork->fork.is_available = true;
	if (pthread_mutex_unlock(&fork->fork.stuff))
		return (ERROR);
	return (ret);//
	// return (SUCCESS);
}

// static int	put_fork(t_philo *philo, t_fork *fork)
// {
// 	int	ret;

// 	// if (check_am_i_dead(philo) == true)
// 	// {
// 	// 	pthread_mutex_unlock(&fork->fork.stuff);
// 	// 	fork->fork.is_available = false;
// 	// 	return (ERROR);
// 	// }
// 	fork->fork.is_available = true;
// 	if (pthread_mutex_unlock(&fork->fork.stuff))
// 		return (ERROR);
// 	return (SUCCESS);
// }
