/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:15:39 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 19:34:17 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <libft.h>

int	is_ok_the_guy_take_forks(t_share *share,int own_id, int num)
{
	int left_id;
	int right_id;
	char	*str;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (left_id == own_id || right_id == own_id)
		return (false);
	// if (guys_forks_avilable(share, left_id, right_id, num) == true)
	// 	return (LET_OK);
	if (share->philos_time_to_dead[own_id] <= share->philos_time_to_dead[left_id] && \
		share->philos_time_to_dead[own_id] <= share->philos_time_to_dead[right_id])
		return (true);
	else if (share->philos_time_to_dead[left_id] == -1 \
		|| share->philos_time_to_dead[right_id] == -1)
		return (true);
	else
		return (false);
}

bool	guys_forks_avilable(t_share *share, int left_id, int right_id, int num)
{
	bool	b1;
	bool	b2;

	b1 = false;
	b2 = false;
	if (ft_pthread_mutex_trylock(&share->forks[right_id].fork) == SUCCESS)
	{
		b1 = true;
		ft_pthread_mutex_unlock(&share->forks[right_id].fork);
	}
	if (ft_pthread_mutex_trylock(&share->forks[left_id].fork) == SUCCESS)
	{
		b2 = true;
		ft_pthread_mutex_unlock(&share->forks[left_id].fork);
	}
	if (b1 && b2)
		return (true);
	return (false);
}

bool	are_forks_not_avilable(t_share *share, int left_id, int right_id, int num)
{
	bool	can_use_right;
	bool	can_use_left;

	can_use_right = false;
	can_use_left = false;
	if (ft_pthread_mutex_trylock(&share->forks[right_id].fork) == SUCCESS)
	{
		can_use_right = true;
		ft_pthread_mutex_unlock(&share->forks[right_id].fork);
	}
	if (ft_pthread_mutex_trylock(&share->forks[left_id].fork) == SUCCESS)
	{
		can_use_left = true;
		ft_pthread_mutex_unlock(&share->forks[left_id].fork);
	}
	if (can_use_right == false && can_use_left == false)
		return (true);
	return (false);
}

void	ultra_debug(int id, int left_id, int right_id, t_dead *dead_info)
{
   char    *str;

    str = ft_strjoin("", "A");
    str = ft_strjoin(str, ft_ltoa(id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ft_ltoa(*dead_info[id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(left_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ft_ltoa(*dead_info[left_id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(right_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ft_ltoa(*dead_info[right_id].time_to_die));
    str = ft_strjoin(str, ": \n");
	write(1, str, strlen(str));
}
