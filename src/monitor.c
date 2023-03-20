/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:24:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 09:44:54 by kakiba           ###   ########.fr       */
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
	// write(1, "tryed!\n", 7);
	if (b1 && b2)
	{
		write(1, "omedetou!\n", 10);
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
bool	is_ok_the_guy_eat(t_shere *shere,int id, int num)
{
	int left_id;
	int right_id;
	bool	ret;
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
	ultra_debug(id, left_id, right_id, shere->dead_info);

	if (array[0] <= array[1] && array[0] <= array[2])
		ret = true;
	else if (array[1] == -1 || array[2] == -1)
		ret = true;
	else
		ret = false;
	return (ret);
}

// bool	is_ok_the_guy_eat(t_dead *dead_info, int id, int philo_num)
// {
// 	int left_id;
// 	int right_id;
// 	bool	ret;

// 	left_id = ft_positive_mod(id - 1, philo_num);
// 	right_id = ft_positive_mod(id + 1, philo_num);
// 	ft_pthread_mutex_lock(&dead_info[id].mutex);
// 	ft_pthread_mutex_lock(&dead_info[left_id].mutex);
// 	ft_pthread_mutex_lock(&dead_info[right_id].mutex);
// 	// 死にそうランキング1位タイだったらOK

// //    char    *str;

// //     str = ft_strjoin("", "A");
// //     str = ft_strjoin(str, ft_ltoa(id));
// //     str = ft_strjoin(str, "    ");
// //     str = ft_strjoin(str, ft_ltoa(*dead_info[id].time_to_die));
// //     str = ft_strjoin(str, ":    ");

// //     str = ft_strjoin(str, ft_ltoa(left_id));
// //     str = ft_strjoin(str, "    ");
// //     str = ft_strjoin(str, ft_ltoa(*dead_info[left_id].time_to_die));
// //     str = ft_strjoin(str, ":    ");

// //     str = ft_strjoin(str, ft_ltoa(right_id));
// //     str = ft_strjoin(str, "    ");
// //     str = ft_strjoin(str, ft_ltoa(*dead_info[right_id].time_to_die));
// //     str = ft_strjoin(str, ":    \n");
// // 	write(1, str, strlen(str));

// 	if (*dead_info[id].time_to_die <= *dead_info[left_id].time_to_die && \
// 		*dead_info[id].time_to_die <= *dead_info[right_id].time_to_die)
// 		ret = true;
// 	else
// 		ret = false;
// 	ft_pthread_mutex_unlock(&dead_info[id].mutex);
// 	ft_pthread_mutex_unlock(&dead_info[left_id].mutex);
// 	ft_pthread_mutex_unlock(&dead_info[right_id].mutex);
// 	return (ret);
// }

int	feed_time_check(t_shere *shere, int id)
{
	t_wish	*wish;

	wish = &shere->wishs[id];
	ft_pthread_mutex_lock(&wish->mutex);
	if (wish->let_me_eat == PLEASE)
	{
		if (is_ok_the_guy_eat(shere, id, shere->philo_num) == true)
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
	while (1)
	{
		if (philo_is_die(shere, i, num) == true)
			return (1);
		feed_time_check(shere, i);
		// if (i == num - 1)
		// 	usleep(5000);
		// i++;
		// if (i == num)
		// 	usleep(100);
		// i = (i + 1) % num;
		++i;
		if (i == num)
		{
			// usleep(100);
			i = 0;
		}
	}
	return (0);
}
