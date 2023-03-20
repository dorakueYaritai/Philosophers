/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_mutex_trylock.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:27:09 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 13:32:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	ft_pthread_mutex_lock(t_shered_resourse *sourse)
{
	int	ret;
	ret = pthread_mutex_lock(&sourse->stuff);
	if (ret == 0)
		sourse->is_available = false;
	return (ret);
}

int	ft_pthread_mutex_unlock(t_shered_resourse *sourse)
{
	int	ret;
	ret = pthread_mutex_unlock(&sourse->stuff);
	if (ret == 0)
		sourse->is_available = true;
		return (ret);
}

static int	ret_unlock(pthread_mutex_t	*mutex, int status)
{
	pthread_mutex_unlock(mutex);
	return (status);
}

int	ft_pthread_mutex_trylock(t_shered_resourse *sourse)
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
