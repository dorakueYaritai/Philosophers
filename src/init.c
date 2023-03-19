/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:05:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 13:14:14 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// void	print_philo_status(t_philo *philo)
// {
// 	printf("starve: %ld\n", philo->time_to_starve);
// 	printf("eat: %ld\n", philo->time_to_eat);
// 	printf("sleep: %ld\n", philo->time_to_sleep);
// 	printf("die: %ld\n", philo->time_to_die);
// 	printf("id: %d\n", philo->philo_id);
// }

pthread_t	*init_th_id(char *argv[])
{
	pthread_t *th;

	th =  malloc(sizeof(pthread_t) * strtol(argv[1], NULL, 10));
	if (th == NULL)
	{
		exit(1);
	}
	return (th);
}

t_philo	*init_philo(char *argv[], t_fork *m_forks, t_dead *dead_array)
{
	size_t	i;
	size_t	philo_num = strtol(argv[1], NULL, 10);
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * philo_num);
	i = 0;
	if (m_forks == NULL || dead_array == NULL)
		return (NULL);
	while (i < philo_num)
	{
		philo[i].time_to_starve = strtol(argv[2], NULL, 10);
		philo[i].time_to_eat = strtol(argv[3], NULL, 10);
		philo[i].time_to_sleep = strtol(argv[4], NULL, 10);
		philo[i].time_to_die = -1;
		philo[i].philo_id = i;
		philo[i].dead_info = &dead_array[i];
		// philo[i].dead_info2 = dead_array[i];
		dead_array[i].time_to_die = &philo[i].time_to_die;
		// philo[i].dead_info.is_death = false;
		philo[i].dead_info->is_death = false;
		if (i % 2 == 0)
		{
			philo[i].forks[FIRST] = &m_forks[i];
			philo[i].forks[SECOND] = &m_forks[(i + 1) % philo_num];
			// philo[i].forks[FIRST]->time_to_die[i % 2] = 
		}
		else
		{
			philo[i].forks[FIRST] = &m_forks[(i + 1) % philo_num];
			philo[i].forks[SECOND] = &m_forks[i];
		}
		i++;
	}
	return (philo);
}

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
		forks[i].request_status[0] = FULL;
		forks[i].request_status[1] = FULL;
		forks[i].life_expectancy[0] = __LONG_MAX__;
		forks[i].life_expectancy[1] = __LONG_MAX__;
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
