/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 13:37:10 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>
#include <philosophers.h>

static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num);
static int	threads_join(t_philo *philos, pthread_t *th_id, int philo_num);

int main(int argc, char* argv[]) {
	t_philo		*philos;
	pthread_t	*th_id;
	t_shere		shere;
	t_status	status;
	t_fork		*forks;

	if (parse_argment(argc, argv) != SUCCESS)
		return (1);
	if (init_status(&status, argv, argc) == ERROR)
		return (1);
	shere.philo_num = ft_strtol(argv[1], NULL, 10);
	shere.dead_info = init_t_dead(shere.philo_num);
	shere.wishs = init_wishs(shere.philo_num);
	shere.forks = init_fork(shere.philo_num);
	philos = init_philos(&status, &shere);
	th_id = init_th_id(shere.philo_num);

	// int i = 0;
	// while (i < shere.philo_num)
	// {
		// printf("%p\n", (philos[i].wish));
		// printf("%p\n", &(shere.wishs[i]));
		// printf("%p\n", &philos[i].wish->mutex);
		// printf("%p\n", &shere.wishs[i].mutex);

		// printf("%d\n", (philos[i].wish->let_me_eat));
		// printf("%d\n", shere.wishs[i].let_me_eat);
		// shere.wishs[i].let_me_eat = LET_YOU_ARE_ALREADY_DEAD;
		// printf("%d\n", (philos[i].wish->let_me_eat));
		// printf("%d\n", shere.wishs[i].let_me_eat);

		// printf("%p\n", &philos[i].wish->mutex);
		// printf("%p\n", &shere.wishs[i].mutex);
		// ft_pthread_mutex_lock(&philos[i].wish->mutex);
		// ft_pthread_mutex_trylock(&shere.wishs[i].mutex);
		// printf("--  --\n");
		// i++;
	// }
	if (threads_create(philos, th_id, shere.philo_num) == 1)
	{
		exit(1);
		return (1);
	}
	monitor_philos_death(&shere);
	if (threads_join(philos, th_id, shere.philo_num) == 2)
		return (2);
	return (0);
}

	// if (ft_pthread_mutex_trylock(&shere.forks->fork) == 0)
	// {
	// 	printf("LET_OK!\n");
	// }
	// if (ft_pthread_mutex_trylock(&shere.forks->fork) == 0)
	// {
	// 	printf("LET_OK!!\n");
	// }
	// else
	// {
	// 	printf("USED!\n");
	// }

	// if (guys_forks_avilable(shere.forks, 1, 4))
	// if (guys_forks_avilable(&shere, 4, 4))
	// {
	// 	printf("LET_OK!\n");
	// 	ft_pthread_mutex_lock(&shere.forks[4 % 4].fork);
	// 	ft_pthread_mutex_unlock(&shere.forks[4 % 4].fork);
	// 	return (0);
	// }
	// else
	// {
	// 	printf("NO!\n");
	// 	return (0);
	// }


static int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&th_id[i], NULL, &routine, &philos[i]) != 0)
		{
			printf("[FOOOOOOOOOOOO!!!]\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	threads_join(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_join(th_id[i], NULL) != 0)
		{
			printf("[NOOOOOOOOOOON!!!!!!!!]\n");
			return (2);
		}
		i++;
	}
	return (0);
}

