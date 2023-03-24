/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:03:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 19:19:04 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	init_share(t_share *share, t_status *status, char *philo_num_arg)
{
	int	i;

	share->philo_num = ft_strtol(philo_num_arg, NULL, 10);
	share->dead_info = init_t_dead(share->philo_num);
	share->wishs = init_wishs(share->philo_num);
	share->forks = init_fork(share->philo_num);
	share->queue = init_queue();
	share->philos_time_to_dead = malloc(sizeof(time_t) * share->philo_num);
	share->philos_eat_times = malloc(sizeof(int) * share->philo_num);
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

t_dead	*init_t_dead(int philo_num)
{
	t_dead	*dead_check;
	int	i;

	i = 0;
	dead_check = malloc(sizeof(t_dead) * philo_num);
	if (dead_check == NULL)
		return (NULL);
	while (i < philo_num)
	{
		if (init_shared_resourse(&dead_check[i].mutex) == ERROR)
			return (NULL);
		// dead_check[i].is_death = false;
		i++;
	}
	return (dead_check);
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
		wishs[i].request = LET_OK;
		wishs[i].fork_id = 0;
		wishs[i].sec_milli = 0;
		i++;
	}
	return (wishs);
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
	return (queue);
}
