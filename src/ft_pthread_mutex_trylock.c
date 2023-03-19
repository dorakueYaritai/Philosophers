/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_mutex_trylock.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:27:09 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 09:49:37 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	ret_unlock(pthread_mutex_t	*mutex, int status)
{
	pthread_mutex_unlock(mutex);
	return (status);
}

int	ft_pthread_mutex_trylock(t_shered_resourse sourse)
{
	if (pthread_mutex_lock(&sourse.is_available_mutex))
		return (ERROR);
	if (s->is_available == false)
	{
		// ret_unlock(&sourse.is_available_mutex, ERROR);
		pthread_mutex_unlock(&sourse.is_available_mutex);
		return (ERROR);
	}
	else
	{
		if (pthread_mutex_lock(&sourse.stuff))
		{
			// ret_unlock(&sourse.is_available_mutex, ERROR);
			pthread_mutex_unlock(&sourse.is_available_mutex);
			return (ERROR);
		}
		s->is_available = false;
		// ret_unlock(&sourse.is_available_mutex, SUCCESS);
		pthread_mutex_unlock(&sourse.is_available_mutex);
		return (SUCCESS);
	}
}

// int	ft_pthread_mutex_trylock(t_shered_resourse sourse)
// {
// 	if (pthread_mutex_lock(&sourse.is_available_mutex))
// 		return (ERROR);
// 	if (s->is_available == false)
// 	{
// 		pthread_mutex_unlock(&sourse.is_available_mutex);
// 		return (ERROR);
// 	}
// 	else
// 	{
// 		if (pthread_mutex_lock(&sourse.stuff))
// 		{
// 			pthread_mutex_unlock(&sourse.is_available_mutex);
// 			return (ERROR);
// 		}
// 		s->is_available = false;
// 		if (pthread_mutex_unlock(&sourse.is_available_mutex))
// 		{
// 			pthread_mutex_unlock(&sourse.is_available_mutex);
// 			s->is_available = true;
// 			return (ERROR);
// 		}
// 		return (SUCCESS);
// 	}
// }

bool	check_am_i_dead(t_philo *philo)
{
	bool	data;

	pthread_mutex_lock(&philo->dead_info->is_death_mutex);
	data = philo->dead_info->is_death;
	pthread_mutex_unlock(&philo->dead_info->is_death_mutex);
	return (data);
}
