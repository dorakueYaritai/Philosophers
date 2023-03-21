/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:03:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 07:51:53 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

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

int	init_share(t_share *share, t_status *status, char *philo_num_arg)
{
	int	i;

	share->philo_num = ft_strtol(philo_num_arg, NULL, 10);
	share->dead_info = init_t_dead(share->philo_num);
	share->wishs = init_wishs(share->philo_num);
	share->forks = init_fork(share->philo_num);
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
