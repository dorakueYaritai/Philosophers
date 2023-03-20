/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:29:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 15:39:40 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ret = print_time(philo->philo_id, sec_milli, LET_PUT_OFF_A_FORK, fork->fork_id);//
	fork->fork.is_available = true;
	if (pthread_mutex_unlock(&fork->fork.stuff))
		return (ERROR);
	return (ret);//
	// return (SUCCESS);
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

	if (act == LET_TAKE_A_FORK)
	{
		join = ft_strjoin(join, " has taken a fork ");
		join = ft_strjoin(join, ft_itoa(fork_id));
		join = ft_strjoin(join, "\n");
	}
	else if (act == LET_EAT)
		join = ft_strjoin(join, " is eating\n");
	else if (act == LET_THINK)
		join = ft_strjoin(join, " is thinking\n");
	else if (act == LET_SLEEP)
		join = ft_strjoin(join, " is sleeping\n");
	else if (act == LET_DEAD)
	{
		join = ft_strjoin(join, " died\n");
		if (write(1, join, strlen(join)) == -1)
			return (ERROR);
		return (SUCCESS);
	}
	if (write(1, join, strlen(join)) == -1)
		return (ERROR);
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
