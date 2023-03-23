/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:50:23 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 19:13:46 by kakiba           ###   ########.fr       */
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
		if (pthread_create(&th_id[i], NULL, &routine_init, &philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	writer_create(t_queue *queue, pthread_t *th_id, int writer_id)
{
	if (pthread_create(&th_id[writer_id], NULL, &writer_init, queue) != 0)
		return (ERROR);
	return (SUCCESS);
}

int	threads_join(pthread_t *th_id, int thread_num)
{
	int	i;

	i = 0;
	while (i < thread_num)
	{
		if (pthread_join(th_id[i], NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}
