/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:29:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/21 20:45:29 by kakiba           ###   ########.fr       */
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


bool	check_am_i_dead(t_philo *philo)
{
	bool	data;

	ft_pthread_mutex_lock(&philo->dead_info->mutex);
	data = philo->dead_info->is_death;
	ft_pthread_mutex_unlock(&philo->dead_info->mutex);
	return (data);
}


static int	exe_act(t_philo *philo, int act)
{
	struct timeval t1;
	long sec_milli;
	long time;
	int	answer;
	char	*join;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_wish_status(philo->wish, act, sec_milli, NONE, philo->philo_id);
	while (1)
	{
		answer = is_wish_come(philo->wish, philo->philo_id);
		if (answer == LET_OK)
			break;
		else if (answer == LET_YOU_ARE_ALREADY_DEAD)
		{
			return (ERROR);
		}
		// usleep(10);
	}
	if (act == LET_EAT)
	{
		if (update_time_to_die(philo, sec_milli + philo->status.time_to_starve) == FINISH)
			return (ERROR);
		usleep((unsigned int)(philo->status.time_to_eat) * 1000);
	}
	else if (act == LET_SLEEP)
		usleep((unsigned int)(philo->status.time_to_sleep) * 1000);
	return (SUCCESS);
}

// exe act の原型
static int	exe_act(t_philo *philo, int act)
{
	struct timeval t1;
	long sec_milli;
	long time;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (check_am_i_dead(philo))
		return (ERROR);
	// この間で dead している可能性がある
	// dead を monitor が観測して出力も行う場合
	// この間で出力が行われて、dead の後に act が行われうる
	// dead の出力を usleep() してから行うという回避方法があるみたいだが、本質的じゃ無い感じがした
	// なぜなら並行プログラミングでは計算順序が未定義であり、特にシングルコアCPUの場合、
	// usleep()してからでもここにスイッチされない可能性がある。
	// まあその場合並行プログラミングといえるかわからないけどw
	// でもsleep()で回避できてる気はしない

	// dead をphilo 自身が出力する場合
	// deadが出力された後にactは起こらないことが確定するが
	// act する前に dead している可能性が前述の通りあるので、
	// 次回の check_am_i_dead で死を発見し、タイムスタンプが逆転する可能性がある
	// 300 1 is sleeping
	// 299 1 is dead みたいな感じ

	if (print_time(philo->philo_id, sec_milli, act, NONE) == ERROR)
		return (ERROR);
	if (act == LET_EAT)
	{
		update_time_to_die(philo, sec_milli + philo->status.time_to_starve);
		usleep((unsigned int)(philo->status.time_to_eat) * 1000);
		// update_time_to_die(philo, sec_milli + philo->time_to_starve);
		// usleep((unsigned int)(philo->time_to_eat) * 1000);
	}
	else if (act == LET_SLEEP)
	{
		usleep((unsigned int)(philo->status.time_to_sleep) * 1000);
		// usleep((unsigned int)(philo->time_to_sleep) * 1000);
	}
	return (SUCCESS);
}


bool	is_neighbor_hungry(t_philo *philo, t_fork *fork)
{
	int	own_id;
	int neighbor_id;
	bool	ret;

	if (fork == NULL)
		return (false);
	own_id = philo->philo_id % 2;
	neighbor_id = (own_id + 1) % 2;
	pthread_mutex_lock(&fork->check_request_status);
	// if (fork->request_status[own_id] < fork->request_status[neighbor_id])
	// 	ret = true;
	if (fork->life_expectancy[own_id] > fork->life_expectancy[own_id])
		ret = true;
	else
		ret = false;
	pthread_mutex_unlock(&fork->check_request_status);
	return (ret);
}

int	be_kind_neighbors(t_philo *philo, t_fork *fork, t_fork *had)
{
	bool	had_side;
	bool	fork_side;

	had_side = is_neighbor_hungry(philo, had); 
	fork_side = is_neighbor_hungry(philo, fork);
	if (had_side == true)
	{
		put_fork(philo, had);
		usleep(10);
		return (take_fork(philo, fork, NULL));
	}
	else if (had_side == false && fork_side == true)
	{
		usleep(10);
		return (take_fork(philo, fork, had));
	}
	else
		return (0);
}

int	update_request_status(t_philo *philo, t_fork *fork, t_fork *had)
{
	struct timeval t1;
	long	sec_milli;
	long	time;
	int		status;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	time = philo->time_to_die - sec_milli;
	if (time < philo->time_to_eat)
		status = SITTING_ON_A_COFFIN;
	else if (time < philo->time_to_eat + philo->time_to_sleep)
		status = SITTING_ON_A_COFFIN;
	else
		status = FULL;
	pthread_mutex_lock(&fork->check_request_status);
	if (had)
	{
		pthread_mutex_lock(&had->check_request_status);
		had->request_status[philo->philo_id % 2] = status;
		had->life_expectancy[philo->philo_id % 2] = time;
	}
	fork->request_status[philo->philo_id % 2] = status;
	fork->life_expectancy[philo->philo_id % 2] = time;
	if (had)
		pthread_mutex_unlock(&had->check_request_status);
	pthread_mutex_unlock(&fork->check_request_status);
}
