/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_fork2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:16:07 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/31 13:28:28 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	lock_for_two_people(t_share *share, int own_id, int opposite_id)
{
	if (own_id < opposite_id)
	{
		ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex);
		ft_pthread_mutex_lock(&share->time_to_die_array[opposite_id].mutex);
	}
	else if (own_id > opposite_id)
	{
		ft_pthread_mutex_lock(&share->time_to_die_array[opposite_id].mutex);
		ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int	unlock_for_two_people(t_share *share, int own_id, int opposite_id)
{
	if (own_id < opposite_id)
	{
		ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		ft_pthread_mutex_unlock(&share->time_to_die_array[opposite_id].mutex);
	}
	else if (own_id > opposite_id)
	{
		ft_pthread_mutex_unlock(&share->time_to_die_array[opposite_id].mutex);
		ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int	lock_mini_first(t_share *share, int first_id, int id_1, int id_2)
{
	if (ft_pthread_mutex_lock(&share->time_to_die_array[first_id].mutex))
		return (ERROR);
	if (id_1 < id_2)
	{
		if (ft_pthread_mutex_lock(&share->time_to_die_array[id_1].mutex))
			return (ERROR);
		if (ft_pthread_mutex_lock(&share->time_to_die_array[id_2].mutex))
			return (ERROR);
	}
	else
	{
		if (ft_pthread_mutex_lock(&share->time_to_die_array[id_2].mutex))
			return (ERROR);
		if (ft_pthread_mutex_lock(&share->time_to_die_array[id_1].mutex))
			return (ERROR);
	}
	return (SUCCESS);
}

int	unlock_mini_first(t_share *share, int first_id, int id_1, int id_2)
{
	if (ft_pthread_mutex_unlock(&share->time_to_die_array[first_id].mutex))
		return (ERROR);
	if (id_1 < id_2)
	{
		if (ft_pthread_mutex_unlock(&share->time_to_die_array[id_1].mutex))
			return (ERROR);
		if (ft_pthread_mutex_unlock(&share->time_to_die_array[id_2].mutex))
			return (ERROR);
	}
	else
	{
		if (ft_pthread_mutex_unlock(&share->time_to_die_array[id_2].mutex))
			return (ERROR);
		if (ft_pthread_mutex_unlock(&share->time_to_die_array[id_1].mutex))
			return (ERROR);
	}
	return (SUCCESS);
}
