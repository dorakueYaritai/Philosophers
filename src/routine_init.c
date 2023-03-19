/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 18:41:15 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	birth_philo_baby(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	// update_time_to_die(philo, sec_milli + philo->status.time_to_starve);
	update_time_to_die(philo, sec_milli + philo->time_to_starve);
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	birth_philo_baby(philo);
	philo_think(philo);
	return (NULL);
}
