/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:15:39 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/29 09:14:03 by kakiba           ###   ########.fr       */
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
		return (ERROR);
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
		return (ERROR);
	return (SUCCESS);
}

int	lock_for_one(t_share *share,int own_id)
{
	if (ft_pthread_mutex_lock(&share->time_to_die_array[own_id].mutex))
		return (ERROR);
	return (SUCCESS);
}

int	unlock_for_one(t_share *share,int own_id)
{
	if (ft_pthread_mutex_unlock(&share->time_to_die_array[own_id].mutex))
		return (ERROR);
	return (SUCCESS);
}

int	lock_mini_first(t_share *share,int first_id, int id_1, int id_2)
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

int	unlock_mini_first(t_share *share,int first_id, int id_1, int id_2)
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
		if (lock_mini_first(share, own_id, left_id, right_id))
			return (ERROR);
	}
	else if (left_id < own_id && left_id < right_id)
	{
		if (lock_mini_first(share, left_id, own_id, right_id))
			return (ERROR);
	}
	else
	{
		if (lock_mini_first(share, right_id, own_id, left_id))
			return (ERROR);
	}
	return (SUCCESS);
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
		if (unlock_mini_first(share, own_id, left_id, right_id))
			return (ERROR);
	}
	else if (left_id < own_id && left_id < right_id)
	{
		if (unlock_mini_first(share, left_id, own_id, right_id))
			return (ERROR);
	}
	else
	{
		if (unlock_mini_first(share, right_id, own_id, left_id))
			return (ERROR);
	}
	return (SUCCESS);
}


int	is_ok_the_guy_take_forks(t_share *share,int own_id, int num)
{
	int left_id;
	int right_id;
	// char	*str;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (left_id == own_id || right_id == own_id)
	{
		// str = ft_strjoin(ft_itoa(own_id), ":");
		// str = ft_strjoin(str, ft_itoa(left_id));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_itoa(right_id));
		// str = ft_strjoin(str, "  same id false \n");
		// write(1, str, ft_strlen(str));
		return (false);
	}
	if (share->time_to_die_array[left_id].is_eating == false || \
		share->time_to_die_array[right_id].is_eating == false)
	{
		// str = ft_strjoin(ft_itoa(own_id), ":");
		// str = ft_strjoin(str, ft_itoa(left_id));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_itoa(right_id));
		// str = ft_strjoin(str, "  true \n");
		// write(1, str, ft_strlen(str));
		return (true);
	}
		// str = ft_strjoin(ft_itoa(own_id), ":");
		// str = ft_strjoin(str, ft_itoa(left_id));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_itoa(right_id));
		// str = ft_strjoin(str, "  false \n");
		// write(1, str, ft_strlen(str));
	return (false);
}

// int	is_ok_the_guy_take_forks(t_share *share,int own_id, int num)
// {
// 	int left_id;
// 	int right_id;
// 	long	left_time;
// 	long	right_time;

// 	left_id = ft_positive_mod(own_id - 1, num);
// 	right_id = ft_positive_mod(own_id + 1, num);
// 	if (left_id == own_id || right_id == own_id)
// 		return (false);
// 	if (share->time_to_die_array[left_id].is_eating == false || \
// 		share->time_to_die_array[right_id].is_eating == false)
// 		return (true);
// 	left_time = share->time_to_die_array[left_id].time_to_die;
// 	right_time = share->time_to_die_array[right_id].time_to_die;
// 	if (share->time_to_die_array[own_id].time_to_die <= left_time && \
// 		share->time_to_die_array[own_id].time_to_die <= right_time)
// 	{
// 		// ultra_debug2(share, own_id, left_id, right_id);
// 		return (true);
// 	}
// 	else if (left_time == -1 && right_time == -1)
// 	{
// 		// ultra_debug2(share, own_id, left_id, right_id);
// 		return (true);
// 	}
// 	else
// 	{
// 		// ultra_debug(share, own_id, left_id, right_id);
// 		return (false);
// 	}
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
    // char *red = "\x1b[31m"; // 赤色
    // char *green = "\x1b[32m"; // 緑色
    // char *reset = "\x1b[0m"; // リセット（色を元に戻す）
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
