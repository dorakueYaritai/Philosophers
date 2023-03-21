/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:36:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 05:41:55 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	put_fork(t_philo *philo, t_fork *fork);
static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had);

int	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;
	int		ans;

	first = philo->forks[FIRST];
	second = philo->forks[SECOND];
	update_wish_status(philo->wish, LET_TRY_TO_TAKE_FORKS, NONE, NONE, philo->philo_id);
	// 手付けていいですか と じっさいfork とる時二回リクエスト
	// 前者はアルゴリズム的回答を求めてて、後者はdead のチェック(eat とかと一緒)
	while (1)
	{
		ans = is_wish_come(philo->wish, philo->philo_id);
		if (ans == LET_OK)
			break;
		else if (ans == LET_YOU_ARE_ALREADY_DEAD)
			return (ERROR);
	}
	if (take_fork(philo, first, NULL) == ERROR)
		return (ERROR);
	if (take_fork(philo, second, first) == ERROR)
	{
		if (put_fork(philo, first) == ERROR)
			return (ERROR);
		return (ERROR);
	}
	return (0);
}

// bus error が出た。なんでだろ
static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
{
	while (ft_pthread_mutex_trylock(&fork->fork) == ERROR)
	{
		// if (had != NULL)
		// {
		// 	put_fork(philo, had);
		// 	return (take_forks(philo));
		// }
	}
	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
	{
		put_fork(philo, fork);
		return (ERROR);
	}
	return (SUCCESS);
}

// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	ft_pthread_mutex_lock(&fork->fork);
// 	if (exe_act(philo, LET_TAKE_A_FORK) == ERROR)
// 	{
// 		put_fork(philo, fork);
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }

// 上と同義だと思うけど、ちょっと怖いから残してる
// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	struct timeval t1;
// 	long sec_milli;
// 	int				ret;
// 	int				answer;

// 	// while (ft_pthread_mutex_trylock(&fork->fork) == ERROR)
// 	// {
// 	// 	;
// 	// }
// 	ft_pthread_mutex_lock(&fork->fork);
// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	update_wish_status(philo->wish, LET_TAKE_A_FORK, sec_milli, fork->fork_id, philo->philo_id);
// 	while (1)
// 	{
// 		answer = is_wish_come(philo->wish, philo->philo_id);
// 		if (answer == LET_YOU_ARE_ALREADY_DEAD)
// 		{
// 			put_fork(philo, fork);
// 			return (ERROR);
// 		}
// 		if (answer == LET_OK)
// 			return (SUCCESS);
// 	}
// }


// static int	take_fork(t_philo *philo, t_fork *fork, t_fork *had)
// {
// 	struct timeval t1;
// 	long sec_milli;
// 	int				ret;

// 	while (1)
// 	{
// 		if (ft_pthread_mutex_trylock(&fork->fork) == SUCCESS)
// 			break;
// 		if (had)
// 		{
// 			if (put_fork(philo, had) == ERROR)
// 				return (ERROR);
// 			// usleep(100);
// 			return (take_forks(philo));
// 		}
// 	}
// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	update_wish_status(philo->wish, LET_TAKE_A_FORK, sec_milli, NONE);
// 	int	answer;
// 	while (1)
// 	{
// 		answer = is_wish_come(philo->wish);
// 		if (answer == LET_OK)
// 			break;
// 		else if (answer == LET_YOU_ARE_ALREADY_DEAD)
// 			return (ERROR);
// 		// ulseep(10);
// 	}
// 	ret = print_time(philo->philo_id, sec_milli, LET_TAKE_A_FORK, fork->fork_id);
// 	return (ret);
// }

int	put_forks(t_philo *philo)
{
	// t_fork	*first;
	// t_fork	*second;

	// first = philo->forks[FIRST];
	// second = philo->forks[SECOND];
	// if (put_fork(philo, first) == ERROR)
	// 	return (ERROR);
	// if (put_fork(philo, second) == ERROR)
	// 	return (ERROR);
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
