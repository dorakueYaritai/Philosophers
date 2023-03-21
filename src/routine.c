/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:38 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 08:00:09 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	philo_think(t_philo *philo);
static int	philo_sleep(t_philo *philo);
static int	philo_eat(t_philo *philo);


int	exe_act(t_philo *philo, int act)
{
	struct timeval	t1;
	long			sec_milli;
	int				answer;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_wish_status(philo->wish, act, sec_milli, NONE, philo->philo_id);
	if (act == LET_EAT)
	{
		usleep((unsigned int)(philo->status.time_to_eat) * 1000);
	}
	else if (act == LET_SLEEP)
	{
		usleep((unsigned int)(philo->status.time_to_sleep) * 1000);
	}
	while (1)
	{
		answer = is_wish_come(philo->wish, philo->philo_id);
		if (answer == LET_OK)
			break;
		else if (answer == LET_YOU_ARE_ALREADY_DEAD)
		{
			return (ERROR);
		}
		// usleep(10);
	}
	return (SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	if (exe_act(philo, LET_EAT) == ERROR)
	{
		put_forks(philo);
		return (ERROR);
	}
	if (put_forks(philo) == ERROR)
		return (ERROR);
	return (philo_sleep(philo));
}

static int	philo_sleep(t_philo *philo)
{
	if (exe_act(philo, LET_SLEEP) == ERROR)
		return (ERROR);
	return (philo_think(philo));
}

int	philo_think(t_philo *philo)
{
	if (exe_act(philo, LET_THINK) == ERROR)
		return (ERROR);
	if (take_forks(philo) == ERROR)
	{
		return (ERROR);
	}
	return (philo_eat(philo));
}

