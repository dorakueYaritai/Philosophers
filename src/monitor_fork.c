/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:15:39 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/21 23:29:58 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <libft.h>

bool	guys_forks_avilable(t_share *share, int id, int num)
{
	bool	b1;
	bool	b2;
	bool	ret;

	ret = false;
	b1 = false;
	b2 = false;
	if (ft_pthread_mutex_trylock(&share->forks[id % num].fork) == SUCCESS)
	{
		b1 = true;
		ft_pthread_mutex_unlock(&share->forks[id % num].fork);
	}
	if (ft_pthread_mutex_trylock(&share->forks[(id + 1) % num].fork) == SUCCESS)
	{
		b2 = true;
		ft_pthread_mutex_unlock(&share->forks[(id + 1) % num].fork);
	}
	if (b1 && b2)
	{
		// write(1, "omedetou!\n", 10);
		return (true);
		// ret = true;
	}
	return (ret);
}


// bool	guys_forks_avilable(t_share *share, int id, int num)
// {
// 	bool	b1;
// 	bool	b2;
// 	bool	ret;

// 	ret = false;
// 	write(1, ft_ltoa(id), 2);
// 	write(1, "try!\n", 5);
// 	b1 = ft_pthread_mutex_trylock(&forks[id].fork);
// 	write(1, "tryed!\n", 7);
// 	if (b1)
// 		ft_pthread_mutex_unlock(&forks[id].fork);
// 	write(1, "try!\n", 5);
// 	b2 = ft_pthread_mutex_trylock(&forks[(id + 1) % num].fork);
// 	write(1, "tryed!\n", 7);
// 	if (b2)
// 		ft_pthread_mutex_unlock(&forks[(id + 1) % num].fork);
// 	if (b1 && b2)
// 		ret = true;
// 	return (ret);
// }

// bool	guys_forks_avilable(t_fork *forks, int id, int num)
// {
// 	bool	b1;
// 	bool	b2;
// 	bool	ret;

// 	ret = false;
// 	b1 = false;
// 	b2 = false;
// 	if (ft_pthread_mutex_trylock(&forks[id].fork) == SUCCESS)
// 	{
// 		b1 = true;
// 		ft_pthread_mutex_unlock(&forks[id].fork);
// 	}
// 	if (ft_pthread_mutex_trylock(&forks[(id + 1) % num].fork) == SUCCESS)
// 	{
// 		b2 = true;
// 		ft_pthread_mutex_unlock(&forks[(id + 1) % num].fork);
// 	}
// 	// write(1, "tryed!\n", 7);
// 	if (b1 && b2)
// 	{
// 		write(1, "omedetou!\n", 10);
// 		ret = true;
// 	}
// 	return (ret);
// }


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

// bool	is_ok_the_guy_eat(t_dead *dead_info, int id, int num)
int	is_ok_the_guy_eat(t_share *share,int id, int num)
{
	int left_id;
	int right_id;
	int	ret;
	time_t	array[3];

	// return (true);
	// if (guys_forks_avilable(share->forks, id, num) == true)
	// 	return (true);
	// if (guys_forks_avilable(share, id, num) == true)
	// 	return (true);
	left_id = ft_positive_mod(id - 1, num);
	right_id = ft_positive_mod(id + 1, num);
	ft_pthread_mutex_lock(&share->dead_info[id].mutex);
	array[0] = *share->dead_info[id].time_to_die;
	ft_pthread_mutex_unlock(&share->dead_info[id].mutex);

	ft_pthread_mutex_lock(&share->dead_info[left_id].mutex);
	array[1] = *share->dead_info[left_id].time_to_die;
	ft_pthread_mutex_unlock(&share->dead_info[left_id].mutex);

	ft_pthread_mutex_lock(&share->dead_info[right_id].mutex);
	array[2] = *share->dead_info[right_id].time_to_die;
	ft_pthread_mutex_unlock(&share->dead_info[right_id].mutex);

	// 死にそうランキング1位タイだったらOK
	// ultra_debug(id, left_id, right_id, share->dead_info);

	if (array[0] <= array[1] && array[0] <= array[2])
		return (LET_OK);
	else if (array[1] == -1 || array[2] == -1)
		return (LET_OK);
	else
		return (LET_TRY_TO_TAKE_FORKS);
}

int	is_ok_the_guy_eat2(t_share *share,int id, int num)
{
	int left_id;
	int right_id;
	char	*str;

	left_id = ft_positive_mod(id - 1, num);
	right_id = ft_positive_mod(id + 1, num);

	if (share->philos_time_to_dead[id] <= share->philos_time_to_dead[left_id] && \
		share->philos_time_to_dead[id] <= share->philos_time_to_dead[right_id])
	{
		// str = ft_strjoin(ft_ltoa(id), "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(left_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[left_id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(right_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[right_id]));
		// str = ft_strjoin(str, "\n");
		// write(1, str, ft_strlen(str));
		return (LET_OK);
	}
	else if (share->philos_time_to_dead[left_id] == -1 \
		|| share->philos_time_to_dead[right_id] == -1)
	{
		// str = ft_strjoin(ft_ltoa(id), "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(left_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[left_id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(right_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[right_id]));
		// str = ft_strjoin(str, "\n");
		return (LET_OK);
	}
	else
	{
		// str = ft_strjoin("false dayo!", ft_ltoa(id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(left_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[left_id]));
		// str = ft_strjoin(str, ":");
		// str = ft_strjoin(str, ft_ltoa(right_id));
		// str = ft_strjoin(str, "is :");
		// str = ft_strjoin(str, ft_ltoa(share->philos_time_to_dead[right_id]));
		// str = ft_strjoin(str, "\n");
		return (LET_TRY_TO_TAKE_FORKS);
	}
}


// int	feed_time_check(t_share *share, int id)
// {
// 	t_wish	*wish;

// 	wish = &share->wishs[id];
// 	ft_pthread_mutex_lock(&wish->mutex);
// 	if (wish->let_me_eat == LET_TRY_TO_TAKE_FORKS)
// 	{
// 		if (is_ok_the_guy_eat(share, id, share->philo_num) == true)
// 			wish->let_me_eat = LET_OK;
// 	}
// 	ft_pthread_mutex_unlock(&wish->mutex);
// 	return (SUCCESS);
// }
