/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:29:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 19:28:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

bool	is_must_eat_times_fulfilled(t_share *share)
{
	int	i;

	i = 0;
	if (share->must_eat_times_exists == false)
		return (false);
	while (i < share->philo_num)
	{
		if (share->philos_eat_times[i] < share->must_eat_times)
			return (false);
		i++;
	}
	return (true);
}
