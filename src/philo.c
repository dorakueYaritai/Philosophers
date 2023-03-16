#include <philosophers.h>

void	take_fork(t_philo *philo, pthread_mutex_t *fork, int fork_id)
{
	struct timeval t1;

	pthread_mutex_lock(fork);
	gettimeofday(&t1, NULL);
	printf("%d has take a  %d fork %d\n", philo->philo_id, fork_id, t1.tv_usec);
}

int	check_am_i_dead(t_philo *philo)
{
	struct timeval t1;

	gettimeofday(&t1, NULL);
	if (philo->time_to_die != -1 && philo->time_to_die <= t1.tv_usec)
	{
		printf("%ddie       %ld\n", philo->philo_id, philo->time_to_die);
		exit (1);
		// return (1);
	}
}

	// pthread_mutex_lock(philo->fork_lh);
	// gettimeofday(&t1, &z1);
	// printf("%d has take a  %d fork %d\n", philo->philo_id, philo->fork1_id, t1.tv_usec);
	// pthread_mutex_lock(philo->fork_rh);
	// gettimeofday(&t1, &z1);
	// printf("%d has take a  %d fork %ld\n", philo->philo_id, philo->fork2_id, t1.tv_usec);

int	philo_eat(t_philo *philo)
{
	struct timeval t1;

	take_fork(philo, philo->fork_lh, philo->fork1_id);
	take_fork(philo, philo->fork_rh, philo->fork2_id);
	// check_am_i_dead(philo);
	gettimeofday(&t1, NULL);
	if (philo->time_to_die != -1 && philo->time_to_die <= t1.tv_usec)
	{
		printf("%ddie       %ld\n", philo->philo_id, philo->time_to_die);
		return (1);
	}
	printf("%dstart eat   %d\n", philo->philo_id, t1.tv_usec);
	philo->time_to_die = t1.tv_usec + philo->time_to_starve;
	usleep((unsigned int)(philo->time_to_eat));
	pthread_mutex_unlock(philo->fork_lh);
	pthread_mutex_unlock(philo->fork_rh);
	return (0);
}

int	philo_usleep(t_philo *philo)
{
	struct timeval t1;

	gettimeofday(&t1, NULL);
	if (philo->time_to_die <= t1.tv_usec)
	{
		printf("%ddie         %ld\n", philo->philo_id, philo->time_to_die);
		return (1);
	}
	printf("%dstart sleep %ld\n", philo->philo_id, t1.tv_usec);
	usleep((unsigned int)(philo->time_to_sleep));
	return (0);
}

int	philo_think(t_philo *philo)
{
	struct timeval t1;

	gettimeofday(&t1, NULL);
	printf("%dstart thinking %ld\n", philo->philo_id, t1.tv_usec);
	take_fork(philo, philo->fork_lh, philo->fork1_id);
	take_fork(philo, philo->fork_rh, philo->fork2_id);
	philo_eat(philo);
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
		if (philo_usleep(philo))
			return (NULL);
	}
	return NULL;
}

int main(int argc, char* argv[]) {

	t_philo		*philos;
	// t_waiter		waiter;
	pthread_t	*th_id;
	pthread_mutex_t	*mutex;
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
		// print_philo_status(&philos[i]);
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
