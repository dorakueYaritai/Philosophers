/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:03:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/21 16:43:45 by kakiba           ###   ########.fr       */
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

int	init_shere(t_shere *shere, t_status *status, char *philo_num_arg)
{
	int	i;

	shere->philo_num = ft_strtol(philo_num_arg, NULL, 10);
	shere->dead_info = init_t_dead(shere->philo_num);
	shere->wishs = init_wishs(shere->philo_num);
	shere->forks = init_fork(shere->philo_num);
	i = 0;
	if (status->must_eat_times < 0)
		shere->must_eat_times_exists = false;
	else
		shere->must_eat_times_exists = true;
}
