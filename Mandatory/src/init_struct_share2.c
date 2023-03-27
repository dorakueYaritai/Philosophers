/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_share2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:46:58 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 09:45:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <libft.h>

// int	init_shared_resourse(t_shared_resourse	*resourse)
// {
// 	if (pthread_mutex_init(&resourse->is_available_mutex, NULL) == -1)
// 		return (ERROR);
// 	if (pthread_mutex_init(&resourse->stuff, NULL) == -1)
// 		return (ERROR);
// 	resourse->is_available = true;
// 	return (SUCCESS);
// }

int	init_shared_resourse(t_shared_resourse	*resourse)
{
	resourse->is_available_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	resourse->stuff = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	resourse->is_available = true;
	return (SUCCESS);
}

pthread_t	*init_th_id(int thread_num)
{
	pthread_t *th;

	th =  malloc(sizeof(pthread_t) * thread_num);
	if (th == NULL)
		return (NULL);
	return (th);
}

int	init_status(t_status *status, char **argv, int argc)
{
	status->time_to_starve = ft_strtol(argv[2], NULL, 10);
	status->time_to_eat = ft_strtol(argv[3], NULL, 10);
	status->time_to_sleep = ft_strtol(argv[4], NULL, 10);
	status->time_to_die = -1;
	if (status->time_to_starve > INT_MAX || \
		status->time_to_sleep > INT_MAX || \
		status->time_to_eat > INT_MAX)
		return (ERROR);
	if (argc == 6)
		status->must_eat_times = ft_strtol(argv[5], NULL, 10);
	else
		status->must_eat_times = -1;
	return (SUCCESS);
}

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (queue == NULL)
		return (NULL);
	if (init_shared_resourse(&queue->mutex) == ERROR)
		return (NULL);
	queue->list = NULL;
	queue->do_proceed = true;
	return (queue);
}
