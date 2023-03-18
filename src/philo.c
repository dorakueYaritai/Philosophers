#include <philosophers.h>

int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (philos[i].is_death == false)
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

int kill_everyone(t_philo *philos, 
	t_dead *dead_info_array, int philo_num, int dead_id)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (i != dead_id)
			pthread_mutex_lock(&dead_info_array[i].is_death_mutex);
		dead_info_array[i].is_death = true;
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_unlock(&dead_info_array[i].is_death_mutex);
		i++;
	}
}

int monitor_philos_death(t_philo *philos, 
	t_dead *dead_info_array, int philo_num)
{
	int	i;
	struct timeval t1;
	long sec_milli;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&dead_info_array[i].is_death_mutex);
		gettimeofday(&t1, NULL);
		sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
		if (philos[i].time_to_die != -1 && philos[i].time_to_die <= sec_milli)
		{
			kill_everyone(philos, dead_info_array, philo_num, i);
			print_time(i, sec_milli, DEAD, NONE);
		}
	}
}


int main(int argc, char* argv[]) {
	t_philo		*philos;
	pthread_t	*th_id;
	t_fork	*forks;
	t_dead	*dead_info_array;
	int			philo_num;

	if (parse_argment(argc, argv) == 1)
		return (1);
	philo_num = atoi(argv[1]);
	forks = init_fork(philo_num);
	dead_info_array = init_t_dead(philo_num);
	philos = init_philo(argv, forks);
	th_id = init_th_id(argv);
	if (threads_create(philos, th_id, philo_num) == 1)
		return (1);
	// monitor_philos_death(philos, dead_info_array, philo_num);
	if (threads_join(philos, th_id, philo_num) == 2)
		return (2);
}
