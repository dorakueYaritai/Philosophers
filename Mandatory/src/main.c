/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 11:24:43 by kakiba           ###   ########.fr       */
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

void	free_all(t_share *share, t_philo *philo, int num)
{
	(void)philo;
	int	i;

	i = 0;
	while (i < num)
	{
		destroy_shared_resourses(&share->wishs[i].mutex);
		destroy_shared_resourses(&share->forks[i].fork);
		i++;
	}
	ft_free(share->philos_time_to_dead);
	ft_free(share->philos_eat_times);
	ft_free(share->th_id);
	ft_free(share->wishs);
	ft_free(share->forks);
	ft_free(philo);
	destroy_shared_resourses(&share->queue->mutex);
	ft_free(share->queue->list);
	ft_free(share->queue);
}

t_share	*init_shares(t_share *share)
{
	t_share	*share_array;
	long	i;

	share_array = malloc(sizeof(t_share) * share->philo_num);
	if (share_array == NULL)
	{
		printf("OH!!!!!!\n");
		exit(1);
	}
	i = 0;
	while (i < share->philo_num)
	{
		share_array[i] = *share;
		share_array[i].philo_id = i;
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
		i++;
	}
	return (share_array);
}

int main(int argc, char* argv[]) {
	t_philo		*philos;
	t_share		share;
	t_share		*shares;
	t_status	status;

	if (parse_argment(argc, argv) != SUCCESS)
		return (1);
	if (init_status(&status, argv, argc) == ERROR)
		return (1);
	init_share(&share, &status, argv[1]);
	shares = init_shares(&share);
	philos = init_philos(&status, &share);
	if (monitor_create(shares, share.philo_num) == ERROR) 
		return (ERROR);
	if (threads_create(philos, share.th_id, share.philo_num) == ERROR)
		return (ERROR);
	if (writer_create(share.queue, share.th_id, share.philo_num) == ERROR)
		return (ERROR);

	// if (monitor_create(&share, share.philo_num) == ERROR) 
	// 	return (ERROR);
	// if (threads_create(philos, share.th_id, share.philo_num) == ERROR)
	// 	return (ERROR);
	// if (writer_create(share.queue, share.th_id, share.philo_num) == ERROR)
	// 	return (ERROR);
	// monitor_philos(&share);
	if (threads_join(share.th_id, share.philo_num) == 2)
		return (2);
	free_all(&share, philos, share.philo_num);
	return (0);
}

	// int i = 0;
	// while (i < share.philo_num)
	// {
	// 	printf("%p\n", &(philos[i].status.must_eat_times));
	// 	printf("--  --\n");
	// 	i++;
	// }

