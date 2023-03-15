#include <philosophers.h>

int	philo_eat(t_philo *philo)
{
	struct timeval t1;
	struct timezone z1;
	z1.tz_dsttime = 0;
	z1.tz_minuteswest = 0;

	pthread_mutex_lock(philo->fork_lh);
	gettimeofday(&t1, &z1);
	printf("%d has take a  %d fork %ld\n", philo->philo_id, philo->philo_id, t1.tv_sec);
	pthread_mutex_lock(philo->fork_rh);
	gettimeofday(&t1, &z1);
	printf("%d has take a  %d fork %ld\n", philo->philo_id, (philo->philo_id + 1) % philo->philo_num, t1.tv_sec);
	gettimeofday(&t1, &z1);
	if (philo->time_to_die != -1 && philo->time_to_die <= t1.tv_sec)
	{
		printf("%ddie       %ld\n", philo->philo_id, philo->time_to_die);
		return (1);
	}
	printf("%dstart eat   %ld\n", philo->philo_id, t1.tv_sec);
	philo->time_to_die = t1.tv_sec + philo->time_to_starve;
	sleep((unsigned int)(philo->time_to_eat));
	pthread_mutex_unlock(philo->fork_lh);
	pthread_mutex_unlock(philo->fork_rh);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	struct timeval t1;
	struct timezone z1;
	z1.tz_dsttime = 0;
	z1.tz_minuteswest = 0;

	gettimeofday(&t1, &z1);
	if (philo->time_to_die <= t1.tv_sec)
	{
		printf("%ddie         %ld\n", philo->philo_id, philo->time_to_die);
		return (1);
	}
	printf("%dstart sleep %ld\n", philo->philo_id, t1.tv_sec);
	sleep((unsigned int)(philo->time_to_sleep));
	return (0);
}

int	parse_argment(int argc, char *argv[])
{
	size_t	i;
	size_t	j;
	size_t	philo_num;
	t_philo	*philo;

	if (argc != 5)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while(argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	while (1)
	{
		if (philo_eat(philo))
			return (NULL);
		if (philo_sleep(philo))
			return (NULL);
	}
	return NULL;
}

int main(int argc, char* argv[]) {

	t_philo		*philos;
	t_waiter		waiter;
	pthread_t	*th_id;
	pthread_mutex_t	*mutex;
	// pthread_mutex_t	mutex[5];
	// pthread_t	th_id[5];
	th_id = NULL;
	int			i;

	if (parse_argment(argc, argv) == 1)
		return (1);
	printf("[parsed]\n");
	mutex = init_fork(argv[1]);
	philos = init_philo(argv, mutex);
	th_id = init_th_id(argv);
	printf("[inited] \n");

	i = 0;
	while (philos[i].is_death == false)
	{
		pthread_create(&th_id[i], NULL, &routine, &philos[i]);
		i++;
	}
	i--;
	while (i >= 0)
	{
		pthread_join(th_id[i], NULL);
		i--;
	}
}
