#include <philosophers.h>


int main(int argc, char* argv[]) {
	t_philo		*philos;
	pthread_t	*th_id;
	t_fork	*forks;
	int			i;

	if (parse_argment(argc, argv) == 1)
		return (1);
	forks = init_fork(argv[1]);
	philos = init_philo(argv, forks);
	th_id = init_th_id(argv);

	i = 0;
	while (philos[i].is_death == false)
	{
		if (pthread_create(&th_id[i], NULL, &routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	i--;
	while (i >= 0)
	{
		if (pthread_join(th_id[i], NULL) != 0)
			return (2);
		i--;
	}
}
