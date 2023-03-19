/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wish.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:33:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 16:33:22 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	update_wish_status(t_wish *wish)
{
	ft_pthread_mutex_lock(&wish->mutex);
	wish->let_me_eat = PLEASE;
	ft_pthread_mutex_unlock(&wish->mutex);
}

bool	is_wish_come(t_wish *wish)
{
	bool	ret;

	if (ft_pthread_mutex_lock(&wish->mutex))
		return (false);
	if (wish->let_me_eat == OK)
		ret = true;
	else
		ret = false;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (false);
	return (ret);
}

int	thanks_a_host(t_wish *wish)
{
	if (ft_pthread_mutex_lock(&wish->mutex))
		return (ERROR);
	wish->let_me_eat = THANK_YOU;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (ERROR);
	return (SUCCESS);
}
