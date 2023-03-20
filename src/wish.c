/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wish.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:33:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 14:34:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id, int id)
{

	ft_pthread_mutex_lock(&wish->mutex);
	if (wish->let_me_eat == LET_YOU_ARE_ALREADY_DEAD)
	{
		ft_pthread_mutex_unlock(&wish->mutex);
		return (ERROR);
	}
	wish->let_me_eat = request;
	wish->sec_milli = sec_milli;
	wish->fork_id = fork_id;

	char *join;
	join = ft_strjoin("::: ", ft_ltoa(id));
	join = ft_strjoin(join, " update ");
	join = ft_strjoin(join, ft_ltoa(request));
	join = ft_strjoin(join, "\n");
	write(1, join, ft_strlen(join));

	ft_pthread_mutex_unlock(&wish->mutex);
}

// bool	is_wish_come(t_wish *wish)
int	is_wish_come(t_wish *wish, int id)
{
	int	ret;
	char	*join;

	if (ft_pthread_mutex_trylock(&wish->mutex) == ERROR)
	{

		write(1, ":::reject saretayo!\n", 20);
		return (LET_REJECT);
	}

	ret = wish->let_me_eat;
	if (ret == LET_OK)
	{
		wish->let_me_eat = LET_THANK_YOU;
	}

	join = ft_strjoin("::: ", ft_ltoa(id));
	join = ft_strjoin(join, " is_wish_come() get ");
	join = ft_strjoin(join, ft_ltoa(ret));
	join = ft_strjoin(join, "\n");
	write(1, join, ft_strlen(join));

	// join = ft_strjoin(":::", ft_ltoa(&wish->let_me_eat));
	// join = ft_strjoin(join, "\n");
	// write(1, join, ft_strlen(join));

	ft_pthread_mutex_unlock(&wish->mutex);

	// if (ft_pthread_mutex_unlock(&wish->mutex))
	// 	return (LET_REJECT);

		// char	*join;
		// join = ft_strjoin(".", ft_ltoa(ret));
		// join = ft_strjoin(join, ".\n");
		// write(1, join, ft_strlen(join));


	return (ret);
}

int	thanks_a_host(t_wish *wish)
{
	if (ft_pthread_mutex_lock(&wish->mutex))
		return (ERROR);
	wish->let_me_eat = LET_THANK_YOU;
	if (ft_pthread_mutex_unlock(&wish->mutex))
		return (ERROR);
	return (SUCCESS);
}
