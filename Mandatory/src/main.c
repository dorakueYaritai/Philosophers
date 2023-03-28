/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/28 15:12:02 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	destroy_shared_resourses(t_shared_resourse	*resourse)
{
	if (pthread_mutex_destroy(&resourse->stuff) == -1)
		return (ERROR);
	if (pthread_mutex_destroy(&resourse->is_available_mutex) == -1)
		return (ERROR);
	return (SUCCESS);
}

void	ft_free(void *memory)
{
	if (memory)
		free (memory);
}

void	free_all(t_share *shares, t_philo *philo)
{
	ft_free(shares->philos_time_to_dead);
	ft_free(shares->philos_eat_times);
	ft_free(shares->th_id);
	ft_free(shares->wishs);
	ft_free(shares->forks);
	ft_free(philo);
	ft_free(shares->queue->list);
	ft_free(shares->queue);
	ft_free(shares->time_to_die_array);
	ft_free(shares);
}

t_share	*init_shares(t_share *share)
{
	t_share	*share_array;
	long	i;

	share_array = malloc(sizeof(t_share) * share->philo_num);
	if (share_array == NULL)
		return (NULL);
	i = 0;
	while (i < share->philo_num)
	{
		share_array[i] = *share;
		// share_array[i].philo_id = i;

		// share_array[i].forks = share->forks;
		// share_array[i].must_eat_times = share->must_eat_times;
		// share_array[i].must_eat_times_exists = share->must_eat_times_exists;
		// share_array[i].philo_id = i;
		// share_array[i].philo_num = share->philo_num;
		// share_array[i].philos_eat_times = share->philos_eat_times;

		// share_array[i].philos_time_to_dead = share->philos_time_to_dead;
		// share_array[i].queue = share->queue;
		// share_array[i].th_id = share->th_id;
		// share_array[i].time_to_starve = share->time_to_starve;
		// share_array[i].wishs = share->wishs;
		// share_array[i].time_to_die_array = share->time_to_die_array;

		i++;
	}
	return (share_array);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	t_share		share;
	t_share		*shares;
	t_status	status;

	if (parse_argment(argc, argv))
		return (ERROR);
	if (init_status(&status, argv, argc))
		return (ERROR);
	if (init_share(&share, &status, argv[1]))
		return (ERROR);
	shares = init_shares(&share);
	philos = init_philos(&status, &share);
	if (all_threads_create(philos, shares))
	{
		free_all(shares, philos);
		return (ERROR);
	}
	if (threads_join(share.th_id, share.philo_num) == 2)
	{
		free_all(shares, philos);
		return (2);
	}
	free_all(shares, philos);
	return (0);
}

	// if (monitor_create(shares, share.philo_num) == ERROR) 
	// 	return (ERROR);
	// if (threads_create(philos, share.th_id, share.philo_num) == ERROR)
	// 	return (ERROR);
	// if (writer_create(share.queue, share.th_id, share.philo_num) == ERROR)
	// 	return (ERROR);
