/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_share1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:03:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 22:40:49 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

//1
int				init_alloc_member(t_share *share);
t_time_to_die	*init_time_to_die_array(int philo_num);
t_fork			*init_fork(int philo_num);
t_wish			*init_wishs(int philo_num);

//2
int				init_shared_resourse(t_shared_resourse	*resourse);
t_queue			*init_queue(void);
pthread_t		*init_th_id(int thread_num);
int				init_status(t_status *status, char **argv, int argc);

int	init_share(t_share *share, t_status *status, char *philo_num_arg)
{
	int	i;

	ft_memset(share, 0, sizeof(t_share));
	share->philo_num = ft_strtol(philo_num_arg, NULL, 10);
	if (share->philo_num <= 0)
		return (ERROR);
	if (init_alloc_member(share))
		return (ERROR);
	i = 0;
	while (i < share->philo_num)
	{
		share->philos_time_to_dead[i] = -1;
		share->philos_eat_times[i] = 0;
		i++;
	}
	if (status->must_eat_times < 0)
		share->must_eat_times_exists = false;
	else
		share->must_eat_times_exists = true;
	share->time_to_starve = status->time_to_starve;
	share->must_eat_times = status->must_eat_times;
	return (0);
}

int	init_alloc_member(t_share *share)
{
	share->wishs = init_wishs(share->philo_num);
	share->forks = init_fork(share->philo_num);
	share->queue = init_queue();
	share->th_id = init_th_id((share->philo_num * 2) + 1);
	share->time_to_die_array = init_time_to_die_array(share->philo_num);
	share->philos_eat_times = malloc(sizeof(int) * share->philo_num);
	share->philos_time_to_dead = malloc(sizeof(time_t) * share->philo_num);
	if (share->wishs == NULL || share->forks == NULL || share->queue == NULL || \
		share->th_id == NULL || share->philos_time_to_dead == NULL || \
		share->time_to_die_array == NULL || share->philos_eat_times == NULL)
		return (ERROR);
	return (SUCCESS);
}

t_time_to_die	*init_time_to_die_array(int philo_num)
{
	t_time_to_die	*time_to_die_array;
	int				i;

	time_to_die_array = malloc(sizeof(t_time_to_die) * philo_num);
	if (time_to_die_array == NULL)
		return (NULL);
	i = 0;
	while (i < philo_num)
	{
		if (init_shared_resourse(&time_to_die_array[i].mutex) == ERROR)
			return (NULL);
		time_to_die_array[i].time_to_die = -1;
		time_to_die_array[i].is_eating = false;
		i++;
	}
	return (time_to_die_array);
}

t_fork	*init_fork(int philo_num)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * philo_num);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < philo_num)
	{
		if (init_shared_resourse(&forks[i].fork) == ERROR)
			return (NULL);
		forks[i].fork_id = i;
		i++;
	}
	return (forks);
}

t_wish	*init_wishs(int philo_num)
{
	t_wish	*wishs;
	int		i;

	wishs = malloc(sizeof(t_wish) * philo_num);
	if (wishs == NULL)
	{
		exit(1);
		return (NULL);
	}
	i = 0;
	while (i < philo_num)
	{
		if (init_shared_resourse(&wishs[i].mutex) == ERROR)
		{
			exit(1);
			return (NULL);
		}
		wishs[i].request_info.request = LET_OK;
		wishs[i].request_info.fork_id = 0;
		wishs[i].request_info.act_time = 0;
		i++;
	}
	return (wishs);
}