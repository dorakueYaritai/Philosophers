/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 09:38:51 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

bool	check_am_i_dead(t_philo *philo)
{
	bool	data;

	ft_pthread_mutex_lock(&philo->dead_info->mutex);
	data = philo->dead_info->is_death;
	ft_pthread_mutex_unlock(&philo->dead_info->mutex);
	return (data);
}

int	print_time(int id, long sec_milli, int act, int fork_id)
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
		// join = ft_strjoin(join, " has taken	a fork ");
		// join = ft_strjoin(join, ft_ltoa(fork_id));
		// join = ft_strjoin(join, "\n");
		join = ft_strjoin(join, " has taken a fork\n");
	}
	else if (act == EAT)
		join = ft_strjoin(join, " is eating\n");
	else if (act == THINK)
		join = ft_strjoin(join, " is thinking\n");
	else if (act == SLEEP)
		join = ft_strjoin(join, " is sleeping\n");
	else if (act == DEAD)
	{
		join = ft_strjoin(join, " died\n");
		if (write(1, join, strlen(join)) == -1)
			return (ERROR);
		return (SUCCESS);
	}
	else if (act == PUTOFF)
	{
		join = "";
		// join = ft_strjoin(join, " has putoff a	fork ");
		// join = ft_strjoin(join, ft_ltoa(fork_id));
		// join = ft_strjoin(join, "\n");
	}
	if (write(1, join, strlen(join)) == -1)
		return (ERROR);
	return (SUCCESS);
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
