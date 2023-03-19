/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 15:02:25 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	update_wish_status(t_wish *wish)
{
	ft_pthread_mutex_lock(&wish->mutex);
	wish->let_me_eat = PLEASE;
	ft_pthread_mutex_unlock(&wish->mutex);
}

bool	is_wish_come(t_wish *wish)
{
	bool	ret;

	if (ft_pthread_mutex_lock(&wish->mutex))
		return (false);
	if (wish->let_me_eat == OK)
		ret = true;
	else
		ret = false;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (false);
	return (ret);
}

int	thanks_a_host(t_wish *wish)
{
	if (ft_pthread_mutex_lock(&wish->mutex))
		return (ERROR);
	wish->let_me_eat = THANK_YOU;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (ERROR);
	return (SUCCESS);
}

int	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	first = philo->forks[FIRST];
	second = philo->forks[SECOND];
	update_wish_status(philo->wish);
	while (1)
	{
		if (is_wish_come(philo->wish) == true)
		{
			thanks_a_host(philo->wish);
			break;
		}
		if (check_am_i_dead(philo) == true)
			return (ERROR);
	}
	// write(1, "a", 1);
	if (take_fork(philo, first, NULL) == ERROR)
		return (ERROR);
	if (take_fork(philo, second, first) == ERROR)
	{
		put_fork(philo, first);
		return (ERROR);
	}
	// if (take_fork(philo, philo->forks[FIRST], NULL) == ERROR)
	// 	return (ERROR);
	// if (take_fork(philo, philo->forks[SECOND], philo->forks[FIRST]) == ERROR)
	// {
	// 	put_fork(philo, philo->forks[FIRST]);
	// 	return (ERROR);
	// }
	return (0);
}

int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
{
	struct timeval t1;
	long sec_milli;

	while (1)
	{
		// update_request_status(philo, fork, had);
		// be_kind_neighbors(philo, fork, had);
		if (check_am_i_dead(philo) == true)
			return (ERROR);
		if (ft_pthread_mutex_trylock(&fork->fork) == SUCCESS)
			break;
	}
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

int	put_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	first = philo->forks[FIRST];
	second = philo->forks[SECOND];
	if (put_fork(philo, first) == ERROR)
		return (ERROR);
	if (put_fork(philo, second) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

bool	check_am_i_dead(t_philo *philo)
{
	bool	data;

	ft_pthread_mutex_lock(&philo->dead_info->mutex);
	data = philo->dead_info->is_death;
	ft_pthread_mutex_unlock(&philo->dead_info->mutex);
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
	else if (act == DEAD)
	{
		join = ft_strjoin(join, " died\n");
		if (write(1, join, strlen(join)) == -1)
			return (ERROR);
		return (SUCCESS);
	}
	else if (act == PUTOFF)
	{
		join = "";
		// join = ft_strjoin(join, " has put off a fork ");
		// join = ft_strjoin(join, ft_itoa(fork_id));
		// join = ft_strjoin(join, "\n");

		// join = ft_strjoin(join, " has put off a fork\n");
	}
	if (write(1, join, strlen(join)) == -1)
	{
		return (ERROR);
	}
	return (SUCCESS);
}

// bool	is_neighbor_hungry(t_philo *philo, t_fork *fork)
// {
// 	int	own_id;
// 	int neighbor_id;
// 	bool	ret;

// 	if (fork == NULL)
// 		return (false);
// 	own_id = philo->philo_id % 2;
// 	neighbor_id = (own_id + 1) % 2;
// 	pthread_mutex_lock(&fork->check_request_status);
// 	// if (fork->request_status[own_id] < fork->request_status[neighbor_id])
// 	// 	ret = true;
// 	if (fork->life_expectancy[own_id] > fork->life_expectancy[own_id])
// 		ret = true;
// 	else
// 		ret = false;
// 	pthread_mutex_unlock(&fork->check_request_status);
// 	return (ret);
// }

// int	be_kind_neighbors(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	bool	had_side;
// 	bool	fork_side;

// 	had_side = is_neighbor_hungry(philo, had);
// 	fork_side = is_neighbor_hungry(philo, fork);
// 	if (had_side == true)
// 	{
// 		put_fork(philo, had);
// 		usleep(10);
// 		return (take_fork(philo, fork, NULL));
// 	}
// 	else if (had_side == false && fork_side == true)
// 	{
// 		usleep(10);
// 		return (take_fork(philo, fork, had));
// 	}
// 	else
// 		return (0);
// }

// int	update_request_status(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	struct timeval t1;
// 	long	sec_milli;
// 	long	time;
// 	int		status;

// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	time = philo->time_to_die - sec_milli;
// 	if (time < philo->time_to_eat)
// 		status = SITTING_ON_A_COFFIN;
// 	else if (time < philo->time_to_eat + philo->time_to_sleep)
// 		status = SITTING_ON_A_COFFIN;
// 	else
// 		status = FULL;
// 	pthread_mutex_lock(&fork->check_request_status);
// 	if (had)
// 	{
// 		pthread_mutex_lock(&had->check_request_status);
// 		had->request_status[philo->philo_id % 2] = status;
// 		had->life_expectancy[philo->philo_id % 2] = time;
// 	}
// 	fork->request_status[philo->philo_id % 2] = status;
// 	fork->life_expectancy[philo->philo_id % 2] = time;
// 	if (had)
// 		pthread_mutex_unlock(&had->check_request_status);
// 	pthread_mutex_unlock(&fork->check_request_status);
// }
