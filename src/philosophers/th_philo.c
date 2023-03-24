/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:38 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/25 01:23:24 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);
int	exe_act(t_philo *philo, int act);
void* routine_init(void *_philo);

void* routine_init(void *_philo){
	t_philo			*philo;
	long			sec_milli;
	int				ans;

	philo = (t_philo *)_philo;
	exe_act(philo, LET_INIT);
	return ((void *) philo_think(philo));
}

static int	philo_think(t_philo *philo)
{
	if (exe_act(philo, LET_THINK) == ERROR)
		return (ERROR);
	if (take_forks(philo) == ERROR)
	{
		return (ERROR);
	}
	return (philo_eat(philo));
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
		answer = get_monitor_answer(philo->wish, philo->philo_id, act);
		if (answer == LET_OK)
			break;
		else if (answer == LET_DEAD)
			return (ERROR);
	}
	return (SUCCESS);
}
