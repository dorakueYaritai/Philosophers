#include <philosophers.h>

pthread_t	*init_th_id(int argc, char *argv[])
{
	(void)argc;
	return (malloc(sizeof(pthread_t *) * strtol(argv[1], NULL, 10)));
}

t_philo	*init_philo(int argc, char *argv[], pthread_mutex_t	*mutex)
{
	size_t	i;
	size_t	philo_num = strtol(argv[1], NULL, 10);
	t_philo	*philo;
	philo = malloc(sizeof(t_philo) * philo_num + 1);
	i = 0;
	while (i < philo_num)
	{
		philo[i].time_to_starve = strtol(argv[2], NULL, 10);
		philo[i].time_to_eat = strtol(argv[3], NULL, 10);
		philo[i].time_to_sleep = strtol(argv[4], NULL, 10);
		philo[i].time_to_die = -1;
		philo[i].isdeath = false;
		philo[i].philo_id = i;
		philo[i].forks = mutex;
		i++;
	}
	philo[i].isdeath = true;
	return (philo);
}

pthread_mutex_t	*init_fork(char *philonum)
{
	pthread_mutex_t	*mutex;
	int	len = atoi(philonum);

	mutex = malloc(sizeof(pthread_mutex_t *) * len);

	int	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&mutex[i], NULL) == -1)
			return (NULL);
		i++;
	}
	return (mutex);
}