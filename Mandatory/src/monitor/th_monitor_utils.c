/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:29:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/31 13:37:33 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>
void	ultra_debug2(t_share *share, int id, int left_id, int right_id);
void	ultra_debug(t_share *share, int id, int left_id, int right_id);

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

bool	whethre_allow_taking_the_fork(t_share *share, int own_id, int num)
{
	int		left_id;
	int		right_id;
	long	left_time;
	long	right_time;

	left_id = ft_positive_mod(own_id - 1, num);
	right_id = ft_positive_mod(own_id + 1, num);
	if (left_id == own_id || right_id == own_id)
	{
		exit(1);
		return (false);
	}
	if (share->time_to_die_array[left_id].is_taking_fork == false
		&& share->time_to_die_array[right_id].is_taking_fork == false)
	{
		ultra_debug2(share, own_id, left_id, right_id);
		return (true);
	}
	if (share->time_to_die_array[left_id].is_taking_fork == true
		&& share->time_to_die_array[right_id].is_taking_fork == true)
	{
		ultra_debug(share, own_id, left_id, right_id);
		return (false);
	}
	left_time = share->time_to_die_array[left_id].time_to_die;
	right_time = share->time_to_die_array[right_id].time_to_die;
	if (share->time_to_die_array[own_id].time_to_die <= left_time
		&& share->time_to_die_array[own_id].time_to_die <= right_time)
	{
		ultra_debug2(share, own_id, left_id, right_id);
		return (true);
	}
	return (false);
}

bool	did_the_old_man_go_heaven(t_share *share, int id)
{
	long			crrent_time;

	crrent_time = ft_get_time_in_millisec();
	if (crrent_time == -1)
		return (true);
	if ((share->time_to_die_array[id].time_to_die < crrent_time && \
		share->time_to_die_array[id].time_to_die != -1))
		return (true);
	return (false);
}

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
