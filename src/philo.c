#include <philosophers.h>

int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num)
{
	int	i;

	i = 0;
	while (philos[i].is_death == false)
	{
		if (pthread_create(&th_id[i], NULL, &routine, &philos[i]) != 0)
		{
			printf("FOOOOOOOOOOOO!!!\n");
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
			return (1);
		i++;
	}
	return (0);
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
	if (threads_join(philos, th_id, philo_num) == 2)
		return (2);
}
