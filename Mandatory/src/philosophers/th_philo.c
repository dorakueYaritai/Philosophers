/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:38 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/31 12:13:54 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);
int			exe_act(t_philo *philo, int act);
void		*routine_init(void *_philo);

void	*routine_init(void *_philo)
{
	t_philo			*philo;

	philo = (t_philo *)_philo;
	if (philo->philo_id % 2 == 0)
		ft_msleep(philo->status.time_to_eat / 2);
	exe_act(philo, LET_INIT);
	printf("%d\n", philo->philo_id);
	return (NULL);
	philo_think(philo);
	return (NULL);
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
	t_wish_info		info;

	info.act_time = ft_get_time_in_millisec();
	if (info.act_time == -1)
		return (ERROR);
	info.request = act;
	info.fork_id = NONE;
	if (update_wish_status(philo->wish, &info) == ERROR)
		return (ERROR);
	if (act == LET_EAT)
		ft_msleep(philo->status.time_to_eat);
	else if (act == LET_SLEEP)
		ft_msleep(philo->status.time_to_sleep);
	while (1)
	{
		usleep(10);
		answer = get_monitor_answer(philo->wish);
		if (answer == LET_OK)
			break ;
		else if (answer == LET_DEAD)
			return (ERROR);
	}
	return (SUCCESS);
}
