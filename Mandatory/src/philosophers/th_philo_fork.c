/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 01:17:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	put_fork(t_philo *philo, t_fork *fork);
static int	take_fork(t_philo *philo, t_fork *fork);

int	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;
	int		ans;
	t_wish_info info;

	first = philo->forks[FIRST];
	second = philo->forks[SECOND];
	init_wish_info(&info, NONE, NONE, LET_TRY_TO_TAKE_FORKS);
	if (update_wish_status(philo->wish, &info) == ERROR)
		return (ERROR);
	// update_wish_status(philo->wish, LET_TRY_TO_TAKE_FORKS, NONE, NONE, philo->philo_id);
	// 手付けていいですか と じっさいfork とる時 別々リクエスト
	// 前者はアルゴリズム的回答を求めてて、後者はdead のチェック(eat とかと一緒)
	while (1)
	{
		ans = get_monitor_answer(philo->wish);
		// ans = get_monitor_answer(philo->wish, philo->philo_id, LET_TRY_TO_TAKE_FORKS);
		// write(1, ft_strjoin(ft_itoa(ans), "\n"), 2);
		if (ans == LET_OK)
			break;
		else if (ans == LET_DEAD)
			return (ERROR);
	}
	if (take_fork(philo, first) == ERROR)
		return (ERROR);
	if (take_fork(philo, second) == ERROR)
	{
		if (put_fork(philo, first) == ERROR)
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

// bus error が出た。なんでだろ
// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	if (ft_pthread_mutex_lock(&fork->fork) == ERROR)
// 		return (ERROR);
// 	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
// 	{
// 		put_fork(philo, fork);
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }

// // bus error が出た。なんでだろ
// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	while (ft_pthread_mutex_trylock(&fork->fork) == ERROR)
// 	{
// 		// if (had != NULL)
// 		// {
// 		// 	put_fork(philo, had);
// 		// 	return (take_forks(philo));
// 		// }
// 	}
// 	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
// 	{
// 		put_fork(philo, fork);
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }

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
	return (ft_pthread_mutex_unlock(&fork->fork));
}