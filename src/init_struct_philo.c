/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:05:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 18:47:16 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

// static int	init_philo_sub(t_philo *philo,
// 	char *argv[], t_fork *m_forks, t_share *share)

// static int	init_philo_sub(t_philo *philo,
// 	t_status *status, t_fork *m_forks, t_share *share){

static int	init_philo_sub(t_philo *philo,
	t_status *status, t_share *share){
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

	philo->dead_info = &share->dead_info[i];
	philo->wish = &share->wishs[i];

	share->dead_info[i].time_to_die = &philo->status.time_to_die;
	share->dead_info[i].must_eat_times = &philo->status.must_eat_times;

	// philo->dead_info->is_death = false;
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

// t_philo	*init_philos(t_status *status, t_fork *m_forks, t_share *share)
t_philo	*init_philos(t_status *status, t_share *share)
{
	int	i;
	int	philo_num;

	t_philo	*philos;
	philo_num = share->philo_num;
	philos = malloc(sizeof(t_philo) * philo_num);
	i = 0;
	if (share == NULL || share->forks == NULL || share->dead_info == NULL)
		return (NULL);
	while (i < philo_num)
	{
		philos[i].philo_id = i;
		init_philo_sub(&philos[i], status, share);
		i++;
	}
	return (philos);
}
