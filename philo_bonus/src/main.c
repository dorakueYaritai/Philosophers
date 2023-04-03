/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/30 20:50:31 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

void	ft_free(void *memory);
int		parse_argment(int argc, char *argv[]);
void	free_all(t_share *shares, t_philo *philo);

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	t_share		share;
	t_share		*shares;
	t_status	status;

	if (parse_argment(argc, argv))
		return (ERROR);
	if (init_status(&status, argv, argc))
		return (ERROR);
	if (init_share(&share, &status, argv[1]))
		return (ERROR);
	shares = init_shares(&share);
	philos = init_philos(&status, &share);
	if (all_threads_create(philos, shares))
	{
		free_all(shares, philos);
		return (ERROR);
	}
	if (threads_join(share.th_id, share.philo_num) == 2)
	{
		free_all(shares, philos);
		return (2);
	}
	free_all(shares, philos);
	return (SUCCESS);
}

void	ft_free(void *memory)
{
	if (memory)
		free (memory);
}

int	parse_argment(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
		return (ERR_ARG_NUM);
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i], 0) == false)
		{
			return (ERR_INVALID_ARG);
		}
		i++;
	}
	return (SUCCESS);
}

void	free_all(t_share *shares, t_philo *philo)
{
	ft_free(shares->philos_time_to_dead);
	ft_free(shares->philos_eat_times);
	ft_free(shares->th_id);
	ft_free(shares->wishs);
	ft_free(shares->forks);
	ft_free(philo);
	ft_free(shares->queue->list);
	ft_free(shares->queue);
	ft_free(shares->time_to_die_array);
	ft_free(shares);
}
