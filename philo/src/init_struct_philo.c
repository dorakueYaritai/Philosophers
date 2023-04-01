/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:05:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/30 20:38:57 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static int	init_philo_sub(t_philo *philo, t_status *status, t_share *share);

t_philo	*init_philos(t_status *status, t_share *share)
{
	int			i;
	int			philo_num;
	t_philo		*philos;

	philo_num = share->philo_num;
	philos = malloc(sizeof(t_philo) * philo_num);
	i = 0;
	if (share == NULL || share->forks == NULL)
		return (NULL);
	while (i < philo_num)
	{
		philos[i].philo_id = i;
		init_philo_sub(&philos[i], status, share);
		i++;
	}
	return (philos);
}

static int	init_philo_sub(t_philo *philo, t_status *status, t_share *share)
{
	int	i;
	int	philo_num;

	philo_num = share->philo_num;
	i = philo->philo_id;
	philo->status = *status;
	philo->wish = &share->wishs[i];
	philo->forks[FIRST] = &share->forks[i];
	philo->forks[SECOND] = &share->forks[(i + 1) % philo_num];
	return (SUCCESS);
}
