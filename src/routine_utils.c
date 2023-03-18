/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/18 13:23:12 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>


// bool	check_am_i_dead(t_philo *philo)
// {
// 	struct timeval t1;
// 	long sec_milli;

// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	if (philo->time_to_die < sec_milli && philo->time_to_die != -1)
// 	{
// 		return (true);
// 		// return (print_time(philo->philo_id, philo->time_to_die, DEAD, 0));
// 	}
// 	return (false);
// }

void	print_time_printf(int id, long sec_milli, int act, int fork_id)
{
	if (act == FORK)
		printf("%ld %d has taken a fork\n", sec_milli, id);
	else if (act == EAT)
		printf("%ld %d is eating\n",  sec_milli, id);
	else if (act == THINK)
		printf("%ld %d is thinking\n",  sec_milli, id);
	else if (act == SLEEP)
		printf("%ld %d is sleeping\n",  sec_milli, id);
	else if (act == DEAD)
		printf("%ld %d died\n", sec_milli, id);
}
