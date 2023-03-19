/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:16:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 09:22:11 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
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

int	threads_join(t_philo *philos, pthread_t *th_id, int philo_num)
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

int kill_everyone(t_dead *dead_info_array, int philo_num, int dead_id)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (i != dead_id)
			pthread_mutex_lock(&dead_info_array[i].is_death_mutex);
			// pthread_mutex_lock(&philos[i].dead_info.is_death_mutex);
		// philos[i].dead_info.is_death = true;
		dead_info_array[i].is_death = true;
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		// pthread_mutex_unlock(&philos[i].dead_info.is_death_mutex);
		pthread_mutex_unlock(&dead_info_array[i].is_death_mutex);
		i++;
	}
}

int	print_sub(int id, long sec_milli, long sec_milli_philo)
{
	char	*id_str;
	char	*join;

	id_str = ft_itoa(id);
	join = ft_strjoin(id_str, "/now:");
	join = ft_strjoin(join, ft_ltoa(sec_milli));
	join = ft_strjoin(join, " vs philo:");
	join = ft_strjoin(join, ft_ltoa(sec_milli_philo));
	join = ft_strjoin(join, "\n");
	write(1, join, ft_strlen(join));
}

// PTHREAD_MUTEX_INITIALIZER()
int monitor_philos_death(t_dead *dead_info_array, int philo_num)
{
	int	i;
	struct timeval t1;
	long sec_milli;

	while (1)
	{
		i = 0;
		while (i < philo_num)
		{
			pthread_mutex_lock(&dead_info_array[i].is_death_mutex);
			gettimeofday(&t1, NULL);
			sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
			if (*dead_info_array[i].time_to_die < sec_milli && *dead_info_array[i].time_to_die != -1)
			{
				kill_everyone(dead_info_array, philo_num, i);
				return (print_time(i, sec_milli, DEAD, NONE));
			}
			pthread_mutex_unlock(&dead_info_array[i].is_death_mutex);
			i++;
		}
		usleep(5000);
	}
	return (0);
}

int main(int argc, char* argv[]) {
	t_philo		*philos;
	pthread_t	*th_id;
	t_dead		*dead_info_array;
	int			philo_num;

	if (parse_argment(argc, argv) == 1)
		return (1);
	philo_num = atoi(argv[1]);
	dead_info_array = init_t_dead(philo_num);
	philos = init_philo(argv, init_fork(philo_num), dead_info_array);
	th_id = init_th_id(argv);

	if (threads_create(philos, th_id, philo_num) == 1)
		return (1);
	monitor_philos_death(dead_info_array, philo_num);
	if (threads_join(philos, th_id, philo_num) == 2)
		return (2);
	return (0);
}

	// int i = 0;
	// while (i < philo_num)
	// {
	// 	// printf("%p\n", (&philos[i].dead_info));
	// 	// printf("%p\n", (&philos[i].dead_info2));
	// 	// printf("%p\n", (philos[i].dead_info2));
	// 	// printf("%p\n", (philos[i].dead_info));
	// 	// printf("%p\n", (&dead_info_array[i]));
	// 	// printf("--  --\n");

	// 	printf("%p\n", (philos[i].dead_info2.is_death_mutex));
	// 	if (pthread_mutex_lock(&philos[i].dead_info2.is_death_mutex))
	// 		return (-1);
	// 	printf("%p\n", (&philos[i].dead_info2.is_death_mutex));
	// 	printf("%p\n", (philos[i].dead_info->is_death_mutex));
	// 	if (pthread_mutex_lock(&philos[i].dead_info->is_death_mutex))
	// 		return (-1);
	// 	printf("%p\n", (&philos[i].dead_info->is_death_mutex));
	// 	printf("%p\n", (&dead_info_array[i].is_death_mutex));
	// 	printf("------\n");
	// 	i++;
	// }

