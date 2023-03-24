/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_death.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:27:05 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/25 01:19:40 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

// int answer_dead_to_all_request(t_share *share)
int answer_dead_to_all_request(t_share *share)
{
	int	i;

	i = 0;
	while (i < share->philo_num)
	{
		if (ft_pthread_mutex_lock(&share->wishs[i].mutex))
			return (ERROR);
		share->wishs[i].request_info.request = LET_DEAD;
		// share->wishs[i].request = LET_DEAD;
		if (ft_pthread_mutex_unlock(&share->wishs[i].mutex))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

bool	did_the_old_man_go_heaven(t_share *share, int id)
{
	struct timeval	t1;
	long			sec_milli;

	sec_milli = ft_get_time_in_millisec();
	if (sec_milli == -1)
		return (true);
	if (share->philos_time_to_dead[id] < sec_milli && \
		share->philos_time_to_dead[id] != -1)
	{
		return (true);
	}
	return (false);
}
