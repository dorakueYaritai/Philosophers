#include <philosophers.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);	

void	take_fork(t_philo *philo, pthread_mutex_t *fork, int fork_id)
{
	struct timeval t1;
	long sec_milli;

	pthread_mutex_lock(fork);
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	printf("%ld %d has taken a fork\n", sec_milli, philo->philo_id);
}

int	check_am_i_dead(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die != -1 && philo->time_to_die <= sec_milli)
	{
		printf("%ld %d died\n", philo->time_to_die, philo->philo_id);
		exit (1);
		return (1);
	}
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die != -1 && philo->time_to_die <= sec_milli)
	{
		printf("%ld %d died\n", philo->time_to_die, philo->philo_id);
		return (1);
	}
	printf("%ld %d is eating\n",  sec_milli, philo->philo_id);
	philo->time_to_die = sec_milli + philo->time_to_starve;
	usleep((unsigned int)(philo->time_to_eat) * 1000);
	pthread_mutex_unlock(philo->fork_lh);
	pthread_mutex_unlock(philo->fork_rh);
	return (philo_sleep(philo));
}

static int	philo_sleep(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die <= sec_milli)
	{
		printf("%ld %d died\n", philo->time_to_die, philo->philo_id);
		return (1);
	}
	printf("%ld %d is sleeping\n",  sec_milli, philo->philo_id);
	usleep((unsigned int)(philo->time_to_sleep) * 1000);
	return (philo_think(philo));
}

static int	philo_think(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	printf("%ld %d is thinking\n",  sec_milli, philo->philo_id);
	take_fork(philo, philo->fork_lh, philo->fork1_id);
	check_am_i_dead(philo);
	take_fork(philo, philo->fork_rh, philo->fork2_id);
	return (philo_eat(philo));
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	philo_think(philo);
	return NULL;
}
