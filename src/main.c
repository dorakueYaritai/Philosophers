/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 11:17:38 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>
#include <philosophers.h>

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num);
static int	threads_join(pthread_t *th_id, int philo_num);

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

	// printf("OKQ\n");
	if (parse_argment(argc, argv) != SUCCESS)
		return (1);
	// printf("OKQ\n");
	if (init_status(&status, argv, argc) == ERROR)
		return (1);
	init_share(&share, &status, argv[1]);
	philos = init_philos(&status, &share);
	share.th_id = init_th_id(share.philo_num);

	if (threads_create(philos, share.th_id, share.philo_num) == ERROR)
	{
		return (ERROR);
	}	
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

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&th_id[i], NULL, &routine_init, &philos[i]) != 0)
		{
			// printf("[FOOOOOOOOOOOO!!!]\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	threads_join(pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	// write(1, "join!\n", 6);
	// printf("join !\n");
	while (i < philo_num)
	{
		if (pthread_join(th_id[i], NULL) != 0)
		{
			// printf("[NOOOOOOOOOOON!!!!!!!!]\n");
			return (2);
		}
		i++;
	}
	return (0);
}

