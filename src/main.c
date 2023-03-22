/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 15:35:35 by kakiba           ###   ########.fr       */
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
		destroy_shared_resourses(&share->dead_info[i].mutex);
		destroy_shared_resourses(&share->forks[i].fork);
		i++;
	}
	ft_free(share->philos_time_to_dead);
	ft_free(share->philos_eat_times);
	ft_free(share->th_id);
	ft_free(share->wishs);
	ft_free(share->dead_info);
	ft_free(share->forks);
	ft_free(philo);
}

int main(int argc, char* argv[]) {
	t_philo		*philos;
	t_share		share;
	t_status	status;

	if (parse_argment(argc, argv) != SUCCESS)
		return (1);
	if (init_status(&status, argv, argc) == ERROR)
		return (1);
	init_share(&share, &status, argv[1]);
	philos = init_philos(&status, &share);
	share.th_id = init_th_id(share.philo_num + 1);
	if (threads_create(philos, share.th_id, share.philo_num) == ERROR)
	{
		return (ERROR);
	}
	if (writer_create(share.queue, share.th_id, share.philo_num + 1) == ERROR)
		return (ERROR);
	monitor_philos_death(&share);
	if (threads_join(share.th_id, share.philo_num) == 2)
		return (2);
	free_all(&share, philos, share.philo_num);
	return (0);
}

	// int i = 0;
	// while (i < share.philo_num)
	// {
	// 	printf("%p\n", &(philos[i].status.must_eat_times));
	// 	printf("%p\n", (share.dead_info[i].must_eat_times));
	// 	printf("--  --\n");
	// 	i++;
	// }

