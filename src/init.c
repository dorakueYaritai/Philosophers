/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:05:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/18 23:09:34 by kakiba           ###   ########.fr       */
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
	philo = malloc(sizeof(t_philo) * (philo_num + 1));
	i = 0;
	while (i < philo_num)
	{
		philo[i].time_to_starve = strtol(argv[2], NULL, 10);
		philo[i].time_to_eat = strtol(argv[3], NULL, 10);
		philo[i].time_to_sleep = strtol(argv[4], NULL, 10);
		philo[i].time_to_die = -1;
		philo[i].philo_id = i;
		philo[i].dead_info = &dead_array[i];
		dead_array[i].time_to_die = &philo[i].time_to_die;
		// philo[i].dead_info = dead_array[i];
		// philo[i].dead_info.is_death = false;
		philo[i].dead_info->is_death = false;
		if (i % 2 == 0)
		{
			philo[i].first = &m_forks[i];
			philo[i].second = &m_forks[(i + 1) % philo_num];
		}
		else
		{
			philo[i].second = &m_forks[i];
			philo[i].first = &m_forks[(i + 1) % philo_num];
		}
		i++;
	}
	return (philo);
}

t_fork	*init_fork(int philo_num)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork) * philo_num);
	if (fork == NULL)
		return (NULL);
	int	i = 0;
	while (i < philo_num)
	{
		if (pthread_mutex_init(&fork[i].fork , NULL) == -1)
		{
			printf("fork init failure!\n");
			exit(1);
		}
		if (pthread_mutex_init(&fork[i].fork_check , NULL) == -1)
		{
			printf("fork init failure!\n");
			exit(1);
		}
		fork[i].is_fork_available = true;
		fork[i].fork_id = i;
		i++;
	}
	return (fork);
}

t_dead	*init_t_dead(int philo_num)
{
	t_dead	*dead_check;
	char	*ptr;

	dead_check = malloc(sizeof(t_dead) * philo_num);
	if (dead_check == NULL)
		return (NULL);
	int	i = 0;
	while (i < philo_num)
	{
		ptr = (char *)&dead_check[i];
		if (pthread_mutex_init(&dead_check[i].is_death_mutex, NULL) == -1)
		{
			printf("fork deadcheck failure!\n");
			exit(1);
		}
		i++;
	}
	return (dead_check);
}
