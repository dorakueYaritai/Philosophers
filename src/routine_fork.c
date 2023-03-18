/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 01:02:54 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
{
	struct timeval t1;
	long sec_milli;

	pthread_mutex_lock(&fork->fork_check);
	while (fork->is_fork_available == false)
	{
		if (check_am_i_dead(philo) == true)
		{
			pthread_mutex_unlock(&fork->fork_check);
			return (ERROR);
		}
		// if (had == NULL)
		// {
		// 	// write(1, "a\n", 2);
		// 	pthread_mutex_unlock(&fork->fork_check);
		// 	// write(1, "b\n", 2);
		// 	return (take_fork(philo, fork, NULL));
		// }
		if (had)
		{
			pthread_mutex_unlock(&fork->fork_check);
			put_fork(philo, had);
			usleep(10000);
			take_fork(philo, had, NULL);
			pthread_mutex_lock(&fork->fork_check);
			// take_fork(philo, fork, had);
		}
	}
	if (check_am_i_dead(philo) == true)
	{
		pthread_mutex_unlock(&fork->fork_check);
		return (ERROR);
	}
	pthread_mutex_lock(&fork->fork);
	fork->is_fork_available = false;
	pthread_mutex_unlock(&fork->fork_check);
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (check_am_i_dead(philo) == true)
	{
		put_fork(philo, fork);
		return (ERROR);
	}
	return (print_time(philo->philo_id, sec_milli, FORK, fork->fork_id));
}

int	put_fork(t_philo *philo, t_fork *fork)
{
	if (check_am_i_dead(philo) == true)
	{
		pthread_mutex_unlock(&fork->fork);
		fork->is_fork_available = false;
		return (ERROR);
	}
	if (pthread_mutex_unlock(&fork->fork))
		return (ERROR);
	fork->is_fork_available = true;
	return (SUCCESS);
}

bool	check_am_i_dead(t_philo *philo)
{
	bool	data;

	pthread_mutex_lock(&philo->dead_info->is_death_mutex);
	data = philo->dead_info->is_death;
	pthread_mutex_unlock(&philo->dead_info->is_death_mutex);
	return (data);
}

int	print_time(int id, long sec_milli, int act, int fork_id)
{
	char	*sec_milli_str;
	char	*id_str;
	char	*join;

	id_str = ft_itoa(id);
	sec_milli_str = ft_ltoa(sec_milli);
	join = ft_strjoin(sec_milli_str, " ");
	join = ft_strjoin(join, id_str);

	if (act == FORK)
	{
		// join = ft_strjoin(join, " has taken a fork ");
		// join = ft_strjoin(join, ft_itoa(fork_id));
		// join = ft_strjoin(join, "\n");
		join = ft_strjoin(join, " has taken a fork\n");
	}
	else if (act == EAT)
		join = ft_strjoin(join, " is eating\n");
	else if (act == THINK)
		join = ft_strjoin(join, " is thinking\n");
	else if (act == SLEEP)
		join = ft_strjoin(join, " is sleeping\n");
	else
	{
		join = ft_strjoin(join, " died\n");
		if (write(1, join, strlen(join)) == -1)
			return (ERROR);
		return (SUCCESS);
	}
	if (write(1, join, strlen(join)) == -1)
	{
		return (ERROR);
	}
	return (SUCCESS);
}
