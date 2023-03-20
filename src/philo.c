/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 18:58:49 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>
#include <philosophers.h>

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num);
static int	threads_join(pthread_t *th_id, int philo_num);

int main(int argc, char* argv[]) {
	t_philo		*philos;
	pthread_t	*th_id;
	t_shere		shere;
	t_status	status;

	// printf("OKQ\n");
	if (parse_argment(argc, argv) != SUCCESS)
		return (1);
	// printf("OKQ\n");
	if (init_status(&status, argv, argc) == ERROR)
		return (1);
	init_shere(&shere, &status, argv[1]);
	philos = init_philos(&status, &shere);
	th_id = init_th_id(shere.philo_num);
	if (threads_create(philos, th_id, shere.philo_num) == 1)
	{
		exit(1);
		return (1);
	}
	monitor_philos_death(&shere);
	if (threads_join(th_id, shere.philo_num) == 2)
		return (2);
	return (0);
}

	// int i = 0;
	// while (i < shere.philo_num)
	// {
	// 	printf("%p\n", &(philos[i].status.must_eat_times));
	// 	printf("%p\n", (shere.dead_info[i].must_eat_times));
	// 	printf("--  --\n");
	// 	i++;
	// }

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&th_id[i], NULL, &routine, &philos[i]) != 0)
		{
			// printf("[FOOOOOOOOOOOO!!!]\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	threads_join(pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	// write(1, "join!\n", 6);
	// printf("join !\n");
	while (i < philo_num)
	{
		if (pthread_join(th_id[i], NULL) != 0)
		{
			// printf("[NOOOOOOOOOOON!!!!!!!!]\n");
			return (2);
		}
		i++;
	}
	return (0);
}

