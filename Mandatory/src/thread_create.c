/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:50:23 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 11:24:30 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&th_id[i + philo_num], NULL, &routine_init, &philos[i]) != 0)
		{
			// printf("ERROR\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor_create(t_share *share, int philo_num)
{
	int	i;

	i = 0;
	// printf("%p\n", share);
	// printf("%p:%p\n", &share[i].th_id[i], &share[i]);
	while (i < philo_num)
	{
		if (pthread_create(&share[i].th_id[i], NULL, &monitor_init, &share[i]) != 0)
		{
			// printf("ERROR\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	writer_create(t_queue *queue, pthread_t *th_id, int philo_num)
{
	if (pthread_create(&th_id[(philo_num * 2)], NULL, &writer_init, queue) != 0)
		return (ERROR);
	return (SUCCESS);
}

int	threads_join(pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num * 2 + 1)
	{
		if (pthread_join(th_id[i], NULL) != 0)
			return (2);
		// printf("joined %d\n", i);
		i++;
	}
	return (0);
}
