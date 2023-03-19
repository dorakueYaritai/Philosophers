/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 15:03:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// int	print_sub(int id, long sec_milli, long sec_milli_philo)
// {
// 	char	*id_str;
// 	char	*join;

// 	id_str = ft_itoa(id);
// 	join = ft_strjoin(id_str, "/now:");
// 	join = ft_strjoin(join, ft_ltoa(sec_milli));
// 	join = ft_strjoin(join, " vs philo:");
// 	join = ft_strjoin(join, ft_ltoa(sec_milli_philo));
// 	join = ft_strjoin(join, "\n");
// 	write(1, join, ft_strlen(join));
// }

int kill_everyone(t_dead *dead_info, int philo_num, int dead_id)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (i != dead_id)
			ft_pthread_mutex_lock(&dead_info[i].mutex);
		dead_info[i].is_death = true;
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		ft_pthread_mutex_unlock(&dead_info[i].mutex);
		i++;
	}
}

int	philo_is_die(t_shere *shere, int i, int num)
{
	struct timeval t1;
	long sec_milli;

	ft_pthread_mutex_lock(&shere->dead_info[i].mutex);
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (*shere->dead_info[i].time_to_die < sec_milli && *shere->dead_info[i].time_to_die != -1)
	{
		kill_everyone(shere->dead_info, num, i);
		print_time(i, sec_milli, DEAD, NONE);
		return (1);
	}
	ft_pthread_mutex_unlock(&shere->dead_info[i].mutex);
}

bool	is_ok_the_guy_eat(t_dead *dead_info, int id, int philo_num)
{
	int left_id;
	int right_id;
	bool	ret;

	if (fork == NULL)
		return (false);
	left_id = (id - 1) % philo_num; //
	right_id = (id + 1) % philo_num;
	// pthread_mutex_lock(&fork->check_request_status);
	ft_pthread_mutex_lock(&dead_info[id].mutex);
	ft_pthread_mutex_lock(&dead_info[left_id].mutex);
	ft_pthread_mutex_lock(&dead_info[right_id].mutex);
	// 死にそうランキング1位タイだったらOK
	if (dead_info[id].time_to_die >= dead_info[left_id].time_to_die && \
		dead_info[id].time_to_die >= dead_info[right_id].time_to_die)
		ret = true;
	else
		ret = false;
	ft_pthread_mutex_unlock(&dead_info[id].mutex);
	ft_pthread_mutex_unlock(&dead_info[left_id].mutex);
	ft_pthread_mutex_unlock(&dead_info[right_id].mutex);
	return (ret);
}

int	feed_time_check(t_shere *shere, int id)
{
	t_wish	*wish;

	wish = &shere->wishs[id];
	ft_pthread_mutex_lock(&wish->mutex);
	if (wish->let_me_eat == PLEASE)
	{
		if (is_ok_the_guy_eat(shere->dead_info, id, shere->philo_num))
			wish->let_me_eat = OK;
	}
	ft_pthread_mutex_unlock(&wish->mutex);
	return (SUCCESS);
}

// PTHREAD_MUTEX_INITIALIZER()
int monitor_philos_death(t_shere *shere)
{
	int	i;
	int	num;

	num = shere->philo_num;
	i = 0;
	while (i < num)
	{
		if (philo_is_die(shere, i, num) == true)
			return (1);
		feed_time_check(shere, i);
		if (i == num - 1)
			usleep(5000);
		i = (i + 1) % num;
		// i++;
	}
	return (0);
	// while (1)
	// {
	// 	i = 0;
	// 	while (i < num)
	// 	{
	// 		if (philo_is_die(shere, i, num) == true)
	// 			return (1);
	// 		// feed_time_check(shere, i);
	// 		i++;
	// 	}
	// 	usleep(5000);
	// }
	// return (0);
}
