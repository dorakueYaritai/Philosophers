/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:29:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 00:24:53 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num);
static int	threads_join(pthread_t *th_id, int philo_num);

// bus error が出た。なんでだろ
// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	if (ft_pthread_mutex_lock(&fork->fork) == ERROR)
// 		ft_return (philo, ERROR);
// 	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
// 	{
// 		put_fork(philo, fork);
// 		ft_return (philo, ERROR);
// 	}
// 	return (SUCCESS);
// }

// // bus error が出た。なんでだろ
// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	while (ft_pthread_mutex_trylock(&fork->fork) == ERROR)
// 	{
// 		// if (had != NULL)
// 		// {
// 		// 	put_fork(philo, had);
// 		// 	return (take_forks(philo));
// 		// }
// 	}
// 	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
// 	{
// 		put_fork(philo, fork);
// 		ft_return (philo, ERROR);
// 	}
// 	return (SUCCESS);
// }

int main(int argc, char* argv[]) {
	t_philo		*philos;
	pthread_t	*th_id;
	t_share		share;
	t_status	status;

	// printf("OKQ\n");
	if (parse_argment(argc, argv) != SUCCESS)
		return (1);
	// printf("OKQ\n");
	if (init_status(&status, argv, argc) == ERROR)
		return (1);
	init_share(&share, &status, argv[1]);
	philos = init_philos(&status, &share);
	th_id = init_th_id(share.philo_num);
	if (threads_create(philos, th_id, share.philo_num) == 1)
	{
		
		return (1);
	}
	monitor_philos_death(&share);
	if (threads_join(th_id, share.philo_num) == 2)
		return (2);
	return (0);
}

// int kill_everyone(t_share *share)
// {
// 	int	i;

// 	i = 0;
// 	while (i < share->philo_num)
// 	{
// 		if (ft_pthread_mutex_lock(&share->wishs[i].mutex))
// 			return (ERROR);
// 		share->wishs[i].request = LET_DEAD;
// 		if (ft_pthread_mutex_unlock(&share->wishs[i].mutex))
// 			return (ERROR);
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// bool	did_the_old_man_go_heaven(t_share *share, int id)
// {
// 	struct timeval	t1;
// 	long			sec_milli;

// 	sec_milli = ft_get_time_in_millisec();
// 	if (sec_milli == -1)
// 		return (true);
// 	if (share->philos_time_to_dead[id] < sec_milli && share->philos_time_to_dead[id] != -1)
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

// int	listen_to_old_guys_request(t_share *share, int id)
// {
// 	t_wish	*wish;
// 	int		request;
// 	long	sec_milli;
// 	int		fork_id;

// 	wish = &share->wishs[id];
// 	ft_pthread_mutex_lock(&wish->mutex);
// 	request = wish->request;
// 	if (request == LET_INIT)
// 	{
// 		share->philos_time_to_dead[id] = (wish->sec_milli + share->time_to_starve);
// 		wish->request = LET_OK;
// 	}
// 	if (did_the_old_man_go_heaven(share, id) == true)
// 	{
// 		ft_pthread_mutex_unlock(&wish->mutex);
// 		enqueue_log_msg_to_writer(share, id, share->philos_time_to_dead[id], LET_DEAD);
// 		return (FOUND_DEAD);
// 	}
// 	if (request == LET_TRY_TO_TAKE_FORKS && is_ok_the_guy_eat2(share, id, share->philo_num))
// 		wish->request = LET_OK;
// 	if (request != LET_EAT && request != LET_SLEEP && request != LET_THINK &&
// 			request != LET_TAKE_A_FORK)
// 	{
// 		ft_pthread_mutex_unlock(&wish->mutex);
// 		return (SUCCESS);
// 	}
// 	sec_milli = wish->sec_milli;
// 	fork_id = wish->fork_id;
// 	wish->request = LET_OK;
// 	ft_pthread_mutex_unlock(&wish->mutex);
// 	if (enqueue_log_msg_to_writer(share, id, sec_milli, request) == ERROR)
// 		return (ERROR);
// 	if (request == LET_EAT)
// 	{
// 		share->philos_time_to_dead[id] = (sec_milli + share->time_to_starve);
// 		++share->philos_eat_times[id];
// 	}
// 	return (SUCCESS);
// }

// int	monitor_philos_death(t_share *share)
// {
// 	int	id;
// 	int	num;
// 	int	ret;

// 	num = share->philo_num;
// 	id = 0;
// 	while (1)
// 	{
// 		ret = listen_to_old_guys_request(share, id);
// 		if (ret)
// 		{
// 			kill_everyone(share);
// 			enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
// 			return (ret);
// 		}
// 		if (is_must_eat_times_fulfilled(share) == true)
// 		{
// 			kill_everyone(share);
// 			enqueue_log_msg_to_writer(share, -1, -1, WRITER_END);
// 			return (SUCCESS);
// 		}
// 		++id;
// 		if (id == num)
// 			id = 0;
// 	}
// 	return (0);
// }

	// int i = 0;
	// while (i < share.philo_num)
	// {
	// 	printf("%p\n", &(philos[i].status.must_eat_times));
	// 	printf("%p\n", (share.dead_info[i].must_eat_times));
	// 	printf("--  --\n");
	// 	i++;
	// }

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&th_id[i], NULL, &routine_init, &philos[i]) != 0)
		{
			// printf("[FOOOOOOOOOOOO!!!]\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	threads_join(pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	// write(1, "join!\n", 6);
	// printf("join !\n");
	while (i < philo_num)
	{
		if (pthread_join(th_id[i], NULL) != 0)
		{
			// printf("[NOOOOOOOOOOON!!!!!!!!]\n");
			return (2);
		}
		i++;
	}
	return (0);
}


int	update_time_to_die(t_philo *philo, long new_time_to_die)
{
	ft_pthread_mutex_lock(&philo->dead_info->mutex);
	*philo->dead_info->time_to_die = new_time_to_die;
	philo->status.must_eat_times -= 1;

	// *(philo->dead_info->must_eat_times) -= 1;
	// if (--philo->status.must_eat_times == 0)
	// 	return (FINISH);
	ft_pthread_mutex_unlock(&philo->dead_info->mutex);
	return (SUCCESS);
}

static void	birth_philo_baby(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_time_to_die(philo, sec_milli + philo->status.time_to_starve);
	// update_time_to_die(philo, sec_milli + philo->time_to_starve);
}

// 上と同義だと思うけど、ちょっと怖いから残してる
// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	struct timeval t1;
// 	long sec_milli;
// 	int				ret;
// 	int				answer;

// 	// while (ft_pthread_mutex_trylock(&fork->fork) == ERROR)
// 	// {
// 	// 	;
// 	// }
// 	ft_pthread_mutex_lock(&fork->fork);
// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	update_wish_status(philo->wish, LET_TAKE_A_FORK, sec_milli, fork->fork_id, philo->philo_id);
// 	while (1)
// 	{
// 		answer = is_wish_come(philo->wish, philo->philo_id);
// 		if (answer == LET_YOU_ARE_ALREADY_DEAD)
// 		{
// 			put_fork(philo, fork);
// 			return (ERROR);
// 		}
// 		if (answer == LET_OK)
// 			return (SUCCESS);
// 	}
// }

// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	struct timeval t1;
// 	long sec_milli;
// 	int				ret;

// 	while (1)
// 	{
// 		if (ft_pthread_mutex_trylock(&fork->fork) == SUCCESS)
// 			break;
// 		if (had)
// 		{
// 			if (put_fork(philo, had) == ERROR)
// 				return (ERROR);
// 			// usleep(100);
// 			return (take_forks(philo));
// 		}
// 	}
// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	update_wish_status(philo->wish, LET_TAKE_A_FORK, sec_milli, NONE);
// 	int	answer;
// 	while (1)
// 	{
// 		answer = is_wish_come(philo->wish);
// 		if (answer == LET_OK)
// 			break;
// 		else if (answer == LET_YOU_ARE_ALREADY_DEAD)
// 			return (ERROR);
// 		// ulseep(10);
// 	}
// 	ret = print_time(philo->philo_id, sec_milli, LET_TAKE_A_FORK, fork->fork_id);
// 	return (ret);
// }

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


// bool	is_ok_the_guy_eat(t_dead *dead_info, int id, int num)
int	is_ok_the_guy_eat(t_share *share,int id, int num)
{
	int left_id;
	int right_id;
	int	ret;
	time_t	array[3];

	// return (true);
	// if (guys_forks_avilable(share->forks, id, num) == true)
	// 	return (true);
	// if (guys_forks_avilable(share, id, num) == true)
	// 	return (true);
	left_id = ft_positive_mod(id - 1, num);
	right_id = ft_positive_mod(id + 1, num);
	ft_pthread_mutex_lock(&share->dead_info[id].mutex);
	array[0] = *share->dead_info[id].time_to_die;
	ft_pthread_mutex_unlock(&share->dead_info[id].mutex);

	ft_pthread_mutex_lock(&share->dead_info[left_id].mutex);
	array[1] = *share->dead_info[left_id].time_to_die;
	ft_pthread_mutex_unlock(&share->dead_info[left_id].mutex);

	ft_pthread_mutex_lock(&share->dead_info[right_id].mutex);
	array[2] = *share->dead_info[right_id].time_to_die;
	ft_pthread_mutex_unlock(&share->dead_info[right_id].mutex);

	// 死にそうランキング1位タイだったらOK
	// ultra_debug(id, left_id, right_id, share->dead_info);

	if (array[0] <= array[1] && array[0] <= array[2])
		return (LET_OK);
	else if (array[1] == -1 || array[2] == -1)
		return (LET_OK);
	else
		return (LET_TRY_TO_TAKE_FORKS);
}


int	is_ok_the_guy_eat2(t_share *share,int id, int num)
{
	int left_id;
	int right_id;
	char	*str;

	left_id = ft_positive_mod(id - 1, num);
	right_id = ft_positive_mod(id + 1, num);

	// if (guys_forks_avilable(share, left_id, right_id, num) == true)
	// 	return (LET_OK);

	// if (are_forks_not_avilable(share, left_id, right_id, num) == true)
	// 	return (LET_TRY_TO_TAKE_FORKS);

	if (share->philos_time_to_dead[id] <= share->philos_time_to_dead[left_id] && \
		share->philos_time_to_dead[id] <= share->philos_time_to_dead[right_id])
	{
		// str = ft_strjoin(ft_ltoa(id), "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(left_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[left_id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(right_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[right_id]));
		// str = ft_strjoin(str, "\n");
		// write(1, str, ft_strlen(str));
		return (true);
	}
	else if (share->philos_time_to_dead[left_id] == -1 \
		|| share->philos_time_to_dead[right_id] == -1)
	{
		// str = ft_strjoin(ft_ltoa(id), "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(left_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[left_id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(right_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[right_id]));
		// str = ft_strjoin(str, "\n");
		return (true);
	}
	else
	{
		// str = ft_strjoin("false dayo!", ft_ltoa(id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(left_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[left_id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(right_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[right_id]));
		// str = ft_strjoin(str, "\n");
		return (false);
	}
}

// int	feed_time_check(t_share *share, int id)
// {
// 	t_wish	*wish;

// 	wish = &share->wishs[id];
// 	ft_pthread_mutex_lock(&wish->mutex);
// 	if (wish->let_me_eat == LET_TRY_TO_TAKE_FORKS)
// 	{
// 		if (is_ok_the_guy_eat(share, id, share->philo_num) == true)
// 			wish->let_me_eat = LET_OK;
// 	}
// 	ft_pthread_mutex_unlock(&wish->mutex);
// 	return (SUCCESS);
// }
