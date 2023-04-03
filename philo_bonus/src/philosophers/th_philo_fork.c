/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/28 15:38:16 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	put_fork(t_philo *philo, t_fork *fork);
static int	take_fork(t_philo *philo, t_fork *fork);

// 手付けていいですか と じっさいfork とる時 別々リクエスト
// 前者はアルゴリズム的回答を求めてて、後者はdead のチェック(eat とかと一緒)

int	take_forks(t_philo *philo)
{
	int			ans;
	t_wish_info	info;

	init_wish_info(&info, NONE, NONE, LET_TRY_TO_TAKE_FORKS);
	if (update_wish_status(philo->wish, &info) == ERROR)
		return (ERROR);
	while (1)
	{
		ans = get_monitor_answer(philo->wish);
		if (ans == LET_OK)
			break ;
		else if (ans == LET_DEAD)
			return (ERROR);
	}
	if (take_fork(philo, philo->forks[FIRST]) == ERROR)
		return (ERROR);
	if (take_fork(philo, philo->forks[SECOND]) == ERROR)
	{
		if (put_fork(philo, philo->forks[FIRST]) == ERROR)
			return (ERROR);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	take_fork(t_philo *philo, t_fork *fork)
{
	if (ft_pthread_mutex_lock(&fork->fork) == ERROR)
		return (ERROR);
	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
	{
		put_fork(philo, fork);
		return (ERROR);
	}
	return (SUCCESS);
}

int	put_forks(t_philo *philo)
{
	if (put_fork(philo, philo->forks[FIRST]) == ERROR)
		return (ERROR);
	if (put_fork(philo, philo->forks[SECOND]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	put_fork(t_philo *philo, t_fork *fork)
{
	(void)philo;
	return (ft_pthread_mutex_unlock(&fork->fork));
}
