#include <philosophers.h>


int main(int argc, char* argv[]) {
	t_philo		*philos;
	// t_waiter		waiter;
	pthread_t	*th_id;
	// pthread_mutex_t	*forks;
	pthread_mutex_t	*fork_check;
	t_fork	*forks;
	th_id = NULL;
	int			i;

	if (parse_argment(argc, argv) == 1)
		return (1);
	forks = init_fork(argv[1]);
	// fork_check = init_fork_check(argv[1]);
	philos = init_philo(argv, forks);
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
