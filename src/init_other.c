/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:50:14 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 17:01:11 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	init_shered_resourse(t_shered_resourse	*resourse)
{
	if (pthread_mutex_init(&resourse->stuff, NULL) == -1)
		return (ERROR);
	if (pthread_mutex_init(&resourse->is_available_mutex, NULL) == -1)
		return (ERROR);
	resourse->is_available = true;
	return (SUCCESS);
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
		if (init_shered_resourse(&forks[i].fork) == ERROR)
			return (NULL);
		forks[i].fork_id = i;
		i++;
	}
	return (forks);
}

t_dead	*init_t_dead(int philo_num)
{
	t_dead	*dead_check;
	int	i;

	i = 0;
	dead_check = malloc(sizeof(t_dead) * philo_num);
	if (dead_check == NULL)
		return (NULL);
	while (i < philo_num)
	{
		if (init_shered_resourse(&dead_check[i].mutex) == ERROR)
			return (NULL);
		dead_check[i].is_death = false;
		i++;
	}
	return (dead_check);
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
		if (init_shered_resourse(&wishs[i].mutex) == ERROR)
		{
			exit(1);
			return (NULL);
		}
		wishs[i].let_me_eat = THANK_YOU;
		i++;
	}
	return (wishs);
}

pthread_t	*init_th_id(int philo_num)
{
	pthread_t *th;

	th =  malloc(sizeof(pthread_t) * philo_num);
	if (th == NULL)
		return (NULL);
	return (th);
}
