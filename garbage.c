/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:29:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/31 13:33:24 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>


int	lock_data_avoiding_race(t_share *share, int own_id, int num)
{
	int	left_id;
	int	right_id;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (share->philo_num == 1)
	{
		printf("1A! : %d: %d\n", share->philo_id, own_id);
		return (ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex));
	}
	else if (share->philo_num == 2)
	{
		printf("2B! : %d: %d\n", share->philo_id, own_id);
		return (lock_for_two_people(share, own_id, left_id));
	}

	// if (ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex))
	// {
	// 	printf("NO\n");
	// 	return (ERROR);
	// }
	// printf("1! : %d: %d\n", share->philo_id, left_id);
	// if (ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex))
	// {
	// 	printf("NO\n");
	// 	return (ERROR);
	// }
	// printf("2! : %d: %d\n", share->philo_id, own_id);
	// if (ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex))
	// {
	// 	printf("NO\n");
	// 	return (ERROR);
	// }
	// printf("3! : %d: %d\n", share->philo_id, right_id);
	// lock_mini_first(share, left_id, own_id, right_id);

	if (own_id < left_id && own_id < right_id)
	{
		// printf("1! : %d: %d\n", share->philo_id, left_id);
		return (lock_mini_first(share, own_id, left_id, right_id));
		// printf("DONE\n");
	}
	else if (left_id < own_id && left_id < right_id)
	{
		// printf("2! : %d: %d\n", share->philo_id, left_id);
		return (lock_mini_first(share, left_id, own_id, right_id));
		// printf("DONE\n");
	}
	else
	{
		// printf("3! : %d: %d\n", share->philo_id, right_id);
		return (lock_mini_first(share, right_id, left_id, own_id));
		// printf("DONE\n");
	}
	return (SUCCESS);
}

int	unlock_data_avoiding_race(t_share *share, int own_id, int num)
{
	int	left_id;
	int	right_id;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (share->philo_num == 1)
		return (ft_pthread_mutex_unlock \
			(&share->time_to_die_array[own_id].mutex));
	else if (share->philo_num == 2)
		return (unlock_for_two_people(share, own_id, left_id));
	// unlock_mini_first(share, left_id, own_id, right_id);

	// if (ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex))
	// {
		// printf("FOO!\n");
	// 	return (ERROR);
	// }
	printf("a! : %d: %d\n", share->philo_id, left_id);
	// if (ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex))
	// {
		// printf("FOO!\n");
	// 	return (ERROR);
	// }
	printf("b! : %d: %d\n", share->philo_id, own_id);
	// if (ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex))
	// {
		// printf("FOO!\n");
	// 	return (ERROR);
	// }
	printf("c! : %d: %d\n", share->philo_id, right_id);

	if (own_id < left_id && own_id < right_id)
	{
		// printf("A! : %d: %d\n", share->philo_id, left_id);
		return (unlock_mini_first(share, own_id, left_id, right_id));
		// printf("DONE\n");
	}
	else if (left_id < own_id && left_id < right_id)
	{
		// printf("B! : %d: %d\n", share->philo_id, left_id);
		return (unlock_mini_first(share, left_id, own_id, right_id));
		// printf("DONE\n");
	}
	else
	{
		// printf("C! : %d: %d\n", share->philo_id, right_id);
		return (unlock_mini_first(share, right_id, left_id, own_id));
		// printf("DONE\n");
	}

	// if (own_id < left_id && own_id < right_id)
	// 	return (unlock_mini_first(share, own_id, left_id, right_id));
	// else if (left_id < own_id && left_id < right_id)
	// 	return (unlock_mini_first(share, left_id, own_id, right_id));
	// else
	// 	return (unlock_mini_first(share, right_id, own_id, left_id));
	return (SUCCESS);
}

// int	exe_act(t_philo *philo, int act)
// {
// 	int				answer;
// 	t_wish_info		info;

// 	info.act_time = ft_get_time_in_millisec();
// 	if (info.act_time == -1)
// 		return (ERROR);
// 	info.request = act;
// 	info.fork_id = NONE;
// 	if (update_wish_status(philo->wish, &info) == ERROR)
// 		return (ERROR);
// 	if (act == LET_EAT)
// 		ft_msleep(philo->status.time_to_eat);
// 	else if (act == LET_SLEEP)
// 		ft_msleep(philo->status.time_to_sleep);
// 	else if (act == LET_DEAD)
// 		return (ERROR);
// 	while (1)
// 	{
// 		usleep(10);
// 		answer = get_monitor_answer(philo->wish);
// 		if (answer == LET_OK)
// 			break ;
// 		else if (answer == LET_DEAD)
// 			return (ERROR);
// 	}
// 	return (SUCCESS);
// }

int	print_time(int id, long sec_milli, int act)
{
	char	*out_put;

	out_put = make_msg(id, sec_milli, act);
	if (out_put == NULL)
		return (ERROR);
	if (write(1, out_put, ft_strlen(out_put)) == -1)
		return (ERROR);
	free (out_put);
	if (act == LET_DEAD)
		return (ERROR);
	return (SUCCESS);
}


// static int	ft_usleep(long now_time, long sleep_time)
// {
// 	const long	goal_time = now_time + sleep_time / 1000;

// 	while (goal_time < ft_get_time_in_millisec());
// 		;
// 	return (0);
// }

// int	writer_exe(t_queue *queue)
// {
// 	t_list	*node;
// 	size_t	len;
// 	bool	do_proceed;

// 	do_proceed = true;
// 	while (do_proceed || node)
// 	{
// 		ft_pthread_mutex_lock(&queue->mutex);
// 		node = ft_dequeue(&queue->list);
// 		do_proceed = queue->do_proceed;
// 		ft_pthread_mutex_unlock(&queue->mutex);
// 		if (node == NULL)
// 		{
// 			usleep(10000);
// 			continue ;
// 		}
// 		// if (node->content == NULL)
// 		// 	continue ;
// 		len = ft_strlen(node->content);
// 		if (write(1, node->content, len) == -1)
// 		{
// 			return (ERROR);
// 		}
// 		free (node->content);
// 		free (node);
// 		usleep(10000);
// 	}
// 	return (0);
// }

static int	init_philo_sub(t_philo *philo, t_status *status, t_share *share)
{
	int	i;
	int	philo_num;

	philo_num = share->philo_num;
	i = philo->philo_id;
	philo->status = *status;
	philo->wish = &share->wishs[i];

	// philo->forks[FIRST] = &share->forks[i];
	// philo->forks[SECOND] = &share->forks[(i + 1) % philo_num];

	// if (i == 0)
	// {
	// 	philo->forks[FIRST] = &share->forks[(i + 1) % philo_num];
	// 	philo->forks[SECOND] = &share->forks[i];
	// }
	// else
	// {
	// 	philo->forks[FIRST] = &share->forks[i];
	// 	philo->forks[SECOND] = &share->forks[(i + 1) % philo_num];
	// }

	// if (i % 2 == 0)
	// {
	// 	philo->forks[FIRST] = &share->forks[i];
	// 	philo->forks[SECOND] = &share->forks[(i + 1) % philo_num];
	// }
	// else
	// {
	// 	philo->forks[FIRST] = &share->forks[(i + 1) % philo_num];
	// 	philo->forks[SECOND] = &share->forks[i];
	// }

	return (SUCCESS);
}


// ================
// isok は悩んでいる
// int	is_ok_the_guy_take_forks(t_share *share, int own_id, int num)
// {
// 	int		left_id;
// 	int		right_id;

// 	left_id = ft_positive_mod(own_id - 1, num);
// 	right_id = ft_positive_mod(own_id + 1, num);
// 	share->time_to_die_array[own_id].eating_status = E_HUNGRY;
// 	if (left_id == own_id || right_id == own_id)
// 	{
// 		return (false);
// 	}
// 	if (share->time_to_die_array[left_id].eating_status != E_HUNGRY)
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

// int	is_ok_the_guy_take_forks(t_share *share, int own_id, int num)
// {
// 	int left_id;
// 	int right_id;
// 	// char	*str;

// 	left_id = ft_positive_mod(own_id - 1, num);
// 	right_id = ft_positive_mod(own_id + 1, num);
// 	if (left_id == own_id || right_id == own_id)
// 	{
// 		// str = ft_strjoin(ft_itoa(own_id), ":");
// 		// str = ft_strjoin(str, ft_itoa(left_id));
// 		// str = ft_strjoin(str, ":");
// 		// str = ft_strjoin(str, ft_itoa(right_id));
// 		// str = ft_strjoin(str, "  same id false \n");
// 		// write(1, str, ft_strlen(str));
// 		return (false);
// 	}
// 	if (share->time_to_die_array[left_id].eating_status == false || 
// 		share->time_to_die_array[right_id].eating_status == false)
// 	{
// 		// str = ft_strjoin(ft_itoa(own_id), ":");
// 		// str = ft_strjoin(str, ft_itoa(left_id));
// 		// str = ft_strjoin(str, ":");
// 		// str = ft_strjoin(str, ft_itoa(right_id));
// 		// str = ft_strjoin(str, "  true \n");
// 		// write(1, str, ft_strlen(str));
// 		return (true);
// 	}
// 		// str = ft_strjoin(ft_itoa(own_id), ":");
// 		// str = ft_strjoin(str, ft_itoa(left_id));
// 		// str = ft_strjoin(str, ":");
// 		// str = ft_strjoin(str, ft_itoa(right_id));
// 		// str = ft_strjoin(str, "  false \n");
// 		// write(1, str, ft_strlen(str));
// 	return (false);
// }

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num);
static int	threads_join(pthread_t *th_id, int philo_num);

int	unlock_right_own_left(t_share *share,int own_id, int num)
{
	int left_id;
	int right_id;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (share->philo_num == 1)
		return (unlock_for_one(share, own_id));
	else if (share->philo_num == 2)
		return (unlock_for_two_people(share, own_id, left_id));
	if (own_id < left_id && own_id < right_id)
	{
		unlock_mini_first(share, own_id, left_id, right_id);
		// ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		// if (left_id < right_id)
		// {
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		// }
		// else
		// {
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		// }
	}
	else if (left_id < own_id && left_id < right_id)
	{
		unlock_mini_first(share, left_id, own_id, right_id);
		// ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		// if (own_id < right_id)
		// {
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		// }
		// else
		// {
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		// }
	}
	else
	{
		unlock_mini_first(share, right_id, own_id, left_id);
		// ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		// if (own_id < left_id)
		// {
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		// }
		// else
		// {
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		// 	ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		// }
	}
	return (0);
}

static int	save_request(t_wish_info *info, t_wish_info *philo_request)
{
	info->act_time = philo_request->act_time;
	info->fork_id = philo_request->fork_id;
	info->request = philo_request->request;
	return (0);
}

// wishs という配列に、それぞれのphiloからのrequest内容が入っている
int	answer_to_philo_request(t_share *share, int id)
{
	t_wish			*wish;
	t_wish_info		save_request_info;

	wish = &share->wishs[id];
	if (lock_data_avoiding_race(share, id, share->philo_num) == ERROR)
		return (ERROR);
	ft_pthread_mutex_lock(&wish->mutex);
	save_request(&save_request_info, &wish->request_info);
	if (answer_request(share, wish, id, save_request_info) == FOUND_DEAD)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		unlock_data_avoiding_race(share, id, share->philo_num);
		return (FOUND_DEAD);
	}
	update_dead_time(share, id, save_request_info);
	ft_pthread_mutex_unlock(&wish->mutex);
	unlock_data_avoiding_race(share, id, share->philo_num);
	return (SUCCESS);
}
// int	answer_to_philo_request(t_share *share, int id)
// {
// 	t_wish			*wish;
// 	t_wish_info		info;

// 	wish = &share->wishs[id];
// 	ft_pthread_mutex_lock(&wish->mutex);
// 	save_request(&info, &wish->request_info);
// 	if (did_the_old_man_go_heaven(share, id) == true)
// 	{
// 		ft_pthread_mutex_unlock(&wish->mutex);
// 		enqueue_log_msg_to_writer(share, id, share->philos_time_to_dead[id], LET_DEAD);
// 		return (FOUND_DEAD);
// 	}
// 	answer_request(share, wish, id, info.request);
// 	ft_pthread_mutex_unlock(&wish->mutex);
// 	if (enqueue_log_msg_to_writer(share, id, info.act_time, info.request) == ERROR)
// 	{
// 		return (ERROR);
// 	}
// 	// update_dead_time(share, id)
// 	if (info.request == LET_EAT || info.request == LET_INIT)
// 	{
// 		share->philos_time_to_dead[id] = (info.act_time + share->time_to_starve);
// 		if (info.request == LET_EAT)
// 			++share->philos_eat_times[id];
// 	}
// 	return (SUCCESS);
// }


// int	answer_request(t_share *share, t_wish *wish, int id, t_wish_info info)
// {
// 	if (did_the_old_man_go_heaven(share, id) == true)
// 	{
// 		enqueue_log_msg_to_writer(share, id, 
// 			share->time_to_die_array[id].time_to_die, LET_DEAD);
// 		ft_pthread_mutex_unlock(&wish->mutex);
// 		answer_dead_to_all_request(share);
// 		return (FOUND_DEAD);
// 	}
// 	else if (info.request == LET_DEAD)
// 	{
// 		enqueue_log_msg_to_writer(share, id, info.act_time, LET_DEAD);
// 		ft_pthread_mutex_unlock(&wish->mutex);
// 		answer_dead_to_all_request(share);
// 		return (FOUND_DEAD);
// 	}
// 	else if (info.request == LET_TRY_TO_TAKE_FORKS)
// 	{
// 		if (whethre_allow_taking_the_fork(share, id, share->philo_num))
// 		{
// 			wish->request_info.request = LET_OK;
// 			share->time_to_die_array[id].is_taking_fork = true;
// 		}
// 	}
// 	else
// 		wish->request_info.request = LET_OK;
// 	return (SUCCESS);
// }

// bus error が出た。なんでだろ
// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	if (ft_pthread_mutex_lock(&fork->fork) == ERROR)
// 		return (ERROR);
// 	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
// 	{
// 		put_fork(philo, fork);
// 		return (ERROR);
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
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }

static int	init_philo_sub(t_philo *philo, t_status *status, t_share *share)
{
	int	i;
	int	philo_num;

	philo_num = share->philo_num;
	i = philo->philo_id;
	// philo->status = *status;
	philo->status.time_to_starve = status->time_to_starve;
	philo->status.time_to_eat = status->time_to_eat;
	philo->status.time_to_sleep = status->time_to_sleep;
	philo->status.time_to_die = status->time_to_die;
	philo->status.must_eat_times = status->must_eat_times;
	philo->wish = &share->wishs[i];
	if (i % 2 == 0)
	{
		philo->forks[FIRST] = &share->forks[i];
		philo->forks[SECOND] = &share->forks[(i + 1) % philo_num];
	}
	else
	{
		philo->forks[FIRST] = &share->forks[(i + 1) % philo_num];
		philo->forks[SECOND] = &share->forks[i];
	}
	return (SUCCESS);
}

t_share	*init_shares(t_share *share)
{
	t_share	*share_array;
	long	i;

	share_array = malloc(sizeof(t_share) * share->philo_num);
	if (share_array == NULL)
		return (NULL);
	i = 0;
	while (i < share->philo_num)
	{
		share_array[i].forks = share->forks;
		share_array[i].must_eat_times = share->must_eat_times;
		share_array[i].must_eat_times_exists = share->must_eat_times_exists;
		share_array[i].philo_id = i;
		share_array[i].philo_num = share->philo_num;
		share_array[i].philos_eat_times = share->philos_eat_times;
		share_array[i].philos_time_to_dead = share->philos_time_to_dead;
		share_array[i].queue = share->queue;
		share_array[i].th_id = share->th_id;
		share_array[i].time_to_starve = share->time_to_starve;
		share_array[i].wishs = share->wishs;
		i++;
	}
	return (share_array);
}

#include <libft.h>
#include <philosophers.h>

int	init_share(t_share *share, t_status *status, char *philo_num_arg)
{
	int	i;

	share->philo_num = ft_strtol(philo_num_arg, NULL, 10);
	share->wishs = init_wishs(share->philo_num);
	share->forks = init_fork(share->philo_num);
	share->queue = init_queue();
	share->philos_time_to_dead = malloc(sizeof(time_t) * share->philo_num);
	share->philos_eat_times = malloc(sizeof(int) * share->philo_num);
	i = 0;
	while (i < share->philo_num)
	{
		share->philos_time_to_dead[i] = -1;
		share->philos_eat_times[i] = 0;
		i++;
	}
	if (status->must_eat_times < 0)
		share->must_eat_times_exists = false;
	else
		share->must_eat_times_exists = true;
	share->time_to_starve = status->time_to_starve;
	share->must_eat_times = status->must_eat_times;
	return (0);
}

t_fork	*init_fork(int philo_num)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * philo_num);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < philo_num)
	{
		if (init_shared_resourse(&forks[i].fork) == ERROR)
			return (NULL);
		forks[i].fork_id = i;
		i++;
	}
	return (forks);
}

t_wish	*init_wishs(int philo_num)
{
	t_wish	*wishs;
	int		i;

	wishs = malloc(sizeof(t_wish) * philo_num);
	if (wishs == NULL)
	{
		exit(1);
		return (NULL);
	}
	i = 0;
	while (i < philo_num)
	{
		if (init_shared_resourse(&wishs[i].mutex) == ERROR)
		{
			exit(1);
			return (NULL);
		}
		wishs[i].request = LET_OK;
		wishs[i].fork_id = 0;
		wishs[i].sec_milli = 0;
		i++;
	}
	return (wishs);
}

int	init_status(t_status *status, char **argv, int argc)
{
	status->time_to_starve = ft_strtol(argv[2], NULL, 10);
	status->time_to_eat = ft_strtol(argv[3], NULL, 10);
	status->time_to_sleep = ft_strtol(argv[4], NULL, 10);
	status->time_to_die = -1;
	if (status->time_to_starve > INT_MAX || \
		status->time_to_sleep > INT_MAX || \
		status->time_to_eat > INT_MAX)
		return (ERROR);
	if (argc == 6)
		status->must_eat_times = ft_strtol(argv[5], NULL, 10);
	else
		status->must_eat_times = -1;
	return (SUCCESS);
}

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (queue == NULL)
		return (NULL);
	if (init_shared_resourse(&queue->mutex) == ERROR)
		return (NULL);
	queue->list = NULL;
	queue->do_proceed = true;
	return (queue);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:03:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 09:20:19 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	init_share(t_share *share, t_status *status, char *philo_num_arg)
{
	int	i;

	share->philo_num = ft_strtol(philo_num_arg, NULL, 10);
	share->wishs = init_wishs(share->philo_num);
	share->forks = init_fork(share->philo_num);
	share->queue = init_queue();
	share->philos_time_to_dead = malloc(sizeof(time_t) * share->philo_num);
	share->philos_eat_times = malloc(sizeof(int) * share->philo_num);
	i = 0;
	while (i < share->philo_num)
	{
		share->philos_time_to_dead[i] = -1;
		share->philos_eat_times[i] = 0;
		i++;
	}
	if (status->must_eat_times < 0)
		share->must_eat_times_exists = false;
	else
		share->must_eat_times_exists = true;
	share->time_to_starve = status->time_to_starve;
	share->must_eat_times = status->must_eat_times;
	return (0);
}

t_fork	*init_fork(int philo_num)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * philo_num);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < philo_num)
	{
		if (init_shared_resourse(&forks[i].fork) == ERROR)
			return (NULL);
		forks[i].fork_id = i;
		i++;
	}
	return (forks);
}

t_wish	*init_wishs(int philo_num)
{
	t_wish	*wishs;
	int		i;

	wishs = malloc(sizeof(t_wish) * philo_num);
	if (wishs == NULL)
	{
		exit(1);
		return (NULL);
	}
	i = 0;
	while (i < philo_num)
	{
		if (init_shared_resourse(&wishs[i].mutex) == ERROR)
		{
			exit(1);
			return (NULL);
		}
		wishs[i].request = LET_OK;
		wishs[i].fork_id = 0;
		wishs[i].sec_milli = 0;
		i++;
	}
	return (wishs);
}

int	init_status(t_status *status, char **argv, int argc)
{
	status->time_to_starve = ft_strtol(argv[2], NULL, 10);
	status->time_to_eat = ft_strtol(argv[3], NULL, 10);
	status->time_to_sleep = ft_strtol(argv[4], NULL, 10);
	status->time_to_die = -1;
	if (status->time_to_starve > INT_MAX || \
		status->time_to_sleep > INT_MAX || \
		status->time_to_eat > INT_MAX)
		return (ERROR);
	if (argc == 6)
		status->must_eat_times = ft_strtol(argv[5], NULL, 10);
	else
		status->must_eat_times = -1;
	return (SUCCESS);
}

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (queue == NULL)
		return (NULL);
	if (init_shared_resourse(&queue->mutex) == ERROR)
		return (NULL);
	queue->list = NULL;
	return (queue);
}

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
// int	print_time(int id, long sec_milli, int act, int fork_id)
// {
// 	static char	*remain;
// 	static int	remain_count;
// 	char	*out_put;
// 	char	*tmp;

// 	out_put = make_msg(id, sec_milli, act);
// 	if (out_put == NULL)
// 		return (ERROR);
// 	if (write(1, out_put, ft_strlen(out_put)) == -1)
// 		return (ERROR);
// 	free (out_put);
// 	if (act == LET_DEAD)
// 		return (ERROR);
// 	return (SUCCESS);
// }


// void	print_time_printf(int id, long sec_milli, int act, int fork_id)
// {
// 	if (act == LET_TAKE_A_FORK)
// 		printf("%ld %d has taken a fork\n", sec_milli, id);
// 	else if (act == LET_EAT)
// 		printf("%ld %d is eating\n",  sec_milli, id);
// 	else if (act == LET_THINK)
// 		printf("%ld %d is thinking\n",  sec_milli, id);
// 	else if (act == LET_SLEEP)
// 		printf("%ld %d is sleeping\n",  sec_milli, id);
// 	else if (act == LET_DEAD)
// 		printf("%ld %d died\n", sec_milli, id);
// }

// int	print_time(int id, long sec_milli, int act, int fork_id)
// {
// 	static char	*remain;
// 	static int	remain_count;
// 	char	*out_put;
// 	char	*tmp;

// 	out_put = make_msg(id, sec_milli, act, fork_id);
// 	if (out_put == NULL)
// 		return (ERROR);
// 	if (remain_count == 0)
// 	{
// 		remain = out_put;
// 		remain_count++;
// 	}
// 	else if (remain_count < 10)
// 	{
// 		tmp = ft_strjoin(remain, out_put);
// 		if (tmp == NULL)
// 			return (ERROR);
// 		free (remain);
// 		remain = tmp;
// 		remain_count++;
// 	}
// 	if (remain_count == 10)
// 	{
// 		if (write(1, remain, ft_strlen(remain)) == -1)
// 			return (ERROR);
// 		remain_count = 0;
// 	}

// 	if (write(1, out_put, ft_strlen(out_put)) == -1)
// 		return (ERROR);
// 	free (out_put);
// 	if (act == LET_DEAD)
// 		return (ERROR);
// 	return (SUCCESS);
// }

