/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:03:13 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 10:02:13 by kakiba           ###   ########.fr       */
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
}