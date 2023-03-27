/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:15:39 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 17:12:28 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <libft.h>
void	ultra_debug2(t_share *share, int id, int left_id, int right_id);

int	lock_for_two_people(t_share *share,int own_id, int opposite_id)
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
	{
		write(1, "BBBBB\n", 6);
		return (ERROR);
	}
	return (SUCCESS);
}

int	unlock_for_two_people(t_share *share,int own_id, int opposite_id)
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
	{
		write(1, "BBBBC\n", 6);
		return (ERROR);
	}
	return (SUCCESS);
}

int	lock_for_one(t_share *share,int own_id)
{
	if (ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex))
	{
		write(1, "BBBBC\n", 6);
		return (ERROR);
	}
	return (SUCCESS);
}

int	unlock_for_one(t_share *share,int own_id)
{
	if (ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex))
	{
		write(1, "BBCCC\n", 6);
		return (ERROR);
	}
	return (SUCCESS);
}

int	lock_right_own_left(t_share *share,int own_id, int num)
{
	int left_id;
	int right_id;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (share->philo_num == 1)
		return (lock_for_one(share, own_id));
	else if (share->philo_num == 2)
		return (lock_for_two_people(share, own_id, left_id));
	if (own_id < left_id && own_id < right_id)
	{
		ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex);
		if (left_id < right_id)
		{
			ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex);
			ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex);
		}
		else
		{
			ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex);
			ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex);
		}
	}
	else if (left_id < own_id && left_id < right_id)
	{
		ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex);
		if (own_id < right_id)
		{
			ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex);
			ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex);
		}
		else
		{
			ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex);
			ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex);
		}
	}
	else
	{
		ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex);
		if (own_id < left_id)
		{
			ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex);
			ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex);
		}
		else
		{
			ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex);
			ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex);
		}
	}
	return (0);
}

int	unlock_right_own_left(t_share *share,int own_id, int num)
{
	int left_id;
	int right_id;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (share->philo_num == 1)
		return (unlock_for_one(share, own_id));
	else if (share->philo_num == 2)
		return (unlock_for_two_people(share, own_id, left_id));
	if (own_id < left_id && own_id < right_id)
	{
		ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		if (left_id < right_id)
		{
			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		}
		else
		{
			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		}
	}
	else if (left_id < own_id && left_id < right_id)
	{
		ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		if (own_id < right_id)
		{
			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		}
		else
		{
			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		}
	}
	else
	{
		ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
		if (own_id < left_id)
		{
			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
		}
		else
		{
			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
		}
	}
	return (0);
}

// int	unlock_right_own_left(t_share *share,int own_id, int num)
// {
// 	int left_id;
// 	int right_id;

// 	left_id = ft_positive_mod(own_id - 1, num);
// 	right_id = ft_positive_mod(own_id + 1, num);
// 	if (left_id == own_id || right_id == own_id)
// 		return (ERROR);
// 	if (own_id < left_id && own_id < right_id)
// 	{
// 		if (left_id < right_id)
// 		{
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
// 		}
// 		else
// 		{
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
// 		}
// 		ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
// 	}
// 	else if (left_id < own_id && left_id < right_id)
// 	{
// 		if (own_id < right_id)
// 		{
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
// 		}
// 		else
// 		{
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
// 		}
// 		ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
// 	}
// 	else
// 	{
// 		if (own_id < left_id)
// 		{
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
// 		}
// 		else
// 		{
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex);
// 			ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
// 		}
// 		ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
// 	}
// 	return (0);
// }

int	is_ok_the_guy_take_forks(t_share *share,int own_id, int num)
{
	int left_id;
	int right_id;
	long	left_time;
	long	right_time;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (left_id == own_id || right_id == own_id)
		return (false);
	if (share->time_to_die_array[left_id].is_eating == true || \
		share->time_to_die_array[right_id].is_eating == true)
		return (false);
	// if (share->time_to_die_array[left_id].is_eating == false && \
	// 	share->time_to_die_array[right_id].is_eating == false)
	// 	return (true);

	// if (guys_forks_avilable(share, left_id, right_id, num) == true)
	// 	return (LET_OK);

	// ft_pthread_mutex_lock(&share->time_to_die_array[left_id].mutex);
	// ft_pthread_mutex_lock(&share->time_to_die_array[right_id].mutex);
	left_time = share->time_to_die_array[left_id].time_to_die;
	right_time = share->time_to_die_array[right_id].time_to_die;
	// ft_pthread_mutex_unlock(&share->time_to_die_array[left_id].mutex);
	// ft_pthread_mutex_unlock(&share->time_to_die_array[right_id].mutex);
	if (share->time_to_die_array[own_id].time_to_die <= left_time && \
		share->time_to_die_array[own_id].time_to_die <= right_time)
	{
		// ultra_debug2(share, own_id, left_id, right_id);
		return (true);
	}
	else if (left_time == -1 || right_time == -1)
	{
		// ultra_debug2(share, own_id, left_id, right_id);
		return (true);
	}
	else
	{
		// ultra_debug(share, own_id, left_id, right_id);
		return (false);
	}
}

// bool	guys_forks_avilable(t_share *share, int left_id, int right_id, int num)
// {
// 	bool	b1;
// 	bool	b2;

// 	b1 = false;
// 	b2 = false;
// 	if (ft_pthread_mutex_trylock(&share->forks[right_id].fork) == SUCCESS)
// 	{
// 		b1 = true;
// 		ft_pthread_mutex_unlock(&share->forks[right_id].fork);
// 	}
// 	if (ft_pthread_mutex_trylock(&share->forks[left_id].fork) == SUCCESS)
// 	{
// 		b2 = true;
// 		ft_pthread_mutex_unlock(&share->forks[left_id].fork);
// 	}
// 	if (b1 && b2)
// 		return (true);
// 	return (false);
// }

// bool	are_forks_not_avilable(t_share *share, int left_id, int right_id, int num)
// {
// 	bool	can_use_right;
// 	bool	can_use_left;

// 	can_use_right = false;
// 	can_use_left = false;
// 	if (ft_pthread_mutex_trylock(&share->forks[right_id].fork) == SUCCESS)
// 	{
// 		can_use_right = true;
// 		ft_pthread_mutex_unlock(&share->forks[right_id].fork);
// 	}
// 	if (ft_pthread_mutex_trylock(&share->forks[left_id].fork) == SUCCESS)
// 	{
// 		can_use_left = true;
// 		ft_pthread_mutex_unlock(&share->forks[left_id].fork);
// 	}
// 	if (can_use_right == false && can_use_left == false)
// 		return (true);
// 	return (false);
// }

void	ultra_debug(t_share *share, int id, int left_id, int right_id)
{
   char    *str;

    str = ft_strjoin("", "A[");
    str = ft_strjoin(str, ft_ltoa(id));
    str = ft_strjoin(str, "]");
    str = ft_strjoin(str, ": ");
    str = ft_strjoin(str, ft_ltoa(share->time_to_die_array[id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(left_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ": ");
    str = ft_strjoin(str, ft_ltoa(share->time_to_die_array[left_id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(right_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ":");
    str = ft_strjoin(str, ft_ltoa(share->time_to_die_array[right_id].time_to_die));
    str = ft_strjoin(str, ":\n");

	if (write(1, str, strlen(str)) == -1)
		return ;
}

void	ultra_debug2(t_share *share, int id, int left_id, int right_id)
{
    char *red = "\x1b[31m"; // 赤色
    char *green = "\x1b[32m"; // 緑色
    char *reset = "\x1b[0m"; // リセット（色を元に戻す）
   char    *str;

    // str = ft_strjoin(green, "A");
    str = ft_strjoin("=======", "A[");
    str = ft_strjoin(str, ft_ltoa(id));
    str = ft_strjoin(str, "] ");
    str = ft_strjoin(str, ": ");
    str = ft_strjoin(str, ft_ltoa(share->time_to_die_array[id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(left_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ": ");
    str = ft_strjoin(str, ft_ltoa(share->time_to_die_array[left_id].time_to_die));
    str = ft_strjoin(str, ": ");

    str = ft_strjoin(str, ft_ltoa(right_id));
    str = ft_strjoin(str, " ");
    str = ft_strjoin(str, ":");
    str = ft_strjoin(str, ft_ltoa(share->time_to_die_array[right_id].time_to_die));
    str = ft_strjoin(str, ":=======\n");
    // str = ft_strjoin(str, reset);

	if (write(1, str, strlen(str)) == -1)
		return ;
}
