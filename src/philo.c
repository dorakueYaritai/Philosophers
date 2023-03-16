#include <philosophers.h>


int main(int argc, char* argv[]) {
	t_philo		*philos;
	// t_waiter		waiter;
	pthread_t	*th_id;
	pthread_mutex_t	*mutex;
	th_id = NULL;
	int			i;

	if (parse_argment(argc, argv) == 1)
		return (1);
	mutex = init_fork(argv[1]);
	philos = init_philo(argv, mutex);
	th_id = init_th_id(argv);

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
