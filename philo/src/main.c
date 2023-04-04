/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/04 09:21:14 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

void	ft_free(void *memory);
int		parse_argment(int argc, char *argv[]);
void	free_all(t_share *shares, t_philo *philo);
int		init_values(t_env *values, int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_env		values;

	if (parse_argment(argc, argv))
		return (ERROR);
	if (init_values(&values, argc, argv) == ERROR)
		return (ERROR);
	if (all_threads_create(values.philos, values.shares))
	{
		free_all(values.shares, values.philos);
		return (ERROR);
	}
	if (threads_join(values.share.th_id, values.share.philo_num) == 2)
	{
		free_all(values.shares, values.philos);
		return (2);
	}
	free_all(values.shares, values.philos);
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
	if (shares == NULL)
		return ;
	ft_free(shares->philos_time_to_dead);
	ft_free(shares->philos_eat_times);
	ft_free(shares->th_id);
	ft_free(shares->wishs);
	ft_free(shares->forks);
	ft_free(shares->queue->list);
	ft_free(shares->queue);
	ft_free(shares->time_to_die_array);
	ft_free(shares);
	ft_free(philo);
}

int	init_values(t_env *values, int argc, char *argv[])
{
	memset(values, 0, sizeof(t_env));
	if (init_status(&values->status, argv, argc))
		return (ERROR);
	if (init_share(&values->share, &values->status, argv[1]))
		return (ERROR);
	values->shares = init_shares(&values->share);
	if (values->shares == NULL)
	{
		free_all(values->shares, NULL);
		return (ERROR);
	}
	values->philos = init_philos(&values->status, &values->share);
	if (values->philos == NULL)
	{
		free_all(values->shares, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}
