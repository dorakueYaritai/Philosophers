/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:05:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 17:06:00 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	init_philo_sub(t_philo *philo,
	char *argv[], t_fork *m_forks, t_shere *shere)
{
	int	i;
	int	philo_num;

	philo_num = shere->philo_num;
	i = philo->philo_id;
	philo->time_to_starve = strtol(argv[2], NULL, 10);
	philo->time_to_eat = strtol(argv[3], NULL, 10);
	philo->time_to_sleep = strtol(argv[4], NULL, 10);
	philo->time_to_die = -1;
	philo->dead_info = &shere->dead_info[i];
	philo->wish = &shere->wishs[i];
	shere->dead_info[i].time_to_die = &philo->time_to_die;
	philo->dead_info->is_death = false;
	if (i % 2 == 0)
	{
		philo->forks[FIRST] = &m_forks[i];
		philo->forks[SECOND] = &m_forks[(i + 1) % philo_num];
	}
	else
	{
		philo->forks[FIRST] = &m_forks[(i + 1) % philo_num];
		philo->forks[SECOND] = &m_forks[i];
	}
}

t_philo	*init_philos(char *argv[], t_fork *m_forks, t_shere *shere)
{
	int	i;
	int	philo_num;

	t_philo	*philos;
	philo_num = shere->philo_num;
	philos = malloc(sizeof(t_philo) * philo_num);
	i = 0;
	if (shere == NULL || m_forks == NULL || shere->dead_info == NULL)
		return (NULL);
	while (i < philo_num)
	{
		philos[i].philo_id = i;
		init_philo_sub(&philos[i], argv, m_forks, shere);
		i++;
	}
	return (philos);
}
