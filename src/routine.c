/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:38 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 17:53:40 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	philo_think(t_philo *philo);
static int	philo_sleep(t_philo *philo);
static int	philo_eat(t_philo *philo);


int	exe_act(t_philo *philo, int act)
{
	int				answer;
	long			sec_milli;

	sec_milli = ft_get_time_in_millisec();
	if (sec_milli == -1)
		return (ERROR);
	update_wish_status(philo->wish, act, sec_milli, NONE, philo->philo_id);
	if (act == LET_EAT)
		usleep((unsigned int)(philo->status.time_to_eat) * 1000);
	else if (act == LET_SLEEP)
		usleep((unsigned int)(philo->status.time_to_sleep) * 1000);
	while (1)
	{
		answer = is_wish_come(philo->wish, philo->philo_id, act);
		if (answer == LET_OK)
			break;
		else if (answer == LET_DEAD)
			return (ERROR);
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

