/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 20:19:41 by kakiba           ###   ########.fr       */
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
			ft_pthread_mutex_lock(&shere->dead_info[i].mutex);
			ft_pthread_mutex_lock(&shere->wishs[i].mutex);
		}
		shere->dead_info[i].is_death = true;
		shere->wishs[i].let_me_eat = LET_YOU_ARE_ALREADY_DEAD;
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		ft_pthread_mutex_unlock(&shere->dead_info[i].mutex);
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

// bool	guys_forks_avilable(t_fork *forks, int id, int num)
// {
// 	bool	b1;
// 	bool	b2;
// 	bool	ret;

// 	ret = false;
// 	b1 = false;
// 	b2 = false;
// 	if (ft_pthread_mutex_trylock(&forks[id].fork) == SUCCESS)
// 	{
// 		b1 = true;
// 		ft_pthread_mutex_unlock(&forks[id].fork);
// 	}
// 	if (ft_pthread_mutex_trylock(&forks[(id + 1) % num].fork) == SUCCESS)
// 	{
// 		b2 = true;
// 		ft_pthread_mutex_unlock(&forks[(id + 1) % num].fork);
// 	}
// 	// write(1, "tryed!\n", 7);
// 	if (b1 && b2)
// 	{
// 		write(1, "omedetou!\n", 10);
// 		ret = true;
// 	}
// 	return (ret);
// }

bool	guys_forks_avilable(t_shere *shere, int id, int num)
{
	bool	b1;
	bool	b2;
	bool	ret;

	ret = false;
	b1 = false;
	b2 = false;
	if (ft_pthread_mutex_trylock(&shere->forks[id % num].fork) == SUCCESS)
	{
		b1 = true;
		ft_pthread_mutex_unlock(&shere->forks[id % num].fork);
	}
	if (ft_pthread_mutex_trylock(&shere->forks[(id + 1) % num].fork) == SUCCESS)
	{
		b2 = true;
		ft_pthread_mutex_unlock(&shere->forks[(id + 1) % num].fork);
	}
	if (b1 && b2)
	{
		// write(1, "omedetou!\n", 10);
		return (true);
		// ret = true;
	}
	return (ret);
}


// bool	guys_forks_avilable(t_shere *shere, int id, int num)
// {
// 	bool	b1;
// 	bool	b2;
// 	bool	ret;

// 	ret = false;
// 	write(1, ft_ltoa(id), 2);
// 	write(1, "try!\n", 5);
// 	b1 = ft_pthread_mutex_trylock(&forks[id].fork);
// 	write(1, "tryed!\n", 7);
// 	if (b1)
// 		ft_pthread_mutex_unlock(&forks[id].fork);
// 	write(1, "try!\n", 5);
// 	b2 = ft_pthread_mutex_trylock(&forks[(id + 1) % num].fork);
// 	write(1, "tryed!\n", 7);
// 	if (b2)
// 		ft_pthread_mutex_unlock(&forks[(id + 1) % num].fork);
// 	if (b1 && b2)
// 		ret = true;
// 	return (ret);
// }

void	ultra_debug(int id, int left_id, int right_id, t_dead *dead_info)
{
   char    *str;

    str = ft_strjoin("", "A");
    str = ft_strjoin(str, ft_ltoa(id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ft_ltoa(*dead_info[id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(left_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ft_ltoa(*dead_info[left_id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(right_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ft_ltoa(*dead_info[right_id].time_to_die));
    str = ft_strjoin(str, ": \n");
	write(1, str, strlen(str));
}

// bool	is_ok_the_guy_eat(t_dead *dead_info, int id, int num)
int	is_ok_the_guy_eat(t_shere *shere,int id, int num)
{
	int left_id;
	int right_id;
	int	ret;
	time_t	array[3];

	// return (true);
	// if (guys_forks_avilable(shere->forks, id, num) == true)
	// 	return (true);
	// if (guys_forks_avilable(shere, id, num) == true)
	// 	return (true);
	left_id = ft_positive_mod(id - 1, num);
	right_id = ft_positive_mod(id + 1, num);
	ft_pthread_mutex_lock(&shere->dead_info[id].mutex);
	array[0] = *shere->dead_info[id].time_to_die;
	ft_pthread_mutex_unlock(&shere->dead_info[id].mutex);

	ft_pthread_mutex_lock(&shere->dead_info[left_id].mutex);
	array[1] = *shere->dead_info[left_id].time_to_die;
	ft_pthread_mutex_unlock(&shere->dead_info[left_id].mutex);

	ft_pthread_mutex_lock(&shere->dead_info[right_id].mutex);
	array[2] = *shere->dead_info[right_id].time_to_die;
	ft_pthread_mutex_unlock(&shere->dead_info[right_id].mutex);

	// 死にそうランキング1位タイだったらOK
	// ultra_debug(id, left_id, right_id, shere->dead_info);

	if (array[0] <= array[1] && array[0] <= array[2])
		return (LET_OK);
	else if (array[1] == -1 || array[2] == -1)
		return (LET_OK);
	else
		return (LET_TRY_TO_TAKE_FORKS);
}

int	feed_time_check(t_shere *shere, int id)
{
	t_wish	*wish;

	wish = &shere->wishs[id];
	ft_pthread_mutex_lock(&wish->mutex);
	if (wish->let_me_eat == LET_TRY_TO_TAKE_FORKS)
	{
		if (is_ok_the_guy_eat(shere, id, shere->philo_num) == true)
			wish->let_me_eat = LET_OK;
	}
	ft_pthread_mutex_unlock(&wish->mutex);
	return (SUCCESS);
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

		// feed_time_check(shere, id);
		if (listen_to_old_guys_request(shere, id) == LET_DEAD)
		{
			return (1);
		}

		// if (i == num - 1)
		// 	usleep(5000);
		// i++;
		// if (i == num)
		// 	usleep(100);
		// i = (i + 1) % num;
		++id;
		if (id == num)
		{
			// usleep(100);
			id = 0;
		}
	}
	return (0);
}
