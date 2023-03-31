/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:15:39 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/31 12:52:04 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <libft.h>

// situation 1: there are some philosophers

// who do something like eating, sleeping, thinking.

// situation 2: they srround the table , and on the table there is one fork
// between each philosopher 
// so a philosopher can take only two forks next to him.

// situation 3: to start eating, the philosopher needs to take two forks.

// situation 4: if a philosopher can't take two forks, he will wait until 
// he can take them. but if he can't take them for a long time, he will die.

// situation 5: you have to avoid philosophers to die.

// situation 6: each philosopher must not communicate with each other.
// like knowing who is about to die.

// so you have to control the order of taking forks using monitor.

// situation 7: if all philosophers want to take a fork, they 
// have to ask monitor. monitor have to answer to them by algorithm.

int		lock_for_two_people(t_share *share, int own_id, int opposite_id);
int		unlock_for_two_people(t_share *share, int own_id, int opposite_id);
int		lock_mini_first(t_share *share, int first_id, int id_1, int id_2);
int		unlock_mini_first(t_share *share, int first_id, int id_1, int id_2);
int		lock_data_avoiding_race(t_share *share, int own_id, int num);
int		unlock_data_avoiding_race(t_share *share, int own_id, int num);
bool	whethre_allow_taking_the_fork(t_share *share, int own_id, int num);
void	ultra_debug2(t_share *share, int id, int left_id, int right_id);

int	lock_data_avoiding_race(t_share *share, int own_id, int num)
{
	int	left_id;
	int	right_id;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (share->philo_num == 1)
	{
		printf("1A! : %d: %d\n", share->philo_id, own_id);
		return (ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex));
	}
	else if (share->philo_num == 2)
	{
		printf("2B! : %d: %d\n", share->philo_id, own_id);
		return (lock_for_two_people(share, own_id, left_id));
	}

	// if (ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex))
	// {
	// 	printf("NO\n");
	// 	return (ERROR);
	// }
	// printf("1! : %d: %d\n", share->philo_id, left_id);
	// if (ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex))
	// {
	// 	printf("NO\n");
	// 	return (ERROR);
	// }
	// printf("2! : %d: %d\n", share->philo_id, own_id);
	// if (ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex))
	// {
	// 	printf("NO\n");
	// 	return (ERROR);
	// }
	// printf("3! : %d: %d\n", share->philo_id, right_id);
	// lock_mini_first(share, left_id, own_id, right_id);

	if (own_id < left_id && own_id < right_id)
	{
		// printf("1! : %d: %d\n", share->philo_id, left_id);
		return (lock_mini_first(share, own_id, left_id, right_id));
		// printf("DONE\n");
	}
	else if (left_id < own_id && left_id < right_id)
	{
		// printf("2! : %d: %d\n", share->philo_id, left_id);
		return (lock_mini_first(share, left_id, own_id, right_id));
		// printf("DONE\n");
	}
	else
	{
		// printf("3! : %d: %d\n", share->philo_id, right_id);
		return (lock_mini_first(share, right_id, left_id, own_id));
		// printf("DONE\n");
	}
	return (SUCCESS);
}

int	unlock_data_avoiding_race(t_share *share, int own_id, int num)
{
	int	left_id;
	int	right_id;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (share->philo_num == 1)
		return (ft_pthread_mutex_unlock \
			(&share->time_to_die_array[own_id].mutex));
	else if (share->philo_num == 2)
		return (unlock_for_two_people(share, own_id, left_id));
	// unlock_mini_first(share, left_id, own_id, right_id);

	// if (ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex))
	// {
		// printf("FOO!\n");
	// 	return (ERROR);
	// }
	printf("a! : %d: %d\n", share->philo_id, left_id);
	// if (ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex))
	// {
		// printf("FOO!\n");
	// 	return (ERROR);
	// }
	printf("b! : %d: %d\n", share->philo_id, own_id);
	// if (ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex))
	// {
		// printf("FOO!\n");
	// 	return (ERROR);
	// }
	printf("c! : %d: %d\n", share->philo_id, right_id);

	if (own_id < left_id && own_id < right_id)
	{
		// printf("A! : %d: %d\n", share->philo_id, left_id);
		return (unlock_mini_first(share, own_id, left_id, right_id));
		// printf("DONE\n");
	}
	else if (left_id < own_id && left_id < right_id)
	{
		// printf("B! : %d: %d\n", share->philo_id, left_id);
		return (unlock_mini_first(share, left_id, own_id, right_id));
		// printf("DONE\n");
	}
	else
	{
		// printf("C! : %d: %d\n", share->philo_id, right_id);
		return (unlock_mini_first(share, right_id, left_id, own_id));
		// printf("DONE\n");
	}

	// if (own_id < left_id && own_id < right_id)
	// 	return (unlock_mini_first(share, own_id, left_id, right_id));
	// else if (left_id < own_id && left_id < right_id)
	// 	return (unlock_mini_first(share, left_id, own_id, right_id));
	// else
	// 	return (unlock_mini_first(share, right_id, own_id, left_id));
	return (SUCCESS);
}
