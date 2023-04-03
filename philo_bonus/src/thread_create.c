/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:50:23 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/30 20:32:11 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	all_threads_create(t_philo *philos, t_share *shares)
{
	int	i;

	i = 0;
	while (i < shares->philo_num)
	{
		if (pthread_create(&shares->th_id[i], NULL, &monitor_init, &shares[i]))
			return (ERROR);
		i++;
	}
	while (i < shares->philo_num * 2)
	{
		if (pthread_create(&shares->th_id[i], \
			NULL, &routine_init, &philos[i - shares->philo_num]))
			return (ERROR);
		i++;
	}
	if (pthread_create(&shares->th_id[i], NULL, &writer_init, shares->queue))
		return (ERROR);
	return (SUCCESS);
}

int	threads_join_and_deteach(pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num * 2)
	{
		if (pthread_detach(th_id[i]))
			return (ERROR);
		i++;
	}
	if (pthread_join(th_id[i], NULL))
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
		i++;
	}
	return (0);
}

// int	deteach_threads_except_writer(pthread_t *th_id, int philo_num)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo_num * 2)
// 	{
// 		if (pthread_detach(th_id[i]) != 0)
// 			return (2);
// 		i++;
// 	}
// 	return (0);
// }
