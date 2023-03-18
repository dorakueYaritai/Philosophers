/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/18 11:15:02 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_time(int id, long sec_milli, int act, int fork_id)
{
	char	*sec_milli_str;
	char	*id_str;
	char	*join;

	id_str = ft_itoa(id);
	sec_milli_str = ft_ltoa(sec_milli);
	join = ft_strjoin(sec_milli_str, " ");
	join = ft_strjoin(join, id_str);

	if (act == FORK)
	{
		join = ft_strjoin(join, " has taken a fork ");
		join = ft_strjoin(join, ft_itoa(fork_id));
		join = ft_strjoin(join, "\n");
		// join = ft_strjoin(join, " has taken a fork \n");
	}
	else if (act == EAT)
		join = ft_strjoin(join, " is eating\n");
	else if (act == THINK)
		join = ft_strjoin(join, " is thinking\n");
	else if (act == SLEEP)
		join = ft_strjoin(join, " is sleeping\n");
	else
	{
		join = ft_strjoin(join, " died\n");
		if (write(1, join, strlen(join)) == -1)
			exit (1);
		exit (1);
	}
	if (write(1, join, strlen(join)) == -1)
		exit(1);
}

int	check_am_i_dead(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die != -1 && philo->time_to_die <= sec_milli)
	{
		print_time(philo->philo_id, philo->time_to_die, DEAD, 0);
	}
	return (0);
}

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
