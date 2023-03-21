/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_mutex_trylock.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:27:09 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 08:37:41 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

// int	ft_pthread_mutex_lock(t_shared_resourse *sourse)
// {
// 	int	ret;

// 	ret = pthread_mutex_lock(&sourse->stuff);
// 	if (ret != 0)
// 		return (ERROR);
// 	ret = pthread_mutex_lock(&sourse->is_available_mutex);
// 	if (ret != 0)
// 	{
// 		pthread_mutex_unlock(&sourse->stuff);
// 		return (ERROR);
// 	}
// 	sourse->is_available = false;
// 	ret = pthread_mutex_unlock(&sourse->is_available_mutex);
// 	if (ret != 0)
// 		return (ERROR);
// 	return (SUCCESS);
// }

int	ft_pthread_mutex_lock(t_shared_resourse *sourse)
{
	int	ret = 0;
	while (ft_pthread_mutex_trylock(sourse) == ERROR)
		;
	// if (ret == 0)
	// 	sourse->is_available = false;
	return (ret);
}


int	ft_pthread_mutex_unlock(t_shared_resourse *sourse)
{
	int	ret;

	if (pthread_mutex_lock(&sourse->is_available_mutex))
		return (ERROR);
	sourse->is_available = true;
	if (pthread_mutex_unlock(&sourse->is_available_mutex))
		return (ERROR);
	ret = pthread_mutex_unlock(&sourse->stuff);
	return (ret);
}

static int	ret_unlock(pthread_mutex_t	*mutex, int status)
{
	pthread_mutex_unlock(mutex);
	return (status);
}

int	ft_pthread_mutex_trylock(t_shared_resourse *sourse)
{
	if (pthread_mutex_lock(&sourse->is_available_mutex))
		return (ERROR);
	if (sourse->is_available == false)
		return (ret_unlock(&sourse->is_available_mutex, ERROR));
	else
	{
		if (pthread_mutex_lock(&sourse->stuff))
			return (ret_unlock(&sourse->is_available_mutex, ERROR));
		sourse->is_available = false;
		return (ret_unlock(&sourse->is_available_mutex, SUCCESS));
	}
}


// int	ft_pthread_mutex_trylock(t_shared_resourse sourse)
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
